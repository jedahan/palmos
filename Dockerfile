FROM jedahan/debian-sarge

MAINTAINER Jonathan Dahan jonathan@jonathan.is

COPY src/sdk-3.5 /usr/local/share/palmdev/sdk-3.5

RUN apt-get install -y build-essential gcc-2.95 pilrc prc-tools prc-tools-doc

VOLUME /root/example

CMD bash
