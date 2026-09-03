.DEFAULT_GOAL := build
.DELETE_ON_ERROR:

CC := cc

CPPFLAGS ?=
COMMON_CFLAGS := -std=c17 -Wall -Wextra -Wpedantic
CFLAGS ?= -O0 -g
SAN_CFLAGS ?= -O1 -g
# AddressSanitizer currently hangs with Apple Clang on macOS 26 (LLVM #200447).
# On a supported toolchain, opt in with: make san SANITIZERS=address,undefined
SANITIZERS ?= undefined
SANITIZER_FLAGS := -fsanitize=$(SANITIZERS) \
	-fno-omit-frame-pointer \
	-fno-sanitize-recover=all
LDFLAGS ?=
LDLIBS ?=

BUILD_DIR := build
comma := ,
SANITIZER_TAG := $(subst $(comma),+,$(SANITIZERS))
SAN_BUILD_DIR := $(BUILD_DIR)/san/$(SANITIZER_TAG)

PROGRAM_SOURCES := \
	basics/conways_game_of_life.c \
	basics/hello_world.c \
	basics/prefixed_length_string.c \
	interview-questions/dna-sequence-composition/dna-sequence-composition-basic.c \
	interview-questions/missing-number/missing_number.c \
	interview-questions/network-route-equivalency/network-route-equivalency-basic.c \
	interview-questions/network-route-equivalency/network-route-equivalency-advanced.c

BINARIES := $(patsubst %.c,$(BUILD_DIR)/%,$(PROGRAM_SOURCES))
SAN_BINARIES := $(patsubst %.c,$(SAN_BUILD_DIR)/%,$(PROGRAM_SOURCES))

# Conway's Game of Life is interactive and runs indefinitely, so the automated
# targets compile it but do not execute it.
TEST_BINARIES := $(filter-out $(BUILD_DIR)/basics/conways_game_of_life,$(BINARIES))
SAN_TEST_BINARIES := $(filter-out $(SAN_BUILD_DIR)/basics/conways_game_of_life,$(SAN_BINARIES))

.PHONY: build test san clean

build: $(BINARIES)

test: build
	@set -eu; \
	for binary in $(TEST_BINARIES); do \
		echo "Running $$binary"; \
		"./$$binary"; \
	done

san: $(SAN_BINARIES)
	@set -eu; \
	for binary in $(SAN_TEST_BINARIES); do \
		echo "Running $$binary with $(SANITIZERS) sanitizer(s)"; \
		ASAN_OPTIONS=halt_on_error=1 \
		UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
		"./$$binary"; \
	done

$(BUILD_DIR)/%: %.c
	@mkdir -p "$(@D)"
	$(CC) $(CPPFLAGS) $(COMMON_CFLAGS) $(CFLAGS) "$<" $(LDFLAGS) $(LDLIBS) -o "$@"

$(SAN_BUILD_DIR)/%: %.c
	@mkdir -p "$(@D)"
	$(CC) $(CPPFLAGS) $(COMMON_CFLAGS) $(SAN_CFLAGS) $(SANITIZER_FLAGS) \
		"$<" $(LDFLAGS) $(LDLIBS) -o "$@"

clean:
	$(RM) -r "$(BUILD_DIR)"
