from flask import Flask, render_template, url_for, request, redirect
from flask_restful import Resource, Api
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
import paramiko

app = Flask(__name__)
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
db = SQLAlchemy(app)
migrate = Migrate(app, db)


class Text(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.TEXT(), nullable=False)

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
    res = send("cd /app")
    # res = send(channel, "/usr/bin/valgrind --tool=memcheck --gen-suppressions=all --leak-check=full \
    # --leak-resolution=med --track-origins=yes --vgdb=no /app/Tests --gtest_repeat=1 --gtest_color=no")
    res = send("./Tests --gtest_repeat=1 --gtest_color=no")
    # res = send(channel, "./Tests")
    # res1 = send(channel, "apt1")
    # send_command(remote_conn, cmd='conf t')
    # client.exec_command("cd /app")

    # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("./Tests")
    #
    # data = [i[:-1] for i in ssh_stdout.readlines()] + [i[:-1] for i in ssh_stderr.readlines()]
    data = res
    # data = ""
    # client.close()
    return {"res": data}


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=80, debug=True)
