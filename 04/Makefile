CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Wno-unused-variable

test: lab_4_prog

lab_4_prog: lab_4.o tests.o
	$(CC) $(FLAGS)  -lgtest_main -lgtest -lpthread -o lab_4 tests.o
	./lab_4

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o lab_4_prog
	rm lab_4
	rm tests