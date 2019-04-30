#ifndef _HANDLER_H
#define _HANDLER_H

#define ADDR "153.19.1.202"
#define PORT 5000

extern int status, buffer, x, result;
extern unsigned int addr_len;
extern struct sockaddr_in address;

int handle_message (int x);

#endif