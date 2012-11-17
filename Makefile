#
# Vladimir Tsoy & Jordan Harmel 
# CS 470
#
# Makefile for Traveling Salesperson
#

CC=gcc
CFLAGS=-g -Wall -std=gnu99
LDFLAGS=-fopenmp

all: tsp stack

tsp: stack tsp.c tsp.h
	$(CC) -o tsp stack.o $(CFLAGS) $(LDFLAGS) tsp.c

stack: stack.c tsp.h
	$(CC) -c -o stack.o $(CFLAGS) stack.c

clean:
	$(RM) tsp *.o
	$(RM) -rf *.dSYM
