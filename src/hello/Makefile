CC = m68k-palmos-gcc
CFLAGS = -O2 -palmos3.5
APP = $(notdir $(shell pwd))

all: $(APP) bin.stamp
	build-prc $(APP).prc $(APP) TuHe $< *.bin

%: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

bin.stamp: $(APP).rcp $(APP).h $(APP).bmp
	pilrc $<

.PHONY: clean

clean:
	-rm -f *.[oa] $(APP) *.bin *.stamp
