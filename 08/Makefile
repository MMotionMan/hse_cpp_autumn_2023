.DEFAULT_GOAL := install

all: install test

install: utils.c
	python setup.py install

test:
	./main.py
