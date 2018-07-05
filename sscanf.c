#include <stdio.h>

int main(void)
{
   char *str = "aaaaa-99999-88888@kdfakdj";
   char str1[10], str2[10], str3[10];
   sscanf(str, "%[^-]-%[^-]-%[^@]", str1, str2, str3);
   printf("%s\n", str1);
   printf("%s\n", str2);
   printf("%s\n", str3);
}

