CFLAGS = -Wall -Werror -g
CCOC = -fprofile-arcs -ftest-coverage  
 
all: main

test1:
	./main < test1.txt

test2:
	./main < test2.txt

test3:
	./main < test3.txt

main: qsort.o
	gcc $(CCOC) $(CFLAGS) qsort.c -o main

qsort.o: qsort.c
	gcc $(CCOC) $(CFLAGS) -c qsort.c

coverage:
	lcov -t "main" -o coverage.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report coverage.info --rc lcov_branch_coverage=1

clean:
	rm -rf *.o main

