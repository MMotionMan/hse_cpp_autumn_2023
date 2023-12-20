CC=g++
FLAGS= -std=c++20 -Wall -pedantic -Wextra -Wno-unused-variable

test: lab_7_prog

lab_7_prog: tests.o
	$(CC) $(FLAGS)  -lgtest_main -lgtest -lpthread -o lab_7 tests.o
	./lab_7

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o lab_7_prog
	rm lab_7
	rm tests