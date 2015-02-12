CONTAINER = jedahan/palmos
EXAMPLE = /root/example

all: hello.prc

hello.prc: 
	docker run -v /home/micro/code/palm/src/example:$(EXAMPLE) -w $(EXAMPLE) -t $(CONTAINER):latest make

clean:
	-rm -f *prc
