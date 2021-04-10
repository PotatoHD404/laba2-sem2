from flask import Flask, render_template, url_for, request, redirect, make_response, Response, session
from flask_socketio import SocketIO, emit
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_session import Session
from datetime import datetime
from secrets import token_urlsafe
import paramiko

app = Flask(__name__)
app.config['SECRET_KEY'] = 'LbcDtbci8PzffxMQHvgvgdWxjBPrzzoLxuBN4PzK014'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
app.config['SESSION_TYPE'] = 'sqlalchemy'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True  # not quiet warning message

db = SQLAlchemy(app)
migrate = Migrate(app, db)

sess = Session(app)

app.config['SESSION_SQLALCHEMY_TABLE'] = 'sessions'
app.config['SESSION_SQLALCHEMY'] = db
sess.app.session_interface.db.create_all()

socketio = SocketIO(app, manage_session=False)

clientsList = {}


class ConsoleText(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.Text, nullable=False)
    date_created = db.Column(db.DateTime, default=datetime.utcnow)
    token = db.Column(db.String(22), nullable=False)

    def __repr__(self):
        return '<Row %r>' % self.id


@app.route('/api/get_text', methods=['GET'])
def resp(channel):
    if not request.cookies.get('token'):
        res = make_response(redirect("/api/get_text"))
        res.set_cookie('token', token_urlsafe(16), max_age=60 * 60 * 24 * 30)
        return res

    res = ""
    tmp = b""

    if channel.recv_ready():
        tmp = channel.recv(4096)
    while len(tmp) == 4096:
        res += tmp.decode('utf-8')
        tmp = channel.recv(4096)
    res += tmp.decode('utf-8')
    token = request.cookies.get('token')
    exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
    if res != "":
        if exists != 0:
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

    if exists or res != "":
        res = ConsoleText.query.filter_by(token=token).first().content

    return res


def login():
    if not session.get('token'):
        token = token_urlsafe(16)
        session['token'] = token


def send(cmd, channel):
    channel.sendall(f'{cmd}\n')
    res = ""
    tmp = b""
    if channel.recv_ready():
        tmp = channel.recv(4096)
    while len(tmp) == 4096:
        res += tmp.decode('utf-8')
        tmp = channel.recv(4096)
    res += tmp.decode('utf-8')
    return res


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
    # if __name__ == '__main__':
    #     client = paramiko.SSHClient()
    # client.load_system_host_keys()
    # client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    # client.connect("core", username="user", password="password")
    # # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("cd /app && ./Tests")
    # # client.exec_command("cd /app", get_pty=True)
    # # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("cd /app && ./Tests")
    # channel = client.get_transport().open_session()
    # # tmp = channel.get_pty()
    # channel.invoke_shell()
    exists = len(ConsoleText.query.filter_by(token=session['token']).all()) > 0
    token = session['token']

    emit('refresh', {'token': token,
                     'text': ConsoleText.query.filter_by(token=token).first().content if exists else ""})


@socketio.on('disconnect')
def disconnect():
    print('Client disconnected')


@socketio.on('restart')
def restart(json):
    print('received json: ' + str(json))


@socketio.on('command')
def command(json):
    emit('response', 'Connected')


@socketio.on('tests')
def get():
    send("cd /app")
    send("./Tests --gtest_repeat=1 --gtest_color=no")


if __name__ == '__main__':
    socketio.run(app, host="0.0.0.0", port=80, debug=True)
