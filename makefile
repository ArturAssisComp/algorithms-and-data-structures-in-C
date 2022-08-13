objects = src/types.o src/array.o



create_lib: build $(objects)
	ar r build/algorithms.a $(objects)

build:
	mkdir build


.PHONY: clean test debug 

clean:
	rm -fr ./build

test:
	echo

debug: create_lib
	echo


