from flask import Flask, render_template, url_for, request, redirect, make_response
# from flask_restful import Resource, Api
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from datetime import datetime
from secrets import token_urlsafe
import paramiko

app = Flask(__name__)
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
db = SQLAlchemy(app)
migrate = Migrate(app, db)
clientsList = []


class ConsoleText(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.Text, nullable=False)
    date_created = db.Column(db.DateTime, default=datetime.utcnow)

    def __repr__(self):
        return '<Row %r>' % self.id


if __name__ == '__main__':
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect("core", username="user", password="password")
    # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("cd /app && ./Tests")
    # client.exec_command("cd /app", get_pty=True)
    # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("cd /app && ./Tests")
    channel = client.get_transport().open_session()
    # tmp = channel.get_pty()
    channel.invoke_shell()


@app.route('/api/get_text', methods=['GET'])
def resp():
    res = ""
    tmp = b""
    if channel.recv_ready():
        tmp = channel.recv(4096)
    while len(tmp) == 4096:
        res += tmp.decode('utf-8')
        tmp = channel.recv(4096)
    res += tmp.decode('utf-8')
    return res


@app.route('/api/cookie', methods=['GET'])
def cookie():
    if not request.cookies.get('foo'):
        res = make_response("Setting a cookie")
        res.set_cookie('foo', 'bar', max_age=60 * 60 * 24 * 365 * 2)
    else:
        res = make_response("Value of cookie foo is {}".format(request.cookies.get('foo')))
    return res


def send(cmd):
    channel.sendall(f'{cmd}\n')
    res = ""
    tmp = b""
    if channel.recv_ready():
        tmp = channel.recv(4096)
    while len(tmp) == 4096:
        res += tmp.decode('utf-8')
        tmp = channel.recv(4096)
    res += tmp.decode('utf-8')
    return res.split('\n')


@app.route('/', methods=['GET'])
def index():
    return render_template("index.html")


@app.route('/api/tests', methods=['GET'])
def get():
    send("cd /app")
    res = send("./Tests --gtest_repeat=1 --gtest_color=no")
    data = res
    return {"res": data}


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=80, debug=True)
