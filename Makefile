# Compiler flags
CC = gcc
CFLAGS = -Iinclude -Wall -O5
LDFLAGS = -lm

SRC = src/main.c $(wildcard src/utils/*.c src/lexer/*.c src/error/*.c src/parameters/*.c)

# Environment and output
OUTDIR = env

ifeq ($(OS),Windows_NT)
    OUT = ${OUTDIR}/compiler.exe
else
    OUT = ${OUTDIR}/compiler
endif

.PHONY: all clean run create_env

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

create_env:
ifeq ($(OS),Windows_NT)
	if not exist $(OUTDIR)\src mkdir $(OUTDIR)\src
	if not exist $(OUTDIR)\include mkdir $(OUTDIR)\include
else
	mkdir -p $(OUTDIR)/src $(OUTDIR)/include
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist $(OUT) del /Q /F $(OUT)
else
	rm -f $(OUT)
endif

run: $(OUT)
ifeq ($(OS),Windows_NT)
	.\$(OUT)
else
	./$(OUT)
endif