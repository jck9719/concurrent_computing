#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

#define CLIENT 123
#define SERVER 321
#define WORD_SIZE 256

typedef struct message_t
{
    long type;
    char word[WORD_SIZE];
} message;

int main(int argc, char **argv)
{
    int client_queue = msgget (CLIENT, 0666);
    int server_queue = msgget (SERVER, 0666);

    message msg;
    strcpy (msg.word, argv[1]);
    msg.type = 1;

    msgsnd (server_queue, &msg, sizeof(char) * WORD_SIZE, 0);
    msgrcv (client_queue, &msg, sizeof(char) * WORD_SIZE, 0, 0);

    fprintf(stdout, "PL: %s\n", argv[1]);
    fprintf(stdout, "EN: %s\n", msg.word);

    return 0;
}