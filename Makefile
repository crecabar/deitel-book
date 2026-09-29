CC      := cc
CFLAGS  := -std=c17 -Wall -Wextra -Wpedantic -Werror
BUILD   := build

LAUNCHER := $(BUILD)/deitel

.PHONY: all clean

all: $(LAUNCHER) $(BUILD)/chapter_06/06_38_string_reverse

$(LAUNCHER): launcher/main.c launcher/exercise.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/chapter_06/06_38_string_reverse: src/chapter_06/06_38_string_reverse.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD)

