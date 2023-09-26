CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Wno-unused-variable

test: lab_1_prog

lab_1_prog: lab_1.o tests.o
	$(CC) $(FLAGS)  -lgtest_main -lgtest -lpthread -o lab_1 tests.o
	./lab_1

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o lab_1_prog
	rm lab_1