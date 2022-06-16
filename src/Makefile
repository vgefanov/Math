CC = gcc
#  -Wno-missing-braces
CFLAGS =-Wall -Wextra -Werror -pedantic -std=c11 -lm
CFLAGS_GCOV =-fprofile-arcs -ftest-coverage
CFLAGS_TEST =-Wall -Wextra -Werror -pedantic -std=c11 -lm -lcheck -lpthread

BUILD_DIR = .
OUTFILE = s21_math
OUTFILE_TEST = $(OUTFILE)_test

SOURCES = $(OUTFILE).c
SOURCES_TEST = $(OUTFILE_TEST).c


# all, clean, test, s21_math.a, gcov_report

all: s21_math.a test

clean:
	rm -rf ./lcov_report
	rm *.o *.a *.gcno *.gcda *.gcov *.info $(BUILD_DIR)/$(OUTFILE_TEST)

test:
	$(CC) $(CFLAGS_TEST) $(SOURCES) $(SOURCES_TEST) -o $(BUILD_DIR)/$(OUTFILE_TEST)
	$(BUILD_DIR)/$(OUTFILE_TEST)

s21_math.a:
	$(CC) $(CFLAGS) -c $(SOURCES) -o $(OUTFILE).o
	ar rc $(OUTFILE).a $(OUTFILE).o

gcov_report:
	$(CC) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(SOURCES) $(SOURCES_TEST) -o $(BUILD_DIR)/$(OUTFILE_TEST)
	$(BUILD_DIR)/$(OUTFILE_TEST)
	gcov $(OUTFILE)
	gcov -f $(OUTFILE).gcda
	lcov --capture --directory . --output-file main_coverage.info
	genhtml main_coverage.info --output-directory lcov_report


# checks

check_all: style check leaks

style:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

leaks: test
	CK_FORK=no leaks --atExit -- $(BUILD_DIR)/$(OUTFILE_TEST)


# service

debug:
	$(CC) $(CFLAGS_TEST) -g $(SOURCES) $(SOURCES_TEST) -o $(BUILD_DIR)/$(OUTFILE_TEST)

brew:
	# cd ~/goinfre
	# git clone https://github.com/Homebrew/brew homebrew
	# eval "$(~/goinfre/homebrew/bin/brew shellenv)"

lcov:
	brew install lcov

valgrind_install:
	brew tap LouisBrunner/valgrind
	brew install --HEAD LouisBrunner/valgrind/valgrind

valgrind:
	valgrind ./$(OUTFILE_TEST) --leak-check=full