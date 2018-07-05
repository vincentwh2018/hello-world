/*
  Test tools for port trigger function.
  Author: Echo.
  Date:   11/18/2005
  Description:
        For some specific applications need port trigger supporting and it is not easy to test, it is very necessary to develop an easy-go test tools both for RD and QA.
        Port trigger function works like this.
        Client send a command packet with a given destination service type(protocol+port), but server will reply a packet to the client with different port.
        src-ip  src-prot   src-port             dst-ip  dst-prot dst-port
orig    ip1     prot1      port1                ip2     prot2    port2
reply   ip2     prot2      port2                ip1     prot3    port3
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "utils.h"

#define SERVER_PORT 1024

typedef union {
	struct sockaddr sin;
	struct sockaddr_in in_sin;
} usockaddr;

int
main (void)
{
  int listen_fd;
  int send_fd;
  int conn_fd;
  struct timeval tv;
  fd_set rdfds;
  int retval;
  char buf[1024];
  usockaddr usa;
  socklen_t len = sizeof(usa);

  listen_fd = socket (AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0)
    {
      perror ("socket");
      return -1;
    }
  init_listen (listen_fd, SERVER_PORT);
  listen (listen_fd, QUEUE_LEN);
  while (1)
    {
      reset_tv (&tv);
      FD_ZERO (&rdfds);
      FD_SET (listen_fd, &rdfds);
      retval = select (listen_fd + 1, &rdfds, NULL, NULL, &tv);
      if (retval == -1)
	{
	  perror ("select");
	  break;
	}
      else if (retval != 1)
	{
	  continue;
	}
      else
	{
	  conn_fd = accept (listen_fd, &usa.sin, &len);
	  if (conn_fd < 0)
	    {
	      perror ("accept");
	      break;
	    }
	  tv.tv_sec = 1;
	  tv.tv_usec = 0;
	  setsockopt (conn_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof (tv));

	  printf ("connect...");
	  while (read (conn_fd, buf, sizeof (buf)) > 0)
	    {
	      printf ("1\n");
	      printf ("%s", buf);
	    }
	  close(conn_fd);
	  bzero (buf, sizeof(buf));
	  sprintf (buf, "hello word");
	  printf ("write %s....", buf);
	   
	  //send request to client 
	  send_fd = socket(AF_INET, SOCK_STREAM, 0);
	  if (send_fd <= 0) {
		perror("socket");
		break;
	  }
	  usa.in_sin.sin_port = htons(1127);
	  usa.in_sin.sin_family = AF_INET;
	  printf("%s\n", inet_ntoa(usa.in_sin.sin_addr));
	  if (connect (send_fd, &usa.sin, sizeof (struct sockaddr_in)) < 0){
		perror ("connect");
		break;
	  }
	
	  write (send_fd, buf, strlen (buf));
	  break;

	  //to reply the response with a different connection
	  //sendreply()

	}
    }
  if (conn_fd > 0)
    close (conn_fd);
  close (listen_fd);
}
