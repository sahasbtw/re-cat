CC = gcc
CFLAGS = -Wall -Wextra -Werror --std=c99

re-cat: main.c
	$(CC) $(CFLAGS) main.c -o re-cat
