.PHONY: clean

compiler: $(wildcard src/*.c)
	g++ -Iinclude -o $@ $^
	
clean:
	rm compiler
