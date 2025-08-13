ARCH := $(shell uname -m)
SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, build/%.o, $(SOURCES)) # $(patsubst PATTERN, REPLACEMENT, TEXT_TO_APPLY_PATTERN)
OBJECTS_DBG := $(patsubst src/%.c, build/%-debug.o, $(SOURCES))

CFLAGS :=
CFLAGS_OPT := $(CFLAGS) -Ofast
CFLAGS_DBG := $(CFLAGS) -Og -g -Wall -Wextra
LDLIBS := -lm -pthread


# Colors
GREEN := \033[0;32m
BLUE := \033[0;34m
CYAN := \033[0;36m
RESET := \033[0m
RED := \033[31m
ORANGE := \033[38;5;208m

BUILD_COLOR := $(CYAN)

.PHONY: dirs clean debug

# Release build
bin/RIG-$(ARCH): $(OBJECTS) | dirs
	@echo -e "\n$(BUILD_COLOR)[Linking]$(RESET)\t$@"; \
	gcc -o $@ $(OBJECTS) $(LDLIBS)


build/%.o: src/%.c | dirs
	@echo -e "$(BUILD_COLOR)[Compiling]$(RESET)\t$<"; \
	gcc -c $< -o $@ $(CFLAGS_OPT);


# Debug build
bin/RIG-debug-$(ARCH): $(OBJECTS_DBG) | dirs
	@echo -e "\n$(BUILD_COLOR)[Linking]$(RESET)\t$@"; \
	gcc -o $@ $(OBJECTS_DBG) $(LDLIBS);


build/%-debug.o: src/%.c | dirs
	@echo -e "$(BUILD_COLOR)[Compiling]$(RESET)\t$<"; \
	gcc -c $< -o $@ $(CFLAGS_DBG);






debug: BUILD_COLOR := $(ORANGE)
debug: bin/RIG-debug-$(ARCH)


dirs:
	@mkdir -p build
	@mkdir -p bin

clean:
	@echo -e "$(GREEN)[Cleaning]$(RESET)"
	@rm -rf bin/ build/ out/

