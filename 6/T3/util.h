#ifndef _QUEUE_H_
#define _QUEUE_H_

#define CLIENT 123
#define SERVER 321
#define W_SIZE 256
#define D_SIZE 5

//queue in and out
extern int client_queue;
extern int server_queue;

//dictionary struct
typedef struct dictionary_t
{
   char pl[W_SIZE];
   char en[W_SIZE];
} dictionary;

//message structure
typedef struct message_t
{
   long type;
   char word[W_SIZE];
} message;

extern void clean ();
char *find_word (char *word);

#endif