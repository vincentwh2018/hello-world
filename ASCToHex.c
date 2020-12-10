#include   <stdio.h>   
#include   "string.h"   
void   ASCToStr(char*   pszSource,char*   pDest)   
{   
    char   pTemp[3]={0};   
    for(int   i=0;i<strlen(pszSource);i++)   
    {   
    sprintf(pTemp,"%X",pszSource[i]);   
    strcat(pDest,pTemp);   
    }   
      
}   
  
void   main()   
{   
    char   pDest[512]={0};   
    ASCToStr("jdkjdlaj46545",pDest);   
    printf("%s",pDest);   
      
}