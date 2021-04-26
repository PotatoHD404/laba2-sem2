import eventlet
from flask import Flask, render_template, request, session
from flask_socketio import SocketIO, emit
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_session import Session
from datetime import datetime
from secrets import token_urlsafe
from cert import run
import paramiko
import re

eventlet.monkey_patch()

app = Flask(__name__)

app.config.from_pyfile('config.py')

db = SQLAlchemy(app)
migrate = Migrate(app, db)

sess = Session(app)
app.config['SESSION_SQLALCHEMY'] = db
sess.init_app(app)

socketio = SocketIO(app, manage_session=False, logger=True, engineio_logger=True,
                    cors_allowed_origins=['https://potatohd.ru', 'https://ui'])

clientsList = {}


def bg_emit():
    for token in clientsList:
        j = clientsList[token]
        channel = j[0]
        res = ''
        tmp = b''

        if channel.recv_ready():
            tmp = channel.recv(4096)
        # noinspection PyTypeChecker
        while len(tmp) == 4096:
            res += tmp.decode('utf-8')
            tmp = channel.recv(4096)
        res += tmp.decode('utf-8')
        exists1 = len(ConsoleText.query.filter_by(token=token).all()) > 0
        if res != '':
            try:
                if not exists1:
                    new_text = ConsoleText(content=res, token=token)
                    db.session.add(new_text)
                else:
                    ConsoleText.query.filter_by(token=token).first().content += res
                db.session.commit()
                if not exists1:
                    exists1 += 1
            except Exception:
                print('Exception happened')
            text = (ConsoleText.query.filter_by(token=token).first().content if exists1 else '').replace('\n', '\r\n')
            pattern = re.compile(
                r"(PolyA:\r\n(?P<PolyA>[ix()0-9^+\-* ]+)\r\n)|(PolyB:\r\n(?P<PolyB>[ix()0-9^+\-* ]+)\r\n)|" +
                r"(Result:\r\n(?P<Result>[ix()0-9^+\-* ]+)\r\n)")
            res = [i.groupdict() for i in pattern.finditer(text)]
            state = {'PolyA': '', 'PolyB': '', 'Result': ''}
            for i in res:
                for key, value in i.items():
                    if value is not None:
                        state[key] = value
            socketio.emit('refresh', {'token': token,
                                      'text': text, 'state': state},
                          room=j[1])


def listen():
    while True:
        bg_emit()
        eventlet.sleep(0.5)


if __name__ == '__main__':
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect('core', username='user', password='password')
    eventlet.spawn(listen)


class ConsoleText(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.Text, nullable=False)
    date_created = db.Column(db.DateTime, default=datetime.utcnow)
    token = db.Column(db.String(22), nullable=False)

    def __repr__(self):
        """Get data representation"""
        return '<Row %r>' % self.id


def login():
    if not session.get('token'):
        token = token_urlsafe(16)
        session['token'] = token


@app.route('/', methods=['GET'])
def index():
    login()
    exists = len(ConsoleText.query.filter_by(token=session['token']).all()) > 0
    token = session['token']
    return render_template('index.html', token=token,
                           text=ConsoleText.query.filter_by(token=token).first().content if exists else '')


@socketio.on('connect')
def connect():
    login()
    global client
    global clientsList
    token = session['token']
    exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
    if exists:
        ConsoleText.query.filter_by(token=token).first().content = ''
        db.session.commit()
    if token not in clientsList:
        channel = client.get_transport().open_session()
        channel.invoke_shell()
        clientsList[token] = [channel, request.sid]
        channel.sendall('\n'.join(['cd /app', './Laba2']) + '\n')
    emit('refresh', {'token': token,
                     'text': (ConsoleText.query.filter_by(
                         token=token).first().content if exists else '').replace('\n', '\r\n')})


@socketio.on('disconnect')
def disconnect():
    global clientsList
    token = session['token']
    if token in clientsList:
        del clientsList[token]
    print('Client disconnected')


# @socketio.on('command')
# def command():
#     emit('log', str(clientsList))


@socketio.on('command')
def tests(json):
    types = {'int': '1', 'float': '2', 'complex': '3'}
    polys = {'a': '1', 'b': '2'}
    commands = ''
    try:
        if json['command'] == 'type':
            commands = [types[json["type"]], '6', polys['a'], '6', polys['b']]
        elif json['command'] == 'input':
            pattern = re.compile(
                r"^(([\-0-9]+(\.[0-9]+)?)+( ([\-0-9]+(\.[0-9]+)?))? )*(([\-0-9]+(\.[0-9]+)?)"
                + r"( ([\-0-9]+(\.[0-9]+)?))?)+$")
            if len(pattern.findall(json["input"])) > 0:
                commands = ['1', polys[json['poly']], json['input'], '6', polys[json['poly']]]
        elif json['command'] == 'multiply':
            commands = ['2']
        elif json['command'] == 'scalarMultiply':
            if re.match(r"^([\-0-9]+(\.[0-9]+)?)( ([\-0-9]+(\.[0-9]+)?))?$", json['scalar']):
                commands = ['3', polys[json['poly']], json['scalar']]
        elif json['command'] == 'calc':
            if re.match(r"^([\-0-9]+(\.[0-9]+)?)( ([\-0-9]+(\.[0-9]+)?))?$", json['x']):
                commands = ['5', polys[json['poly']], json['x']]
        elif json['command'] == 'sum':
            commands = ['4']
        elif json['command'] == 'tests':
            commands = ['0', 'cd /app', './Tests --gtest_repeat=1']
        elif json['command'] == 'clear':
            token = session['token']
            exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
            if exists:
                ConsoleText.query.filter_by(token=token).first().content = ''
                db.session.commit()
            emit('refresh', {'token': token,
                             'text': (ConsoleText.query.filter_by(
                                 token=token).first().content if exists else '').replace('\n', '\r\n')})
            return
    except:
        pass
    if commands == '':
        emit('error', 'Input error')
    else:
        token = session['token']
        command = '\n'.join(commands) + '\n'
        exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
        if not exists:
            new_text = ConsoleText(content=command, token=token)
            db.session.add(new_text)
        else:
            ConsoleText.query.filter_by(token=token).first().content += command
        db.session.commit()
        channel = clientsList[session['token']][0]
        channel.sendall(command)
        emit('refresh', {'token': token,
                         'text': (ConsoleText.query.filter_by(
                             token=token).first().content if exists else '').replace('\n', '\r\n')})


if __name__ == '__main__':
    run()
    socketio.run(app, host='ui', port=443, keyfile='key.pem', certfile='cert.pem')
