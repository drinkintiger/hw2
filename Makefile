#
# Vladimir Tsoy & Jordan Harmel 
# CS 470
#
# Makefile for Traveling Salesperson
#

CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-fopenmp

all: tsp

tsp: tsp.c
	$(CC) -o tsp $(CFLAGS) $(LDFLAGS) tsp.c

clean:
	$(RM) tsp *.o
	$(RM) -rf *.dSYM