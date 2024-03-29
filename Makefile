BIN = mcp9600

BUILD_DIR = build
DEBUG_DIR = debug

SOURCES =	main.c \
			src/mcp9600-driver.c \
			interface/mcp9600-interface.c \
			platform/linux/i2c.c

CC = gcc
CFLAGS = -Wall -Wextra -O2
LIBS = -li2c
INCLUDE_DIR =	-Iinterface/ \
				-Iplatform/linux/ \
				-Isrc/

OUTPUT = $(BUILD_DIR)/$(BIN)
DEBUG_OUTPUT = $(DEBUG_DIR)/$(BIN)

all:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT) $(LIBS) $(INCLUDE_DIR)

debug:
	mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) -g -ggdb3 $(SOURCES) -o $(DEBUG_OUTPUT) $(LIBS)

clean:
	rm -rf $(BUILD_DIR) $(DEBUG_DIR)
