CC=g++
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Wno-unused-variable

test: lab_5_prog

lab_5_prog: lab_5.o tests.o
	$(CC) $(FLAGS)  -lgtest_main -lgtest -lpthread -o lab_5 tests.o
	./lab_5

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o lab_5_prog
	rm lab_5
	rm tests