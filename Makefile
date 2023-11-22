CC := gcc
CFLAGS := -Wall -fPIC -g
SRC_DIR := src
BUILD_DIR := build
LIB_NAME := libso_stdio

# List all source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Derive object files from source files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Set up the main target
$(LIB_NAME).so: $(OBJ_FILES)
	$(CC) -shared -o $@ $^

# Compile each source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# PHONY target to clean up the build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(LIB_NAME).so
