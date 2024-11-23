.PHONY: clean

compiler: $(shell find src -type f -iname '*.c')
	gcc -Iinclude -o $@ $^
	
clean:
	rm compiler
