#include <stdio.h>
#include <string.h>
#include <pthread.h>

/*线程一*/  
void thread_1(void)  
{  
    int i=0;  
	FILE *fp=NULL;
	char filename[50]={0};
	
    for(i=0;i<10;i++)  
    {  
        sprintf(filename, "/home/projects/test/thread1_%d", i);
        fp=fopen(filename, "w");   
		printf("This is a pthread_1 fileno %d\n", fileno(fp));
        sleep(1);  
		memset(filename, 0, 50);
    } 
	
	pthread_exit(0);
}  
  
/*线程二*/  
void thread_2(void)  
{  
    int i;  
	FILE *fp=NULL;
	char filename[50]={0};
	
    for(i=0;i<10;i++)  
    {  
        sprintf(filename, "/home/projects/test/thread2_%d", i);
        fp=fopen(filename, "w");   
		printf("This is a pthread_2 fileno %d\n", fileno(fp));
        sleep(1);  
		memset(filename, 0, 50);
    } 
    pthread_exit(0);  
}  
  
int main(void)  
{  
    pthread_t id_1,id_2;  
    int i,ret;  
/*创建线程一*/  
    ret=pthread_create(&id_1,NULL,(void  *) thread_1,NULL);  
    if(ret!=0)  
    {  
        printf("Create pthread error!\n");  
        return -1;  
    }  
/*创建线程二*/  
     ret=pthread_create(&id_2,NULL,(void  *) thread_2,NULL);  
    if(ret!=0)  
    {  
        printf("Create pthread error!\n");  
        return -1;  
    }  
	
	
/*等待线程结束*/  
    pthread_join(id_1,NULL);  
    pthread_join(id_2,NULL);  
    return 0;  
}





