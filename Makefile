CC      := cc
CFLAGS  := -std=c17 -Wall -Wextra -Wpedantic -Werror
BUILD   := build

LAUNCHER := $(BUILD)/deitel

EXERCISE_SOURCES := $(wildcard src/chapter_*/*.c)
EXERCISES := $(patsubst src/%.c,$(BUILD)/%,$(EXERCISE_SOURCES))

CATALOG := $(BUILD)/exercises.inc

.PHONY: all clean

all: $(LAUNCHER) $(EXERCISES)

$(LAUNCHER): launcher/main.c launcher/exercise.h $(CATALOG)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(BUILD) launcher/main.c -o $@

$(BUILD)/%: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(CATALOG): $(EXERCISE_SOURCES) scripts/generate_catalog.sh
	@mkdir -p $(dir $@)
	@./scripts/generate_catalog.sh $(EXERCISE_SOURCES) > $@

clean:
	rm -rf $(BUILD)
