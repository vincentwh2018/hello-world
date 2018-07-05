#include <stdio.h>

static char string[4096];

int main()
{
   char *str = "Test for static variable!";
   strcpy(string, str);
   printf("%s\n", string);
   return 0;
}
