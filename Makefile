ARCH := $(shell uname -m)
LIBPNG_CFLAGS := $(shell pkg-config --cflags libpng)
LIBPNG_LDFLAGS := $(shell pkg-config --libs libpng)

RIG-$(ARCH): main.? PNG_generator.? JPEG_generator.? progressbar.? my_utils.? dir_creator.?
	gcc -o RIG-$(ARCH) main.c PNG_generator.c JPEG_generator.c dir_creator.c my_utils.c progressbar.c -Ofast -lpng -ljpeg $(LIBPNG_CFLAGS) $(LIBPNG_LDFLAGS)


clean:
	rm -f RIG-$(ARCH)
	rm -rf out/
