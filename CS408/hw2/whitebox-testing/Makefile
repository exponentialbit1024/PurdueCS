CFLAGS=-Wall -g -pedantic -fstack-protector-all
LDFLAGS=-fprofile-arcs -ftest-coverage
CC=gcc
meow: main.o meow.o array.o hashtable.o
main.o: main.c
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c -o $@ $<
clean:
	$(RM) main.o main.gcda main.gcno meow.o array.o hashtable.o meow
cov-clean:
	$(RM) main.gcda
