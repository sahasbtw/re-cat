cat program written in C
=========================

Just as a recreational programming session.

**$ ./re-cat Makefile**
```
[Makefile]
CC = gcc
CFLAGS = -Wall -Wextra -Werror --std=c99

re-cat: main.c
	$(CC) $(CFLAGS) main.c -o re-cat
```
