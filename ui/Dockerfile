FROM python:3.7

WORKDIR /app

COPY ./src .
COPY ./gunicorn.sh ./../
RUN pip install --no-cache-dir -r requirements.txt

RUN flask db init
RUN flask db migrate -m "Initial migration."
RUN flask db upgrade