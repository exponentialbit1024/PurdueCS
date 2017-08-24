
CC = gcc

CFLAGS = --std=gnu11 -Wall 

all: git-commit MyMalloc.so test0 test1-1 test1-2 test1-3 test1-4 test1 test2 test3 test4 test5 test6 test7 test8 test9 test10

MyMalloc.so: MyMalloc.c
	$(CC) $(CFLAGS) -fPIC -c -g MyMalloc.c
	gcc -shared -o MyMalloc.so MyMalloc.o

test0: test0.c MyMalloc.c
	$(CC) $(CFLAGS) -o test0 test0.c MyMalloc.c

test1-1: test1-1.c MyMalloc.c
	$(CC) $(CFLAGS) -o test1-1 test1-1.c MyMalloc.c

test1-2: test1-2.c MyMalloc.c
	$(CC) $(CFLAGS) -o test1-2 test1-2.c MyMalloc.c

test1-3: test1-3.c MyMalloc.c
	$(CC) $(CFLAGS) -o test1-3 test1-3.c MyMalloc.c

test1-4: test1-4.c MyMalloc.c
	$(CC) $(CFLAGS) -o test1-4 test1-4.c MyMalloc.c

test1: test1.c MyMalloc.c
	$(CC) $(CFLAGS) -o test1 test1.c MyMalloc.c

test2: test2.c MyMalloc.c
	$(CC) $(CFLAGS) -o test2 test2.c MyMalloc.c

test3: test3.c MyMalloc.c
	$(CC) $(CFLAGS) -o test3 test3.c MyMalloc.c

test4: test4.c MyMalloc.c
	$(CC) $(CFLAGS) -o test4 test4.c MyMalloc.c

test5: test5.c MyMalloc.c
	$(CC) $(CFLAGS) -o test5 test5.c MyMalloc.c 

test6: test6.c MyMalloc.c
	$(CC) $(CFLAGS) -o test6 test6.c MyMalloc.c

test7: test7.c MyMalloc.so
	$(CC) $(CFLAGS) -o test7 test7.c MyMalloc.c

test8: test8.c MyMalloc.so
	$(CC) $(CFLAGS) -o test8 test8.c MyMalloc.c

test9: test9.c MyMalloc.so
	$(CC) $(CFLAGS) -o test9 test9.c MyMalloc.c -lpthread

test10: test10.c MyMalloc.so
	$(CC) $(CFLAGS) -o test10 test10.c MyMalloc.c

runtestEXTRA:
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:`pwd` && export LD_LIBRARY_PATH && \
	echo "--- Running testEXTRA ---" && \
    ./firefox

git-commit:
	git add *.c *.h Makefile >> .local.git.out  || echo
	git add *.txt 2>/dev/null >> .local.git.out  || echo
	git commit -a -m 'Commit' >> .local.git.out || echo
	git push

clean:
	rm -f *.o test0 test1 test1-1 test1-2 test1-3 test1-4 test2 test3 test4 test5 test6 test7 test8 test9 test10 MyMalloc.so core a.out *.out *.txt

