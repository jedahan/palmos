CONTAINER = jedahan/palmos
ROOTFS = /var/tmp/rootfs
TMP = /var/tmp
CWD = $(shell pwd)

all: hello.prc giraffe.prc ui.prc

%.prc: src/%/Makefile
	docker run -v $(CWD)/src:$(TMP) -w $(TMP)/$(@:.prc=) -t $(CONTAINER):latest make

define DOCKERFILE
FROM scratch
ADD rootfs.tar.xz /
endef
export DOCKERFILE
# needs sudo!
debian-sarge:
	debootstrap --arch=i386 sarge $(ROOTFS) http://archive.debian.org/debian/
	rm -rf $(ROOTFS)/{dev,proc}
	mkdir -p $(ROOTFS){dev,proc}
	mkdir -p $(ROOTFS)/etc
	cp /etc/resolv.conf $(ROOTFS)/etc/
	-rm -f $(ROOTFS)/rootfs.tar.xz
	tar --numeric-owner -caf rootfs.tar.xz -C $(ROOTFS) --transform='s,^./,,' .
	-rm -rf $(ROOTFS)/*
	cp rootfs.tar.xz $(ROOTFS)/
	echo "$$DOCKERFILE" >> $(ROOTFS)/Dockerfile
	docker build -t $(USER)/debian-sarge $(ROOTFS)
		
palmos:
	docker build -t $(USER)/palmos .

phem:
	sudo adb push src/*/*.prc /sdcard/phem/card/

.PHONY: clean

clean:
	-rm -f src/*/*{bin,prc}
	-rm -rf $(ROOTFS)
