#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_LENGHT 20
#define DB_SIZE 20

typedef struct _MESSAGE
{
    int id;
    char *path;
} MESSAGE;

typedef struct _CLIENT
{
    int id;
    char *surname;
} CLIENT;

void create_database (char *filename, void *data);
char *get_surname (int id, void *data);
MESSAGE get_client (int client, int size);
void send_message (int server, void *database, void *data);






int main ()
{
    CLIENT database[DB_SIZE];
    MESSAGE message;


    create_database("database.txt", database);

    // for (int i = 0; i < DB_SIZE; ++i)
    //     fprintf (stdout, "%d %s\n", database[i].id, database[i].surname);

    mkfifo ("klientfifo", 0666);
    mkfifo ("serverfifo", 0666);

    int client = open ("klientfifo", O_RDONLY);
    int server = open ("serwerfifo", O_WRONLY);

    int message_lenght = 0;
    int bytes = 0;

    while (1)
    {
        if ((bytes = read(client, &message_lenght, sizeof (int))) > 0)
        {
            message = get_client (client, message_lenght);
            printf ("%d\n", message.id);
            send_message (server, &database, &message);
        }
    }

    close (client);
    close (server);
    unlink ("klientfifo");
    unlink ("serwerfifo");
     

    return 0;
}

void create_database (char *filename, void *data)
{
    FILE *handler;

    if ((handler = fopen (filename, "r"))) {
        for (int i = 0; i < DB_SIZE; ++i)
        {
            ((CLIENT *)data)[i].surname = (char *) malloc (MAX_LENGHT);
            fscanf (handler, "%d %20s", &((CLIENT *)data)[i].id, ((CLIENT *)data)[i].surname);
        }
    fclose (handler);
    }
    else {
        fprintf (stdout, "File cannot be open!");
    }
}

char *get_surname (int id, void *data)
{
    for (int i = 0; i < DB_SIZE; ++i)
    {
        if (((CLIENT *)data)[i].id == id)
            return ((CLIENT *)data)[i].surname;
    }
    return "ID NOT FOUND";
}

MESSAGE get_client (int client, int size)
{
    MESSAGE message;
     char *buffer = (char *) malloc (size);
    read(client, buffer, size);
    memcpy (&message.id, buffer, sizeof (int));
    message.path = (char *) malloc (size - sizeof (int));
    memcpy (message.path, (buffer + sizeof (int)), size - sizeof (int));
    free (buffer);
    return message;
}

void send_message (int server, void *database, void *data)
{
    int surname_lenght = 0;
    char *surname = get_surname(((MESSAGE*)data)->id, database);
    char *message = (char *) malloc (strlen (surname) + (sizeof (int) + 1));

    surname_lenght = strlen (surname);

    memcpy (message, &surname_lenght, sizeof (int));
    memcpy (message + sizeof (int), surname, surname_lenght);

    printf ("%s\n", surname);

    write (server, message, surname_lenght + sizeof (int));
    
    free (message);
}



