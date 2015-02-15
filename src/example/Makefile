CC = m68k-palmos-gcc
CFLAGS = -O2 -palmos3.5
APP = hello
DEPS = $(APP).rcp $(APP).h $(APP).bmp

all: $(APP).prc

%.prc: % bin.stamp
	build-prc $@ "Hello World!" TuHe $< *.bin

%: %.o
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

bin.stamp: $(DEPS)
	pilrc $<

.PHONY: clean

clean:
	-rm -f *.[oa] $(APP) *.bin *.stamp
