#***********************************************
#CopyRight Reserved
#Author: Vinson
#***********************************************
CC = gcc

test: test.o
	$(CC) -o test test.o
#	this cmd will not print out
	@echo "what is wildcard"
#	this cmd will print out
#	echo "what is wildcard"
	echo $(wildcard cfe)
ifneq ($(wildcard cfe), )
	@echo "hello there"
endif

test.o: test.c
	$(CC) -c test.c

clean: 
	-rm -f test *.o
