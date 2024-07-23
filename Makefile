CC = gcc
CFLAGS = -Wall -I./src

# 빌드 디렉토리
BUILD_DIR = ./build

# 소스 디렉토리
SRC_DIR = ./src

# 소스 파일들
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.c)

# 오브젝트 파일들
OBJ_FILES = $(patsubst $(SRC_DIR)/%/%.c, $(BUILD_DIR)/%-%.o, $(SRC_FILES))

# 타겟 실행 파일
TARGET = main

all: $(BUILD_DIR) $(OBJ_FILES) $(TARGET)

# 빌드 디렉토리 생성
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 타겟 실행 파일 빌드
$(TARGET): $(OBJ_FILES) $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(BUILD_DIR)/main.o

# 오브젝트 파일 빌드
$(BUILD_DIR)/%-%.o: $(SRC_DIR)/%/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
