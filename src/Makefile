CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g -pedantic
GCOVFLAGS = -fprofile-arcs -ftest-coverage
FILES =$(wildcard *.c)
UNAME_S=$(shell uname -s)
APP = build/s21_SmartCalc.app

ifeq ($(UNAME_S),Linux)
LDFLAGS= -lm -lcheck -lpthread -lsubunit
endif
ifeq ($(UNAME_S),Darwin)
LDFLAGS= -lm -lcheck -lpthread
endif

all: uninstall test gcov_report install

test:
	$(CC) $(CFLAGS) $(FILES) -o tests -lgcov --coverage $(LDFLAGS) 
	./tests



gcov_report: 
	$(CC) $(GCOVFLAGS) $(FILES) $(LDFLAGS) -o tests -lcheck
	./tests
	lcov -t tests -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index-sort-f.html


install: uninstall
	@mkdir build
	@cd build/ && qmake  ../s21_SmartCalc/s21_SmartCalc.pro && make
	@mkdir $(HOME)/Desktop/s21_SmartCalc/
	@cp -rf $(APP) $(HOME)/Desktop/s21_SmartCalc
	@make clean

uninstall:
	rm -rf build
	make clean

dvi:
	open README.html

dist: install
	tar -czf s21_SmartCalc.tar.gz --directory=s21_SmartCalc/ .

style:
	clang-format -style=google -i *.c *.h
	clang-format -style=google -i s21_SmartCalc/*.h s21_SmartCalc/*.cpp
	clang-format -style=google -n *.c *.h
	clang-format -style=google -n s21_SmartCalc/*.h s21_SmartCalc/*.cpp

clean:
	rm -rf obj *.a test html_report report.info program *.o *.gch *.gch *.gcno *.gcda s21_SmartCalc.tar.gz
	

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov


lib:
	$(CC) -c $(SOURCES) $(LDFLAGS)
	ar -rc libcalc.a *.o
	ranlib libcalc.a

.PHONY: all test clean lib gcov_report

