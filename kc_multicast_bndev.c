/*
 * =====================================================================================
 *
 *       Filename:  broadcast.c
 *
 *    Description:  send broadcast packet
 *
 *        Version:  1.0
 *        Created:  12/12/2008 04:04:21 PM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include<stdio.h>  
#include<string.h>
#include<stdlib.h>
#include<errno.h>

#include<netdb.h>        //herror() 
#include<unistd.h>       // read(), write(),exit() 
#include<netinet/in.h>   //struct sockaddr_in  inet_ntoa() inet_addr()
#include<sys/types.h>     //socket() bind() accept()  connect() inet_addr()
#include<sys/socket.h>   
//socket() bind() listen() accept() connect() inet_ntoa() inet_addr()
#include<arpa/inet.h>       //inet_addr()  inet_ntoa()
#include<linux/if.h>      //  struct ifreq

#include<fcntl.h>         //open()
#include<sys/stat.h>     // O_RDWR,O_CREAT,O_TRUNC
#include<sys/time.h>            // struct timeval
#include<sys/select.h>          // select()
#include<netinet/tcp.h> //for TCP_XXX defines.

int broadSend(int times, char *bndevName, char* ipStr)
{
  int err = 0;
	int ret = 0;
	int broadfd = -1;
  int i = 0;
  int failCount = 0;
  struct sockaddr_in *broadaddr;
  int addrlen = sizeof(struct sockaddr_in);
  const int on = 1;
  char mess[32];
  
  if(bndevName == NULL)
  { bndevName = "br0"; }
  printf("times %d, bndevName %s\n", times, bndevName);

  memset(mess, 0, sizeof(mess));
  mess[0] = '1';
  mess[1] = '2';
  mess[2] = '3';
  
  broadfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(broadfd < 0)
  {
      printf(" socket err \n");
      return -1;
  }
  broadaddr = (struct sockaddr_in *)malloc(addrlen);
  memset(broadaddr, 0, addrlen);
  broadaddr->sin_family = AF_INET;
  broadaddr->sin_port = htons(7423);
  if(ipStr == NULL)
  { broadaddr->sin_addr.s_addr = inet_addr("239.255.0.1");  }
  else
  { broadaddr->sin_addr.s_addr = inet_addr(ipStr);  }
//  broadaddr->sin_addr.s_addr = inet_addr("224.0.0.1");
//  broadaddr->sin_addr.s_addr = inet_addr("224.0.0.254");
//  broadaddr->sin_addr.s_addr = inet_addr("224.0.1.1");
  
  if(bndevName != NULL)
  {
    struct ifreq if1;
    int nameSize = 0;
    int ret = 0;

    nameSize = strlen(bndevName) + 1;
    memcpy(if1.ifr_name, (const void*)bndevName, nameSize);
    ret = setsockopt(broadfd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&if1, sizeof(if1));
    if(ret == 0)
    { printf(" bind %s success \n", bndevName); }
    else
    { printf(" bind %s fail \n", bndevName); }
  }while(0);

  setsockopt(broadfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
  

  if(1)
  {
    struct in_addr iaddr;
    iaddr.s_addr = INADDR_ANY;
    setsockopt(broadfd, IPPROTO_IP, IP_MULTICAST_IF, &iaddr, sizeof(struct in_addr));
    if(ret)
    {   
      printf("set multi if fail : %d\n",   sizeof(struct in_addr));  
      perror("fff");
    }
  }

  while(i < times)
  {
  		mess[3] = i;
  		ret = sendto(broadfd, mess, sizeof(mess), 0, (struct sockaddr *)broadaddr, addrlen);
      if(ret < 0)
      {
        ++failCount;
        err = errno;
        printf(" %d : %s \n", ret, strerror(err));
      }
      ++i;
  		usleep(1000); //  1 millisec
  }
	printf("\n send times %d , failCount %d\n", times, failCount);
  close(broadfd);

	return ret;
}



int main(int argc, char *argv[])
{
	int times = 1;
  int err = 0;
  char *bndevName = NULL;
  char *ipStr = NULL;

  printf("ex. ./a.out send_count devName ip. If no arg, use default \n");

  if(argc >= 2)
  { sscanf(argv[1], "%d", &times);  }
  if(argc >= 3)
  { bndevName = argv[2];  }
  if(argc >= 4)
  { ipStr = argv[3];  }

	if(times < 0)
	{	times = 0;	}

	if(times > 10000)
	{	times = 10000;	}

	broadSend(times, bndevName, ipStr);

GOTO_MAIN_END:

	return 0;
}


