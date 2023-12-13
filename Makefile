ARCH := $(shell uname -m)

RIG-$(ARCH): main.c
	gcc -o RIG-$(ARCH) main.c -lpng

clean:
	rm -f RIG-$(ARCH)
	rm -rf out/
