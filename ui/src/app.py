import eventlet
from flask import Flask, render_template, request, session
from flask_socketio import SocketIO, emit
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_session import Session
from datetime import datetime
from secrets import token_urlsafe
import paramiko

eventlet.monkey_patch()

app = Flask(__name__)

app.config.from_pyfile('config.py')

db = SQLAlchemy(app)
migrate = Migrate(app, db)

sess = Session(app)
app.config['SESSION_SQLALCHEMY'] = db
sess.init_app(app)

socketio = SocketIO(app, manage_session=False, logger=True, engineio_logger=True)

clientsList = {}


def bg_emit():
    for token in clientsList:
        j = clientsList[token]
        channel = j[0]
        res = ""
        tmp = b""

        if channel.recv_ready():
            tmp = channel.recv(4096)
        while len(tmp) == 4096:
            res += tmp.decode('utf-8')
            tmp = channel.recv(4096)
        res += tmp.decode('utf-8')
        exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
        if res != "":
            if exists:
                ConsoleText.query.filter_by(token=token).first().content += res
            else:
                new_text = ConsoleText(content=res, token=token)

            try:
                if not exists:
                    db.session.add(new_text)
                db.session.commit()
                if not exists:
                    exists += 1
            except Exception:
                'Pass'
            socketio.emit('refresh', {'token': token,
                                      'text': (ConsoleText.query.filter_by(
                                          token=token).first().content if exists else "").replace('\n', '\r\n')},
                          room=j[1])


def listen():
    while True:
        bg_emit()
        eventlet.sleep(0.5)


if __name__ == '__main__':
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect("core", username="user", password="password")
    eventlet.spawn(listen)


class ConsoleText(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.Text, nullable=False)
    date_created = db.Column(db.DateTime, default=datetime.utcnow)
    token = db.Column(db.String(22), nullable=False)

    def __repr__(self):
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
    return render_template("index.html", token=token,
                           text=ConsoleText.query.filter_by(token=token).first().content if exists else "")


@socketio.on('connect')
def connect():
    login()
    global client
    global clientsList
    token = session['token']
    exists = len(ConsoleText.query.filter_by(token=token).all()) > 0

    if token not in clientsList:
        channel = client.get_transport().open_session()
        channel.invoke_shell()
        clientsList[token] = [channel, request.sid]

    emit('refresh', {'token': token,
                     'text': (ConsoleText.query.filter_by(
                         token=token).first().content if exists else "").replace('\n', '\r\n')})


@socketio.on('disconnect')
def disconnect():
    global clientsList
    token = session['token']
    if token in clientsList:
        del clientsList[token]
    print('Client disconnected')


@socketio.on('clear')
def clear():
    token = session['token']
    exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
    if exists:
        ConsoleText.query.filter_by(token=token).first().content = ""
        db.session.commit()
    emit('refresh', {'token': token,
                     'text': (ConsoleText.query.filter_by(
                         token=token).first().content if exists else "").replace('\n', '\r\n')})


@socketio.on('command')
def command():
    emit('log', str(clientsList))


@socketio.on('tests')
def tests():
    channel = clientsList[session['token']][0]
    channel.sendall(f'cd /app\n')
    channel.sendall(f'./Tests --gtest_repeat=1\n')
    emit('log', 'tests started')


if __name__ == '__main__':
    socketio.run(app, host="0.0.0.0", port=80, debug=True)
