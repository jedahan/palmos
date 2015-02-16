CC = m68k-palmos-gcc
CFLAGS = -O2 -palmos3.5

all: ui bin.stamp
	build-prc ui.prc "UI" TuUi ui *.bin

ui: ui.o
	$(CC) $(CFLAGS) -o ui ui.o

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c

bin.stamp: ui.rcp ui.h uimono.bmp uigrey4.bmp uigrey16.bmp uicolor.bmp
	pilrc ui.rcp

clean:
	-rm -f *.[oa] ui *.bin *.stamp
