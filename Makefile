ARCH := $(shell uname -m)
SOURCES := $(wildcard src/*.c)


bin/RIG-$(ARCH): src/*.?
	mkdir -p bin
	gcc -o bin/RIG-$(ARCH) src/*.c -Ofast -lpng -ljpeg


clean:
	rm -f RIG-$(ARCH)
	rm -f bin/*
	rm -rf out/
