CC = gcc

all : window main final

window :
	$(CC) -c -g window.c

main :
	$(CC) -c -g main.c

final :
	$(CC) -o main main.o window.o -lX11

clean :
	rm main main.o window.o