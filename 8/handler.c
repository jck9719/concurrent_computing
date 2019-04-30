#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "handler.h"

int x, result;

int handle_message (int x)
{
	 int status, buffer;
	 unsigned int addr_len;

	struct sockaddr_in address;

	bzero ((char *) &address, sizeof (address));

	address.sin_family = AF_INET;
	address.sin_port = htons ((ushort) PORT);

	inet_pton (AF_INET, ADDR, &address.sin_addr);

	addr_len = sizeof (struct sockaddr_in);

	status = socket (PF_INET, SOCK_DGRAM, 0);

	bind (status, (struct sockaddr*) &address, addr_len);

	buffer = htonl (x);
	sendto (status, (char *) &buffer, sizeof (buffer), 0, (struct sockaddr *) &address, addr_len);

	recvfrom (status, (char *) &buffer, sizeof (buffer), 0, (struct sockaddr*) &address, &addr_len);
	buffer = ntohl (buffer);

	return buffer;
}