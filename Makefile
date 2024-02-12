ARCH := $(shell uname -m)
LIBPNG_CFLAGS := $(shell pkg-config --cflags libpng)
LIBPNG_LDFLAGS := $(shell pkg-config --libs libpng)

RIG-$(ARCH): main.c
	gcc -o RIG-$(ARCH) main.c $(LIBPNG_CFLAGS) $(LIBPNG_LDFLAGS)

clean:
	rm -f RIG-$(ARCH)
	rm -rf out/
