#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <signal.h>
#include "util.h"

int main ()
{
    signal (SIGINT, clean);

    client_queue = msgget (CLIENT, 0666 | IPC_CREAT);
    server_queue = msgget (SERVER, 0666 | IPC_CREAT);

    message msg;

    while (1)
    {
        msgrcv (server_queue, &msg, sizeof(char) * W_SIZE, 0, 0);
        strcpy (msg.word, find_word(msg.word));
        msgsnd (client_queue, &msg, sizeof(char) * W_SIZE, 0);
    }

    return 0;
}