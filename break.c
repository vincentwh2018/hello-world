#include <stdio.h>


int main()
{
   int i = 0;

   do {
     if (i == 0)
     {
        i++;
        if (i == 1)
        {
           i++;
           if (i == 2)
              break;
        }
     }
     printf("%s - %u!!!\n", __func__, __LINE__);
   } while (1);

   printf("%s - %u!!!\n", __func__, __LINE__);
}
