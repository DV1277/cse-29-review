# Which compiler to use
CC = gcc
# Compiler flags
CFLAGS = -g -std=gnu99

%_list: %_list.c linked_list.o
	$(CC) $(CFLAGS) -o $@ $^

%: %.c
	$(CC) $(CFLAGS) -o $@ $<
