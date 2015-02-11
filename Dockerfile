FROM jedahan/debian-sarge

MAINTAINER Jonathan Dahan jonathan@jonathan.is

COPY src /usr/local/share/palmdev

RUN apt-get install -y build-essential gcc-2.95 pilrc prc-tools prc-tools-doc

VOLUME /root/example

CMD bash
