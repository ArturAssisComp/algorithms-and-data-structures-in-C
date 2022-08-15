objects = src/types.o src/array.o
ctest_files = ext/ctest_lib/lib/ctest.a ext/ctest_lib/include/ctest.h  ext/ctest_lib/include/ctest_functions.h ext/ctest_lib/include/globals.h ext/ctest_lib/include/assert.h ext/ctest_lib/include/std_assert_macro.h
ctest_a = ext/ctest_lib/lib/ctest.a



create_lib: build $(objects)
	ar r build/algorithms.a $(objects)


build:
	mkdir build

build_debug: build
	mkdir -p build/debug

build_test: build
	mkdir -p build/test

.PHONY: install

install: build_test
	cd build/test; git clone https://github.com/ArturAssisComp/ctest.git; 
	cd build/test/ctest; git checkout version1_0; make
	cd build/test/ctest/build/ctest_lib/include; mv ctest.h ctest_functions.h globals.h assert.h std_assert_macros.h ../../../../../../ext/ctest_lib/include
	mv build/test/ctest/build/ctest_lib/lib/ctest.a ext/ctest_lib/lib
	rm -fr build/test/ctest

.PHONY: clean test debug valgrind

clean:
	rm -fr ./build $(objects)

test: $(objects)
	 
	objcopy --redefine-sym T_is_equal=_T_is_equal src/types.o
	objcopy --redefine-sym T_free_element=_T_free_element src/types.o
	objcopy --redefine-sym A_create_array=_A_create_array src/types.o
	objcopy --redefine-sym A_delete_array=_A_delete_array src/types.o
	objcopy --redefine-sym A_create_array=_A_create_array src/array.o
	objcopy --redefine-sym A_delete_array=_A_delete_array src/array.o
	cc -g -lm -o build/test/test_basic_types test/test_basic_types.c $(ctest_a) $(objects)


debug: create_lib build_debug
	cc -g -lm debug/debug_main.c build/algorithms.a -o build/debug/debug_main

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=build/debug/valgrind-out.txt ./build/debug/debug_main


