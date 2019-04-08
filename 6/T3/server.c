#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <signal.h>

#define CLIENT 123
#define SERVER 321
#define W_SIZE 256
#define D_SIZE 5

int client_queue;
int server_queue;

void clean ();
char *find_word (char *word);

typedef struct dictionary_t
{
   char pl[W_SIZE];
   char en[W_SIZE];
} dictionary;

dictionary leksis[D_SIZE] =
{
   { "kot", "cat" },
   { "pies", "dog" },
   { "szkoła", "school" },
   { "ojciec", "father"},
   { "woda", "water"}
};

typedef struct message_t
{
   long type;
   char word[W_SIZE];
} message;

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

void clean ()
{
    msgctl(client_queue, IPC_RMID, 0);
    msgctl(server_queue, IPC_RMID, 0);
    exit(0);
}

char *find_word (char *word)
{
    for (int i = 0; i < D_SIZE; ++i)
    {
        if (strcmp(word, leksis[i].pl) == 0)
            return leksis[i].en;
    }
    return "Nie znam takiego słowa";
}