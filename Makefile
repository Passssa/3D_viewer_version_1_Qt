CC= gcc
CFLAGS= -Wall -Werror -Wextra
SOURCES= *.c
OBJECTS=$(SOURCES:.c=.o)
OS= $(shell uname)
TEST_FILES= tests/*.c
PROJECT_NAME= 3DViewer_1_0

ifeq ($(OS), Darwin)
	TEST_FLAGS=-lcheck
else
	TEST_FLAGS=-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
endif

all: uninstall install gcov_report dvi dist

install: recreate_build_dir
	cd view && qmake6 && make && make clean && rm Makefile && cd ../ && mv view/$(PROJECT_NAME) build/

uninstall:
	rm -rf build

test: clean $(PROJECT_NAME).a
	$(CC) $(CFLAGS)  $(SOURCES) $(TEST_FILES) -o test -g $(TEST_FLAGS)
	@./test

add_coverage_flag:
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage_flag tests
	$(CC) $(CFLAGS)  $(SOURCES) $(TEST_FILES) -o test -g $(TEST_FLAGS)
	./test
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info
	
ifeq ($(OS), Darwin)
	open report/index.html
else
	open ./report/index.html
endif

clean:
	rm -rf *.a *.so *.out *.o report *.gc* *.info *.txt test *.gch *.pdf *.tar view/*.o
	rm -rf  *.html *.css test.info test.dSYM report

dvi:
	open view/dvi.html

dist:
	rm -rf dist.tar
	tar  -cvzf dist.tar build/$(PROJECT_NAME)

$(PROJECT_NAME).a: clean
	$(CC) $(CFLAGS) $(SOURCES) -c 
	ar rc $(PROJECT_NAME).a *.o
	ranlib $(PROJECT_NAME).a

recreate_build_dir:
	rm -rf build
	mkdir build

rebuild:
	make clean
	make all

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SOURCES) *.c *.h
ifeq ($(OS), Darwin)
	leaks --atExit -- ./test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif

linter:
	cp linters/.clang-format ./
	clang-format -i *.c *.h
	clang-format -i view/*.cpp  *.h
	rm -rf .clang-format

push: clean linter
	git fetch
	git add .
	git commit -m "$(c)"
	git push origin "$(b)"