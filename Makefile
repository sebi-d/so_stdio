CC := gcc
CFLAGS := -Wall -fPIC
SRC_DIR := src
BUILD_DIR := build
LIB_NAME := libso_stdio

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

$(LIB_NAME).so: $(OBJ_FILES)
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(LIB_NAME).so