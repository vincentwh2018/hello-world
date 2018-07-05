#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int send_dcc_msg (char *msg);

int send_dcc_msg (char *msg)
{
   int sockfd = -1;
   struct sockaddr_in sockaddr;
   struct sockaddr_in myaddr;

   memset (&sockaddr, 0, sizeof (struct sockaddr_in));
   bzero (&myaddr, sizeof (struct sockaddr_in));
   sockaddr.sin_family = AF_INET;
   sockaddr.sin_port = htons (1028);
   sockaddr.sin_addr.s_addr = inet_addr("192.168.200.118");
   //myaddr.sin_family = AF_INET;
   //myaddr.sin_port = htons (5060);
   //myaddr.sin_addr.s_addr = htonl (INADDR_ANY);
   //sockaddr.sin_addr.s_addr = htonl ((unsigned long int)0xC0A80AA1);  //192.168.10.161


   //sockfd = socket (sockaddr.sin_family, SOCK_DGRAM, 0);
   sockfd = socket (sockaddr.sin_family, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      printf ("create socket error\n");
      return -1;
   }
   //if (bind (sockfd, (struct sockaddr *)&myaddr, sizeof (struct sockaddr)))
   //{
   //	printf ("bind error..\n");
   //   close (sockfd);
   //	return -1;
   //}
   if (connect(sockfd, (struct sockaddr *) &sockaddr,
	sizeof (struct sockaddr_in)) < 0)
   {
      printf ("connect error\n");
      close (sockfd);
      return -1;
   }

   int ret = write (sockfd, msg, strlen (msg));
   
   if (ret != strlen(msg))
   {
	printf ("send %d\n bytes..\n");
   }

/*
   if (write (sockfd, msg, strlen (msg)) < 0)
   {
      printf ("write error\n");
      return -1;
   }
*/
   //sleep(5);
   close(sockfd);

   return 1;
}



int main()
{
   char *dccmsg = "wancfg.dcc?method=set";
   	
   printf("dccmsg: \n%s\n", dccmsg);
   send_dcc_msg(dccmsg);
   return 0;
}

