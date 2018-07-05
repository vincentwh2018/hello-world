/*
  Test tools for port trigger function.
  Author: Echo.
  Date:   11/18/2005
  Description:
	For some specific applications need port trigger supporting and it is not easy to test, it is very necessary to develop an easy-go test tools both for RD and QA.
	Port trigger function works like this.
	Client send a command packet with a given destination service type(protocol+port), but server will reply a packet to the client with different port.
	src-ip	src-prot   src-port		dst-ip 	dst-prot dst-port
orig    ip1	prot1	   port1		ip2	prot2	 port2	
reply	ip2	prot2	   port2		ip1	prot3	 port3
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

int
main (void)
{
  int send_fd;
  int listen_fd;
  int conn_fd;
  struct sockaddr_in sin;
  char buf[1024];
  char read_buf[1024];
  fd_set rfds;
  int retval;
  struct timeval tv;

  int pid = 0;			//for child process to send request  

  if ((send_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror ("send socket");
      return -1;
    }
  listen_fd = socket (AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0)
    {
      perror ("listen socket");
      close (send_fd);
      return -1;
    }
  sin_init (&sin, 1024);
  init_listen (listen_fd, 1127);
#if 0
  bzero (&sin, sizeof (sin));
  sin.sin_addr.s_addr = inet_addr ("192.168.10.144");
  sin.sin_family = AF_INET;
  sin.sin_port = htons (80);
#endif
  listen (listen_fd, QUEUE_LEN);
  if ((pid = fork ()) == 0)
    {

      //for child process
      //close listen socket first
      //close (listen_fd);
      if (connect (send_fd, (struct sockaddr *) &sin, sizeof (sin)) < 0)
	{
	  perror ("connect");
	  close (send_fd);
	  close (listen_fd);
	  return -1;
	}
      sprintf (buf, "GET /index.htm HTTP/1.0\r\n\r\n");
      if (write (send_fd, buf, strlen (buf)) < 0)
	{
	  perror ("send");
	  close (send_fd);
	  close (listen_fd);
	}
      fsync (send_fd);
      while (read (send_fd, buf, sizeof (buf) - 1) > 0)
	{
	  printf ("%s", buf);
	  printf ("1\n");
	}
      close (send_fd);
      printf ("send complete...\n");
      exit (0);
    }
  close (send_fd);

  while (1)
    {
      reset_tv (&tv);
      FD_ZERO (&rfds);
      FD_SET (listen_fd, &rfds);
      retval = select (listen_fd + 1, &rfds, NULL, NULL, &tv);
      if (retval == -1)
	{
	  perror ("select");
	  break;
	}
      else if (retval == 1)
	{
	  if (FD_ISSET (listen_fd, &rfds))
	    {
	      conn_fd = accept (listen_fd, NULL, NULL);
	      if (conn_fd < 0)
		{
		  perror ("accept");
		  break;
		}
	      while (read (conn_fd, read_buf, sizeof (read_buf)) > 0)
		{
		  printf ("%s", read_buf);
		}
	      sprintf (buf, "\n\nConnection Successfully!!!!!\n");
	      //      write (conn_fd, buf, strlen (buf));
	      close (conn_fd);
	      break;
	    }
	}
      else
	continue;
    }
  close (listen_fd);
}
