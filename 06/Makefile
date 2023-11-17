CC=g++
FLAGS= -std=c++20 -Wall -pedantic -Wextra -Wno-unused-variable

test: lab_6_prog

lab_6_prog: tests.o
	$(CC) $(FLAGS)  -lgtest_main -lgtest -lpthread -o lab_6 tests.o
	./lab_6

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

clean:
	rm -rf *.o lab_6_prog
	rm lab_6
	rm tests