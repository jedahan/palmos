FROM jedahan/debian-sarge

MAINTAINER Jonathan Dahan jonathan@jonathan.is

COPY src/sdk-3.5 /usr/local/share/palmdev/sdk-3.5

RUN apt-get install -y make gcc-2.95 pilrc prc-tools prc-tools-doc

VOLUME /var/tmp

CMD bash
