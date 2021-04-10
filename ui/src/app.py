from flask import Flask, render_template, url_for, request, redirect, make_response, Response, session
from flask_socketio import SocketIO, emit
from celery import Celery
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_session import Session, SqlAlchemySessionInterface
from datetime import datetime
from secrets import token_urlsafe
import threading
from time import sleep
import paramiko

app = Flask(__name__)
app.config['SECRET_KEY'] = 'LbcDtbci8PzffxMQHvgvgdWxjBPrzzoLxuBN4PzK014'
app.secret_key = 'LbcDtbci8PzffxMQHvgvgdWxjBPrzzoLxuBN4PzK014'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True  # not quiet warning message

db = SQLAlchemy(app)
migrate = Migrate(app, db)

sess = Session(app)
SqlAlchemySessionInterface(app, db, "sessions", "sess_")
sess.init_app(app)
# sess.app.session_interface.db.create_all()

socketio = SocketIO(app, manage_session=False)

app.config['CELERY_BROKER_URL'] = 'redis://redis-server:6379/0'
celery = Celery(app.name, broker=app.config['CELERY_BROKER_URL'])
celery.conf.update(app.config)

clientsList = {}


@celery.task(bind=True)
def thread_function():
    while True:
        for token, j in zip(clientsList.keys(), clientsList.values()):
            emit('log', 'working', room=j[1])
            # channel = j[0]
            # res = ""
            # tmp = b""
            #
            # if channel.recv_ready():
            #     tmp = channel.recv(4096)
            # while len(tmp) == 4096:
            #     res += tmp.decode('utf-8')
            #     tmp = channel.recv(4096)
            # res += tmp.decode('utf-8')
            # exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
            # if res != "":
            #     if exists:
            #         ConsoleText.query.filter_by(token=token).first().content += res
            #     else:
            #         new_text = ConsoleText(content=res, token=token)
            #
            #     try:
            #         if not exists:
            #             db.session.add(new_text)
            #         db.session.commit()
            #         if not exists:
            #             exists += 1
            #     except Exception:
            #         'Pass'
            #     emit('refresh', {'token': token,
            #                      'text': ConsoleText.query.filter_by(token=token).first().content if exists else ""},
            #          room=j[1])
        sleep(0.5)


if __name__ == '__main__':
    x = threading.Thread(target=thread_function)
    x.start()
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect("core", username="user", password="password")


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
        # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("cd /app && ./Tests")
        # client.exec_command("cd /app", get_pty=True)
        # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("cd /app && ./Tests")
        channel = client.get_transport().open_session()
        # tmp = channel.get_pty()
        channel.invoke_shell()
        clientsList[token] = [channel, request.sid]

    emit('log', str(clientsList))
    emit('refresh', {'token': token,
                     'text': ConsoleText.query.filter_by(token=token).first().content if exists else ""})


@socketio.on('disconnect')
def disconnect():
    global clientsList
    token = session['token']
    if token in clientsList:
        del clientsList[token]
    print('Client disconnected')


# @socketio.on('restart')
# def restart(json):
#     print('received json: ' + str(json))


@socketio.on('clear')
def clear():
    token = session['token']
    exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
    if exists:
        ConsoleText.query.filter_by(token=token).first().content = ""
        db.session.commit()
    emit('refresh', {'token': token,
                     'text': ConsoleText.query.filter_by(token=token).first().content if exists else ""})


@socketio.on('command')
def command():
    token = session['token']
    emit('log', str(clientsList))
    # emit('response', 'Connected')


@socketio.on('tests')
def tests():
    channel = clientsList[session['token']][0]
    channel.sendall(f'cd /app\n')
    channel.sendall(f'./Tests --gtest_repeat=1 --gtest_color=no\n')
    emit('log', 'tests started')


if __name__ == '__main__':
    socketio.run(app, host="0.0.0.0", port=80, debug=True)
