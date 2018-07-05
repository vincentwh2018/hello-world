#include <stdio.h>


/*
*  In Hex, 'A' stand for Dec 10, 'B' stand for Dec 11...
*  In ASCII, 'A' which Dec is 65, we need to minus 55(0x37), to get it's Dec number.
*/
char *AsciiToChar(char *asc,char str[])
{
      int i=0,n=0,len;
      char cTemp[1024];
      memset(cTemp,0x00,sizeof(cTemp));
      strcpy(cTemp,asc);
      len=strlen(cTemp);
      for(i=0;i<len;i+=2)
      {
              if(('0'<=cTemp[i]&&cTemp[i]<='9')&&('0'<=cTemp[i+1]&&cTemp[i+1]<='9'))
                      str[n++]=(char)(cTemp[i]<<4|(cTemp[i+1]&0x0F));
              else if('0'<=cTemp[i]&&cTemp[i]<='9'&&('A'<=cTemp[i+1]&&cTemp[i+1]<='F'))
                      str[n++]=(char)(cTemp[i]<<4|(cTemp[i+1]-0x37));  //minus 55
              else if(('A'<=cTemp[i]&&cTemp[i]<='F')&&('0'<=cTemp[i+1]&&cTemp[i+1]<='9'))
                      str[n++]=(char)(((cTemp[i]-0x37)<<4)|(cTemp[i+1]&0x0F));
              else if(('A'<=cTemp[i]&&cTemp[i]<='F')&&('A'<=cTemp[i+1]&&cTemp[i+1]<='F'))
                      str[n++]=(char)(((cTemp[i]-0x37)<<4)|(cTemp[i+1]-0x37));  //minus 55
              else
                      printf("your input is wrong!!");
      }
      str[n]='\0';
      return str;
}

int main()
{
      char strin[1024];
      int i;
      memset(strin,0x00,sizeof(strin));
      printf("%s\n",AsciiToChar("6D4E333435",strin));
      exit(0);
}

