#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <signal.h>

int client_queue;
int server_queue;

dictionary leksis[D_SIZE] =
{
   { "kot", "cat" },
   { "pies", "dog" },
   { "szkoła", "school" },
   { "ojciec", "father"},
   { "woda", "water"}
};


//clean queue after sigint
void clean ()
{
    msgctl(client_queue, IPC_RMID, 0);
    msgctl(server_queue, IPC_RMID, 0);
    exit(0);
}


//find proper word
char *find_word (char *word)
{
    for (int i = 0; i < D_SIZE; ++i)
    {
        if (strcmp(word, leksis[i].pl) == 0)
            return leksis[i].en;
    }
    return "Nie znam takiego słowa";
}
