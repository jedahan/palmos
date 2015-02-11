CC = m68k-palmos-gcc
CFLAGS = -O2 -palmos3.5

all: hello.prc

hello.prc: hello bin.stamp
	build-prc hello.prc "Hello World!" TuHe hello *.bin

hello: hello.o
	$(CC) $(CFLAGS) -o hello hello.o

hello.o: hello.c hello.h
	$(CC) $(CFLAGS) -c hello.c

bin.stamp: hello.rcp hello.h hello.bmp
	pilrc hello.rcp

clean:
	-rm -f *.[oa] hello *.bin *.stamp
