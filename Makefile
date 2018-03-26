
CFLAGS:=-I/usr/include/libweston-3 -I/usr/include/weston -I/usr/include/pixman-1 \
	 -fPIC

LDFLAGS:=-shared -lweston-3

binder.so: binder.c Makefile
	gcc ${CFLAGS} $< ${LDFLAGS} -o $@
