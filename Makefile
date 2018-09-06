
CFLAGS:=-I/usr/include/libweston-5 -I/usr/include/libevdev-1.0 \
	-I/usr/include/weston -I/usr/include/pixman-1 \
	 -fPIC -Wall

LDFLAGS:=-shared -lweston-5

binder.so: binder.c Makefile /usr/lib/libweston-5.so
	gcc ${CFLAGS} $< ${LDFLAGS} -o $@
