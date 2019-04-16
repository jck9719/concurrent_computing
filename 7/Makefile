CC = gcc

all : engine main final

engine :
	$(CC) -c -g engine.c

main :
	$(CC) -c -g main.c

final :
	$(CC) -o main main.o engine.o

clean :
	rm main main.o engine.o