CC = gcc
CFLAGS = -Iinclude -Wall
LDFLAGS = -lm

SRC = src/main.c src/utils/*.c src/lexer/*.c src/error/*.c
OUT = compiler

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OUT)

run:
	./${OUT}