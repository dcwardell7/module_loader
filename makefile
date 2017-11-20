ERROR_FLAGS=-Wall -Wextra -Wshadow -Wstrict-aliasing -ansi -pedantic -Werror
CPP_ERROR_FLAGS=${ERROR_FLAGS} -Weffc++

lib: libmodule_loader.a

test: lib libgreeter.so libclass_greeter.so main.o
	g++ test/lib/main.o -Llib -lmodule_loader -ldl -o test/bin/test
	rm test/lib/main.o
	LD_LIBRARY_PATH=test/lib test/bin/test

clean:
	rm -f lib/* test/lib/* test/bin/*

libmodule_loader.a: module_entry.o so_loader.o module_loader.o
	ar rcs lib/libmodule_loader.a lib/module_entry.o lib/so_loader.o lib/module_loader.o
	rm lib/*.o

module_entry.o:
	g++ ${CPP_ERROR_FLAGS} -std=c++14 -O -c src/module_entry.cpp -o lib/module_entry.o

so_loader.o: module_entry.o
	g++ ${CPP_ERROR_FLAGS} -std=c++14 -O -c src/so_loader.cpp -o lib/so_loader.o

module_loader.o: so_loader.o
	g++ ${CPP_ERROR_FLAGS} -std=c++14 -O -Iinclude -c src/module_loader.cpp -o lib/module_loader.o

libgreeter.so:
	gcc ${ERROR_FLAGS} -fPIC -shared test/src/greeter.c -o test/lib/libgreeter.so

libclass_greeter.so:
	g++ ${CPP_ERROR_FLAGS} -std=c++14 -fPIC -shared -Itest/include test/src/class_greeter.cpp -o test/lib/libclass_greeter.so

main.o:
	g++ ${CPP_ERROR_FLAGS} -std=c++14 -O -Iinclude -Itest/include -c test/src/main.cpp -o test/lib/main.o
