from celery import Celery
import config
from time import sleep

celery = Celery('worker', broker=config.CELERY_BROKER_URL, backend=config.CELERY_BROKER_URL)


@celery.task(name='thread_function')
def thread_function(clientsList, emit):
    print("shiiiiiiiiiiiiiiiiiiiiiiet")
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
