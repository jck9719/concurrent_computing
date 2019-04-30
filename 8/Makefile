CC = gcc

all : handler main final

handler :
	$(CC) -c -g handler.c

main :
	$(CC) -c -g main.c

final :
	$(CC) -o main main.o handler.o

clean :
	rm main main.o handler.o