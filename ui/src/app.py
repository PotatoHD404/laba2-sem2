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
clientsList = {}


class ConsoleText(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.Text, nullable=False)
    date_created = db.Column(db.DateTime, default=datetime.utcnow)
    token = db.Column(db.String(22), nullable=False)

    def __repr__(self):
        return '<Row %r>' % self.id


if __name__ == '__main__':
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect("core", username="user", password="password")
    channel = client.get_transport().open_session()
    channel.invoke_shell()


# request.cookies.get('token')
@app.route('/api/get_text', methods=['GET'])
def resp():
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
    try:
        exists = len(ConsoleText.query.filter_by(token=token).all()) > 0
    except Exception:
        exists = 0
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


def get_cookie(sender):
    if not request.cookies.get('token'):
        res = make_response("Setting a cookie")
        res.set_cookie('token', token_urlsafe(16), max_age=60 * 60 * 24 * 30)
    else:
        res = make_response(f"Value of cookie foo is {request.cookies.get('token')}")

    return redirect(sender)


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
    return res


@app.route('/', methods=['GET'])
def index():
    if not request.cookies.get('token'):
        token = token_urlsafe(16)
        res = make_response(render_template("index.html", variable=request.cookies.get('token')))
        res.set_cookie('token', token, max_age=60 * 60 * 24 * 30)
        return res

    return render_template("index.html", variable=request.cookies.get('token'))


@app.route('/api/tests', methods=['GET'])
def get():
    send("cd /app")
    send("./Tests --gtest_repeat=1 --gtest_color=no")
    return "Ok"


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=80, debug=True)
