objects = src/types.o src/array.o



create_lib: build $(objects)
	ar r build/algorithms.a $(objects)


build:
	mkdir build

build_debug:
	mkdir -p build/debug

.PHONY: clean test debug 

clean:
	rm -fr ./build $(objects)

test:
	echo

debug: create_lib build_debug
	cc -g -lm debug/debug_main.c build/algorithms.a -o build/debug/debug_main


