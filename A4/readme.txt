Name: Scott Giorlando
Partner: Zachary Palmer
Assignment: Tombstones
Submission: 1

What works and what doesn't:

NOTE: Test case 3 is the test file given to us on Blackboard.  So to run just do ./test3

So we did a slight change since Dr. Wilkes' test file wasn't working fully, it does now though with this submission.
Program is working fully with three fleshed out test cases.

Running Instructions:

  1.) type "make trial1" or "make trial2" or "make trial3" this will make and run each test


Output on those tests:

[PATH]# make trial1
rm test1.o test2.o test3.o  *~ *.gch -rf test1 test2 test3
g++    -c -o test1.o test1.cpp
g++ test1.o -o test1
g++    -c -o test2.o test2.cpp
g++ test2.o -o test2
g++    -c -o test3.o test3.cpp
g++ test3.o -o test3
./test1
Test successful.

[PATH]# make trial2
rm test1.o test2.o test3.o  *~ *.gch -rf test1 test2 test3
g++    -c -o test1.o test1.cpp
g++ test1.o -o test1
g++    -c -o test2.o test2.cpp
g++ test2.o -o test2
g++    -c -o test3.o test3.cpp
g++ test3.o -o test3
./test2
Exception - [Dangling]
Makefile:22: recipe for target 'trial2' failed
make: *** [trial2] Error 1
[PATH]# make trial3

rm test1.o test2.o test3.o  *~ *.gch -rf test1 test2 test3
g++    -c -o test1.o test1.cpp
g++ test1.o -o test1
g++    -c -o test2.o test2.cpp
g++ test2.o -o test2
g++    -c -o test3.o test3.cpp
g++ test3.o -o test3
./test3
Exception - [Dangling]
Makefile:25: recipe for target 'trial3' failed
make: *** [trial3] Error 1
