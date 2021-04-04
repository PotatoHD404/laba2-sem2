from flask import Flask
from flask_restful import Resource, Api
import paramiko

app = Flask(__name__)
api = Api(app)


# @app.route('/', methods=('GET'))
class Product(Resource):
    @staticmethod
    def get():
        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect("core", username="user", password="password")
        # session = client.open_channel(kind='session')
        ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("cd /app && ./Tests ")
        # ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command("ls")
        # ssh = client.invoke_shell()
        # response = ssh.send("Hentai")
        # ssh.close()
        data = [[i[:-1] for i in ssh_stdout.readlines()], [i[:-1] for i in ssh_stderr.readlines()]]
        client.close()
        return {'product': [data]}


api.add_resource(Product, '/')

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=80, debug=True)
