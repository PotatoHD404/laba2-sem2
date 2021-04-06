FROM willwill/wait-for-it
RUN -s -t 30 ui:80 --

FROM ubuntu:latest
RUN curl ui -o output.txt