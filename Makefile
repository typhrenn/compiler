CC = gcc
CFLAGS = -Iinclude -Wall
LDFLAGS = -lm

SRC = src/*.c
OUT = compiler

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OUT)

run:
	./${OUT}