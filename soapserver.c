#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 7003
#define SERVER_NAME "micro_httpd"
#define PROTOCOL "HTTP/1.1"
#define RFC1123FMT "%a, %d %b %Y %H:%M:%S GMT"

typedef union
{
	struct sockaddr sa;
	struct sockaddr_in sa_in;
} usockaddr;

static int initialize_listen_socket (usockaddr * usaP)
{
	int listen_fd;
	int i;

	memset (usaP, 0, sizeof (usockaddr));
	usaP->sa.sa_family = AF_INET;
	usaP->sa_in.sin_addr.s_addr = htonl (INADDR_ANY);
	usaP->sa_in.sin_port = htons (SERVER_PORT);

	listen_fd = socket (usaP->sa.sa_family, SOCK_STREAM, 0);
	if (listen_fd < 0)
	{
		perror ("socket");
		return -1;
	}
	(void) fcntl (listen_fd, F_SETFD, 1);
	i = 1;
	if (setsockopt
	    (listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *) &i,
	     sizeof (i)) < 0)
	{
		perror ("setsockopt");
		return -1;
	}
	if (bind (listen_fd, &usaP->sa, sizeof (struct sockaddr_in)) < 0)
	{
		perror ("bind");
		return -1;
	}
	if (listen (listen_fd, 10) < 0)
	{
		perror ("listen");
		return -1;
	}
	return listen_fd;
}


static void send_headers(FILE *conn_fp, int status, char* title)
{
    time_t now;
    char timebuf[100];

    (void) fprintf( conn_fp, "%s %d %s\r\n", PROTOCOL, status, title );
    (void) fprintf( conn_fp, "Server: %s\r\n", SERVER_NAME );
    (void) fprintf( conn_fp,"Cache-Control: no-cache\r\n") ;
    now = time( (time_t*) 0 );
    (void) strftime( timebuf, sizeof(timebuf), RFC1123FMT, gmtime( &now ) );
    (void) fprintf( conn_fp, "Date: %s\r\n", timebuf );
    (void) fprintf( conn_fp, "Connection: close\r\n" );
    (void) fprintf( conn_fp, "\r\n" );
}


int main()
{
   usockaddr usa;
   int listen_fd;
   fd_set rset;
   int nready;
   FILE *conn_fp;
   int conn_fd;
   int readlen = 0;
   char soapmsg[5000];
   
   if ((listen_fd = initialize_listen_socket (&usa)) < 0)
   {
   	 fprintf (stderr, "can't bind to any address\n");
   	 exit (errno);
   }
   
   for (;;)
   { 
   	 FD_ZERO(&rset);
   	 FD_SET (listen_fd, &rset);
   	 
   	 nready = select(FD_SETSIZE,&rset,NULL,NULL,NULL);
   	 
   	 if ( nready == -1 ) 
   	 {
            printf("!!! HTTP server is received request with nready == -1 !!!\n");
            usleep(100);
            continue;
         }
         else if ( nready != 1 ) 
         {
            perror("select");
            printf("app: HTTP server received request with nready == %d\n", nready);
         }
         
         if ( FD_ISSET(listen_fd,&rset))
         {

            memset(soapmsg, 0, sizeof(soapmsg));
            printf("Receive request! \n");
          
            if ((conn_fd = accept(listen_fd, &usa.sa, &readlen)) < 0) 
            {
                printf("Listen accept error! \n");
            }
            else 
            {
                printf("Listen accept success! \n");
                if (!(conn_fp = fdopen(conn_fd, "r+"))) 
                {
                    perror("fdopen");
                    shutdown(listen_fd, 2);
                    close(listen_fd);
                    return errno;
                }
                            
                if ((readlen = read(conn_fd, soapmsg, sizeof(soapmsg))) > 0) 
                {
                    if (readlen >= 5000)
                       while (read(conn_fd, soapmsg, sizeof(soapmsg)) > 0) {}

                    send_headers(conn_fp, 200, "OK");
                }
                else 
                {
                    printf("No message received! \n");
                }    
                close(conn_fd);
            }
        }
   }
   
}
