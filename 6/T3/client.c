#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include "util.h"

int main(int argc, char **argv)
{

    if (argc < 2)
        {
            fprintf (stderr, "Word to translate is not give!\nUse: ./client [word]\n");
            exit (1);
        }
    else if (argc > 2)
    {
        fprintf (stderr, "Too many arguments. Input only one word!\nUse: ./client [word]\n");
        exit (1);
    }


    client_queue = msgget (CLIENT, 0666);
    server_queue = msgget (SERVER, 0666);

    message msg;
    strcpy (msg.word, argv[1]);
    msg.type = 1;

    msgsnd (server_queue, &msg, sizeof(char) * W_SIZE, 0);
    msgrcv (client_queue, &msg, sizeof(char) * W_SIZE, 0, 0);

    fprintf(stdout, "[PL]: %s\n[EN]: %s\n", argv[1], msg.word);

    return 0;
}