/**
** utilites for test tools
** Author: echo
** Date:   11/18/2005
**/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/*init the struct sockaddr_in*/
void
sin_init (struct sockaddr_in *psin_addr, int port)
{
  bzero (psin_addr, sizeof (struct sockaddr_in));
  psin_addr->sin_addr.s_addr = inet_addr ("10.0.0.1");
  psin_addr->sin_family = AF_INET;
  psin_addr->sin_port = htons (port);
}

/*
**       Description: Init the listenning socket
**       Returns:        -1      error
**                       0       success
*/

int
init_listen (int fd, int port)
{
  struct sockaddr_in sin;
  int i = 1;
  sin_init (&sin, port);
  sin.sin_addr.s_addr = htonl (INADDR_ANY);
  if (setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, (char *) &i, sizeof (i)) < 0)
    {
      perror ("setsockopt");
      return -1;
    }
  if (bind (fd, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      perror ("bind");
      return -1;
    }
  return 0;
}

/*
 reset tv struct for select
*/

void
reset_tv (struct timeval *tv)
{
  tv->tv_sec = 1;
  tv->tv_usec = 0;
}

