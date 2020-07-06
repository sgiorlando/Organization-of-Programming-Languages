all: test1 test2 test3

test1: test1.o tombstones.h
	g++ test1.o -o test1

test1.o: test1.cpp

test2: test2.o tombstones.h
	g++ test2.o -o test2

test2.o: test2.cpp

test3: A4-tests.o tombstones.h
	g++ A4-tests.o -o test3

A4-tests.o: A4-tests.cpp

trial1: clean all
	./test1

trial2: clean all
	./test2

trial3: clean all
	./A4-tests


clean:
	rm test1.o test2.o A4-tests.o  *~ *.gch -rf test1 test2 test3
