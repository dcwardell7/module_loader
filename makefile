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
	g++ -std=c++14 -O -c src/module_entry.cpp -o lib/module_entry.o

so_loader.o: module_entry.o
	g++ -std=c++14 -O -c src/so_loader.cpp -o lib/so_loader.o

module_loader.o: so_loader.o
	g++ -std=c++14 -O -Iinclude -c src/module_loader.cpp -o lib/module_loader.o

libgreeter.so:
	gcc -fPIC -Wall -Werror -Wextra -pedantic test/src/greeter.c -shared -o test/lib/libgreeter.so

libclass_greeter.so:
	g++ -std=c++14 -fPIC -Wall -Werror -Wextra -pedantic -Itest/include test/src/class_greeter.cpp -shared -o test/lib/libclass_greeter.so

main.o:
	g++ -std=c++14 -O -Iinclude -Itest/include -c test/src/main.cpp -o test/lib/main.o
