#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

typedef struct _MESSAGE
{
    int lenght;
    int id;
    char *path;
} MESSAGE;

void send_message (int client, void *data);
void get_server (int server);

int main ()
{
    MESSAGE message;
    int id;
    printf ("Enter id:\n");
    scanf ("%d", &id);

    message.id = id;
    message.path = getenv("HOME");
    message.lenght = sizeof (int) + strlen (message.path);

    if (message.id < 0) {
        fprintf (stderr, "sometrhing wrong");
        return 1;
    }

    int client = open ("klientfifo", O_WRONLY);
    int server = open ("serwerfifo", O_RDONLY);

    send_message (client, &message);
    get_server (server);

}


void send_message (int client, void *data)
{
    char *buffer = (char *) malloc (sizeof (int) + ((MESSAGE *)data)->lenght);
    memcpy (buffer, &((MESSAGE *)data)->lenght, sizeof (int));
    memcpy (buffer + sizeof (int), &((MESSAGE *)data)->id, sizeof (int));
    memcpy(buffer + (2 * sizeof(int)), ((MESSAGE *)data)->path, ((MESSAGE *)data)->lenght - sizeof(int));
    write (client, buffer, ((MESSAGE *)data)->lenght + sizeof (int));
    free (buffer);
}

void get_server (int server)
{
    unsigned char *surname = calloc (20, sizeof (char));
    fsync (server);
    read (server, surname, 80);
    printf ("%s\n",surname);
}