ARCH := $(shell uname -m)

# Cross-compiler prefix (leave empty for native)
CROSS_COMPILE ?=
CC := $(CROSS_COMPILE)gcc

SOURCES := $(wildcard src/*.c)
BUILD_DIR := build/$(ARCH)

OBJECTS := $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SOURCES)) # $(patsubst PATTERN, REPLACEMENT, TEXT_TO_APPLY_PATTERN)
OBJECTS_DBG := $(patsubst src/%.c, $(BUILD_DIR)/%-debug.o, $(SOURCES))

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
	$(CC) -o $@ $(OBJECTS) $(LDLIBS)


$(BUILD_DIR)/%.o: src/%.c | dirs
	@echo -e "$(BUILD_COLOR)[Compiling]$(RESET)\t$<"; \
	$(CC) -c $< -o $@ $(CFLAGS_OPT);


# Debug build
bin/RIG-debug-$(ARCH): $(OBJECTS_DBG) | dirs
	@echo -e "\n$(BUILD_COLOR)[Linking]$(RESET)\t$@"; \
	$(CC) -o $@ $(OBJECTS_DBG) $(LDLIBS);


$(BUILD_DIR)/%-debug.o: src/%.c | dirs
	@echo -e "$(BUILD_COLOR)[Compiling]$(RESET)\t$<"; \
	$(CC) -c $< -o $@ $(CFLAGS_DBG);






debug: BUILD_COLOR := $(ORANGE)
debug: bin/RIG-debug-$(ARCH)


dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p bin

clean:
	@echo -e "$(GREEN)[Cleaning]$(RESET)"
	@rm -rf bin/ build/ out/

