#
# Malicious Direct Connect Client Makefile
#
# David Vargas
# CSCI 4390-01 Senior Project
# Dr. Zhixiang Chen (Senior Project Coordinator)
# Dr. Timothy Wylie (Faculty Advisor)
# University of Texas Rio Grande Valley
#
# Senior Project
# Due 12/12/18
#

CC = gcc
CFLAGS = -Wall -I./include/

RM = rm
RFLAGS = -f

LIBS = -lpcre

OBJ = ./bin/main.o ./bin/client.o ./bin/protocol.o

all: myrkur
	@echo "Built Malicious Client"

myrkur: main.o client.o protocol.o
	$(CC) $(CFLAGS) $(OBJ) -o ./bin/myrkur $(LIBS)

main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o ./bin/main.o

client.o: ./src/client.c
	$(CC) $(CFLAGS) -c ./src/client.c -o ./bin/client.o

protocol.o: ./src/protocol.c
	$(CC) $(CFLAGS) -c ./src/protocol.c -o ./bin/protocol.o

clean:
	$(RM) $(RFLAGS) ./bin/*.o
	$(RM) $(RFLAGS) ./bin/myrkur
