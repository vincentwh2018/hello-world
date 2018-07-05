#include <stdio.h> 
#include <errno.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/vfs.h> 
#include <math.h> 
#define SIZE1 100 
#define FN "/etc/mtab"
#define SPACE ' '

int displayapartition(char * pt,char * pt1); 

int main(void){ 

 char tmpline[SIZE1]; 
 FILE * fp; 
 char * pt1; 
 char * pt2; 
 char * pt3; 


 if( (fp = fopen(FN,"r")) == NULL ){ 
    fprintf(stderr,"%s \n",strerror(errno)); 
    exit(5); 
 } 

 while( fgets(tmpline, SIZE1, fp) != NULL ){ 
     pt1=strchr(tmpline, SPACE); 
     pt2=pt1+sizeof(char); 
     *pt1='\0'; 
     pt3=strchr(pt2,SPACE); 
     *pt3='\0'; 
     if(strstr(tmpline,"/dev") != NULL ){ 
        displayapartition(tmpline,pt2); 
     } 
 } 
 return 0; 
} 

int displayapartition(char * pt,char * pt1){ 
 
 struct statfs buf;
 int usage;  
 statfs(pt1,&buf); 
 usage=ceil((buf.f_blocks-buf.f_bfree)*100/buf.f_blocks); 

 printf("%s ",pt); 
 printf("%ld ",buf.f_blocks); 
 printf("%ld ",buf.f_blocks-buf.f_bfree); 
 printf("%ld ",buf.f_bavail); 
 printf("%d%% ",usage); 
 printf("%s ",pt1); 
 printf("\n"); 

 return 0; 
}