CC = gcc
CFLAGS = -Wall -I./src

BUILD_DIR = ./build

SRC_DIR = ./src

SRC_FILES = $(wildcard $(SRC_DIR)/**/*.c)

OBJ_FILES = $(patsubst $(SRC_DIR)/%/%.c, $(BUILD_DIR)/%-%.o, $(SRC_FILES))

TARGET = $(BUILD_DIR)/main

all: $(BUILD_DIR) $(OBJ_FILES) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJ_FILES) $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(BUILD_DIR)/main.o

$(BUILD_DIR)/%-%.o: $(SRC_DIR)/%/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
