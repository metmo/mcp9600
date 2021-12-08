BIN = mcp9600

BUILD_DIR = build

SOURCES = main.c src/mcp9600-driver.c

INCLUDE_DIR = lib

OUTPUT = $(BUILD_DIR)/$(BIN)
all:
	mkdir -p build
	$(CC) -g -ggdb3 -li2c -I$(INCLUDE_DIR) $(SOURCES) -o $(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)
