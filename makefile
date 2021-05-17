cc			= /usr/bin/clang
CFLAGS		= -Wall -ansi -pedantic -g
SHELL		= /bin/bash
SRC_DIR 	= src
OUT_DIR 	= out
OBJ_DIR 	= $(OUT_DIR)/obj
BIN_DIR 	= $(OUT_DIR)/bin
PROGRAM 	= myText.out
TARGET		= $(BIN_DIR)/$(PROGRAM)

HEADERS 	= $(wildcard $(SRC_DIR)/*.h)
SOURCES 	= $(wildcard $(SRC_DIR)/*.c)
OBJECTS		= $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
.PHONY: all clean

all: $(OUT_DIR) $(TARGET)

$(OUT_DIR): $(BIN_DIR) $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OUT_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -rf $(OUT_DIR)