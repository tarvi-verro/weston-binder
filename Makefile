
WESTON_VERSION=$(shell pkg-config --modversion weston | cut -d '.' -f 1)
LIBWESTON_MOD=libweston-$(WESTON_VERSION)
LIBWESTON_LIBPREFIX=$(shell pkg-config --variable=libdir $(LIBWESTON_MOD))

CFLAGS:=$(shell pkg-config --cflags weston $(LIBWESTON_MOD)) \
	$(shell pkg-config --cflags libevdev) \
	 -fPIC -Wall

LDFLAGS:=-shared $(shell pkg-config --libs $(LIBWESTON_MOD))

binder.so: binder.c Makefile $(LIBWESTON_LIBPREFIX)/$(LIBWESTON_MOD).so
	gcc ${CFLAGS} $< ${LDFLAGS} -o $@
