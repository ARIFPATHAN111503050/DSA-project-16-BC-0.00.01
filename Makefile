all:
	cc -c -g main.c token.c stack.c function.c
	cc -g main.o token.o stack.o function.o -o project -lm

