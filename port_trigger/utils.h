/**
** Name:  utils.h	
** Desc:  interfaces for utilities.
** Author: Echo
** Date:  11/18/2005
**/

#define QUEUE_LEN 100

void sin_init (struct sockaddr_in *psin_addr, int port);
int init_listen (int fd, int port);
void reset_tv (struct timeval *tv);


