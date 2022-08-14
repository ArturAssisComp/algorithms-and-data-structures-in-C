objects = src/types.o src/array.o



create_lib: build $(objects)
	ar r build/algorithms.a $(objects)


build:
	mkdir build

build_debug:
	mkdir -p build/debug

.PHONY: clean test debug valgrind

clean:
	rm -fr ./build $(objects)

test:
	echo

debug: create_lib build_debug
	cc -g -lm debug/debug_main.c build/algorithms.a -o build/debug/debug_main

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=build/debug/valgrind-out.txt ./build/debug/debug_main


