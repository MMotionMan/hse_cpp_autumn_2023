CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Wno-unused-variable

test: lab_3_prog

lab_3_prog: lab_3.o tests.o
	$(CC) $(FLAGS)  -lgtest_main -lgtest -lpthread -o lab_3 tests.o
	./lab_3

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o lab_3_prog
	rm lab_3
	rm test