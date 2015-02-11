FROM jedahan/debian-sarge

MAINTAINER Jonathan Dahan jonathan@jonathan.is

COPY src /usr/local/share/palmdev

RUN apt-get install -y pilrc prc-tools prc-tools-doc

VOLUME /home/micro/palm/src

CMD bash
