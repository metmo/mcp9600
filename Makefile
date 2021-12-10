BIN = mcp9600

BUILD_DIR = build

SOURCES = main.c src/mcp9600-driver.c

INCLUDE_DIR = 

OUTPUT = $(BUILD_DIR)/$(BIN)
all:
	mkdir -p build
	$(CC) -g -ggdb3 -li2c $(SOURCES) -o $(OUTPUT) -Wall -Wextra

clean:
	rm -rf $(BUILD_DIR)
