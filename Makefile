ARCH := $(shell uname -m)
SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, build/%.o, $(SOURCES)) # $(patsubst PATTERN, REPLACEMENT, TEXT_TO_APPLY_PATTERN)

# Colors
GREEN := \033[0;32m
BLUE := \033[0;34m
CYAN := \033[0;36m
RESET := \033[0m

.PHONY: dirs clean

bin/RIG-$(ARCH): $(OBJECTS) | dirs
	@echo -e "\n$(CYAN)[Linking]$(RESET)\t$@"; \
	gcc -o $@ $(OBJECTS) -Ofast -lpng -ljpeg; \




build/%.o: src/%.c | dirs
	@echo -e "$(CYAN)[Compiling]$(RESET)\t$<"; \
	gcc -c $< -o $@ -Ofast; \

dirs:
	@mkdir -p build
	@mkdir -p bin

clean:
	@echo -e "$(GREEN)[Cleaning]$(RESET)"
	@rm -rf bin/ build/ out/

