cc			= /usr/bin/gcc
CFLAGS		= -wall -Werror -Wextra -O3
SHELL		= /bin/bash
SRC_DIR 	= src
OUT_DIR 	= out
OBJ_DIR 	= $(OUT_DIR)/obj
BIN_DIR 	= $(OUT_DIR)/bin
PROGRAM 	= rb_4b_server.out
TARGET		= $(BIN_DIR)/$(PROGRAM)

HEADERS 	= $(wildcard $(SRC_DIR)/*.h)
SOURCES 	= $(wildcard $(SRC_DIR)/*.c)

.PHONY: all clean




clean:
	rm -rf $(OUT_DIR)