CONTAINER = jedahan/palmos
EXAMPLE = /root/example
ROOTFS = /var/tmp/rootfs
CWD = $(shell pwd)

all: hello.prc

test:
	echo $(CWD)/src/example

hello.prc: 
	docker run -v $(CWD)/src/example:$(EXAMPLE) -w $(EXAMPLE) -t $(CONTAINER):latest make

debian-sarge:
	sudo debootstrap --arch=i386 sarge $(ROOTFS) http://archive.debian.org/debian/
	rm -rf $(ROOTFS)/{dev,proc}
	mkdir -p $(ROOTFS){dev,proc}
	mkdir -p $(ROOTFS)/etc
	cp /etc/resolv.conf $(ROOTFS)/etc/
	tar --numeric-owner -caf $(ROOTFS)/rootfs.tar.xz -C $(ROOTFS) --transform='s,^./,,' .
	cat > $(ROOTFS)/Dockerfile <<EOF
	FROM scratch
	ADD rootfs.tar.xz /
	EOF
	docker build -t $(USER)/debian-sarge $(ROOTFS)
		
palmos:
	docker build -t $(USER)/palmos .

clean:
	-rm -f src/example/*{bin,prc}
	-rm -rf $(ROOTFS)
