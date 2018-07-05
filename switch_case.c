#include <stdio.h>

int main(int argc, char* argv[])
{
   int i=0;

   switch(i)
   {
      case 0:
      if (i == 0)
      {
        printf("%s -- %u\n", __FILE__, __LINE__);
        break;
      }
      case 1:
      printf("%s -- %u\n", __FILE__, __LINE__);
      break;
      default:
      break;
   }
}
