#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char* argv[])
{
   struct in_addr addr1, addr2;
   unsigned long l1, l2;
   l1 = inet_addr("192.168.10.74");
   l2 = inet_addr("211.100.21.179");

   addr1.s_addr = l1;
   addr2.s_addr = l2;

   printf("%s - - %s\n", inet_ntoa(addr1), inet_ntoa(addr2));

   printf("%s\n", inet_ntoa(addr1));
   printf("%s\n", inet_ntoa(addr2));
   
   return 0;
}
