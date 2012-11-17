#
# Vladimir Tsoy & Jordan Harmel 
# CS 470
#
# Makefile for Traveling Salesperson
#

CC=gcc
CFLAGS=-g -Wall -std=gnu99
LDFLAGS=-fopenmp

all: tsp stack list

tsp: stack list tsp.c tsp.h
	$(CC) -o tsp stack.o $(CFLAGS) $(LDFLAGS) tsp.c

stack: stack.c tsp.h
	$(CC) -c -o stack.o $(CFLAGS) stack.c

list: list.c tsp.h
	$(CC) -c -o list.o $(CFLAGS) list.c
clean:
	$(RM) tsp *.o
	$(RM) -rf *.dSYM
