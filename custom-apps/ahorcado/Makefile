# Makefile for ahorcado - NeonBitOS Hangman Game
# Compiles statically for inclusion in minimal Linux distro

CC = gcc
CFLAGS = -Wall -O2 -std=c99
LDFLAGS = -static

TARGET = ahorcado
SOURCE = ahorcado.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)
	@echo "ahorcado compiled successfully (static binary)"
	@echo "Size: $$(du -h $(TARGET) | cut -f1)"
	@echo "Words: 500 palabras en español"

clean:
	rm -f $(TARGET)

.PHONY: all clean test
