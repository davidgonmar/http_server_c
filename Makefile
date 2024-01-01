CC=gcc
CFLAGS=-Wall
SRCFILES = $(wildcard *.c)
BIN_DIR=bin
HEADERS = $(wildcard *.h)

.PHONY: all format

server:
	$(CC) $(SRCFILES) -DCURRENT_LOG_LEVEL=LOG_LEVEL_INFO -o $(BIN_DIR)/test && $(BIN_DIR)/test

format:
	clang-format -i $(SRCFILES) $(HEADERS)