FROM gcc:latest
MAINTAINER P.Knowledge <knowledge@patche.me>

RUN apt update -yq && \
    apt install -yq --no-install-recommends nasm;

RUN make 

WORKDIR /
