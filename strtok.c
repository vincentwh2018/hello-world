#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
   char ipaddr[] = "218;199.103.68";
   
   /* error, ipaddr point to a const string */
   //char *ipaddr = "218.199.103.68"; 
   
   char *cp = NULL;
   int i;

   if (argc > 0)
     for (i=0; i< argc; i++)
       printf("argv[%d]=%s\n", i, argv[i]);

   printf("ipaddr=%s\n", ipaddr);
   
   /* char *strtok(char *s, const char *delim), 
    * delim could be a char or a string, if delim 
    * is a string, then any char that in the string 
    * will be a delimiter.
    */
    
   /* char ; and char . both are delimiters */
   cp = strtok(ipaddr, ";.");  
   
   /* error, "192.168.10.161" is a const string */
   //cp = strtok("192.168.10.161", ".,");  
   
   if (cp != NULL)
      printf("%s\n", cp);

   while(cp != NULL)
   {
      cp = strtok(NULL, ";.");
      if (cp != NULL)
         printf("%s\n", cp);
   }
  
   cp = "123\n";
   printf("strlen(cp)=%d\n", strlen(cp));
   char teststr[10];
   memset(teststr, 0, sizeof(char)*10);
   strcpy(teststr, cp);
   printf("strlen(teststr)=%d\n", strlen(teststr));
   
   cp = NULL;
   if (strchr(cp, '+') == NULL)
      printf("NULL\n");  
}
