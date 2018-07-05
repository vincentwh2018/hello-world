#include <stdio.h>

char* getstring()
{
   char *p="hello world";
   return p;
}

int main()
{
   printf("%s\n", getstring());
}
