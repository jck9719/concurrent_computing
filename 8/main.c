#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "handler.h"

int main ()
{
	scanf("%d", &x);

	result = handle_message (x);
	fprintf (stdout, "Result = %d\n", result);
	fprintf (stdout, "Function: x^2 + 1\n");

	return 0;
}           
