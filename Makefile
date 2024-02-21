ARCH := $(shell uname -m)
LIBPNG_CFLAGS := $(shell pkg-config --cflags libpng)
LIBPNG_LDFLAGS := $(shell pkg-config --libs libpng)

RIG-$(ARCH): main.c PNG_generator.c progressbar.c my_utils.c dir_creator.c
	gcc -o RIG-$(ARCH) main.c -lpng $(LIBPNG_CFLAGS) $(LIBPNG_LDFLAGS)


clean:
	rm -f RIG-$(ARCH)
	rm -rf out/
