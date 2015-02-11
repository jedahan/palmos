FROM jedahan/debian-sarge

MAINTAINER Jonathan Dahan, jonathan@jonathan.is

RUN apt-get install -y pilrc
RUN apt-get install -y prc-tools
RUN apt-get install -y prc-tools-doc

ADD src/sdk1+2+3.1.tar.gz /root/
ADD src/example.tar.gz /root/

RUN tar xf /root/sdk1+2+3.1.tar.gz
RUN tar xf /root/example.tar.gz

CMD bash
