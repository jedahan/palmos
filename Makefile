CONTAINER = jedahan/palmos
ROOTFS = /var/tmp/rootfs
TMP = /var/tmp
CWD = $(shell pwd)
DEPS = intexp.prc

all: $(DEPS)

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

push: $(DEPS:.prc=-push)
.PHONY: push

%-push:
	sudo adb push src/$(@:-push=)/$(@:-push=.prc) /sdcard/phem/card/

clean: $(DEPS:.prc=-clean)
.PHONY: clean

%-clean:
	docker run -v $(CWD)/src:$(TMP) -w $(TMP)/$(@:-clean=) -t $(CONTAINER):latest make clean
