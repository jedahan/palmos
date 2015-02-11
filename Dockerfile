FROM jedahan/debian-sarge

MAINTAINER Jonathan Dahan jonathan@jonathan.is

RUN mkdir -p /usr/local/share/palmdev

COPY src/sdk3.1 /usr/local/share/palmdev

RUN apt-get install -y pilrc prc-tools prc-tools-doc

VOLUME /home/micro/palm/src

CMD bash
