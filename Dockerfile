FROM jedahan/debian-sarge

MAINTAINER Jonathan Dahan, jonathan@jonathan.is

RUN apt-get install -y pilrc prc-tools prc-tools-doc

ADD src /root

CMD bash
