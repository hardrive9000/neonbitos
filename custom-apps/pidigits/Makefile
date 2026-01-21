# Makefile for pidigits - NeonBitOS Pi Calculator
# Compiles statically for inclusion in minimal Linux distro

CC = gcc
CFLAGS = -Wall -O2 -std=c99
LDFLAGS = -static -lm

TARGET = pidigits
SOURCE = pidigits.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)
	@echo "pidigits compiled successfully (static binary)"
	@echo "Size: $$(du -h $(TARGET) | cut -f1)"

clean:
	rm -f $(TARGET)

.PHONY: all clean
