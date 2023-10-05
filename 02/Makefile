CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Wno-unused-variable

test: lab_2_prog

lab_2_prog: lab_2.o tests.o
	$(CC) $(FLAGS)  -lgtest_main -lgtest -lpthread -o lab_2 tests.o
	./lab_2

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o lab_2_prog
	rm lab_2