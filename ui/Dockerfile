FROM python:3.7

WORKDIR /app

COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

COPY . .

RUN flask db init
RUN flask db migrate -m "Initial migration."
RUN flask db upgrade

CMD [ "python", "app.py"]