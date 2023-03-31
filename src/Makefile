CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TST_LIBS = -lcheck #$(shell pkg-config --cflags --libs check)
ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt -lsubunit -lm
endif
LIB_NAME = s21_decimal

SRCS=$(wildcard s21_*.c)
OBJS=$(SRCS:.c=.o)
SRCS2=test_main.c $(wildcard tests/*.c)
OBJS2=$(SRCS2:.c=.o)

all: clean test

rebuild: all

clean:
	rm -rf *.o test *.a *.gcno *.gcda *.gcov \
	*.html *.css *.info main/*.o desperos \
	sallieam fartlouv jeannakr test.dSYM \
	tests/*.o tests/*/*.o tests/*/*/*.o \
	tests/*/*/*/*.o s21_decimal.a

clang-format:
	clang-format -n -style=Google *.c *.h tests/*.c tests/*.h
	
set-style-google:
	clang-format -i -style=Google *.c *.h tests/*.c tests/*.h

%.o: %.c
	$(CC) $(FLAGS) $(DEBUG) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o

test: clean $(LIB_NAME).a
	$(CC) $(FLAGS) -g $(SRCS2) $(LIB_NAME).a $(TST_LIBS) -o test
	./test

add_coverage_flag:
	$(eval FLAGS += --coverage)

gcov_report:  add_coverage_flag test
	./test
	rm -rf test*.gcda test*.gcno
	lcov -t “gcov_test” -o test.info --rc lcov_branch_coverage=1 --no-external -c -d .
	genhtml -o report_make/ test.info --rc lcov_branch_coverage=1
	open ./report_make/index.html