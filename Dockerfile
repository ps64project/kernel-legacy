FROM gcc:latest
MAINTAINER P.Knowledge <knowledge@patche.me>

RUN apt update -yq && \
    apt install -yq --no-install-recommends nasm;

ADD . /app
WORKDIR /app

RUN make 

WORKDIR /
