#include <stdio.h>

typedef union
{ 
  int i;
  char c;
}test_union;

typedef enum
{
   CLASSSTM_CLID_RING,
   CLASSSTM_CLID_NODATA_RING,
   CLASSSTM_CLID_SAS_CAS,
   CLASSSTM_CLID_SAS_ONLY,
   CLASSSTM_CLID_SAS_CAS_OFF,
   CLASSSTM_CLID_ACK_RCVD,
   CLASSSTM_TONE_GEN_EVT,
   CLASSSTM_CLID_INFO,
   CLASSSTM_CLID_TX_END,
   CLASSSTM_CLID_FIRST_RINGOFF,

   CLASSSTM_OFFHOOK,
   CLASSSTM_ONHOOK,
   CLASSSTM_FLASH,

   CLASSSTM_VMWI_ON,
   CLASSSTM_VMWI_OFF,
   CLASSSTM_VMWI_OSI_END,

   CLASSSTM_RING_OFF,
   CLASSSTM_TIMER_EXPIRE
}ItemType;


void getEventString( int event, char *string )
{
   string[0] = '\0';

#define CASE_EVENT_STRING( event )  \
      case event:                   \
      {                             \
         strcpy( string, #event );  \
      }                             \
      break;

   switch ( event )
   {
      CASE_EVENT_STRING( CLASSSTM_CLID_RING           )
      CASE_EVENT_STRING( CLASSSTM_CLID_NODATA_RING    )
      CASE_EVENT_STRING( CLASSSTM_RING_OFF            )
      CASE_EVENT_STRING( CLASSSTM_CLID_FIRST_RINGOFF  )
      CASE_EVENT_STRING( CLASSSTM_OFFHOOK             )
      CASE_EVENT_STRING( CLASSSTM_ONHOOK              )
      CASE_EVENT_STRING( CLASSSTM_FLASH               )
      CASE_EVENT_STRING( CLASSSTM_TIMER_EXPIRE        )
      CASE_EVENT_STRING( CLASSSTM_CLID_TX_END         )
      CASE_EVENT_STRING( CLASSSTM_CLID_SAS_CAS        )
      default:
      {
         strcpy( string, "Event unknown!" );
      }
      break;
   }
}

char* getstring(void)
{
  char* p="hello world";
  return p;
}


int main(int argc, char **argv)
{
  test_union a;
  char str[100];
  char msg[] = "02345"
               "67890";
  int i;
  if (argc > 0)
    for (i=0; i < argc; i++)
       printf("argv[%d]=%s\n", i, argv[i]);

  str[0] = '\0';
  printf("msg: %s\n", msg);
  memset(&a, 0, sizeof(test_union));
  a.c = 'a';
  printf("%c\n", a.c);
  printf("%d\n", a.i);
  printf("%d,  %d,  %d\n", strlen("\r\n"), sizeof("\r\n"), sizeof(test_union));
  printf("%d\n", (38 % 20));
  strncpy(msg, "\0", 0);
  printf("%s\n", msg);
  getEventString(CLASSSTM_CLID_SAS_CAS, str);
  printf("aa%%aa\"\n");
  printf("%01X -- %d\n", 128 & 0x0F, strlen("aa\r\n"));

  int m = 0;
  int n = m?:9;
  printf("%d\n", n);

  printf("%s %u\n", __FUNCTION__, __LINE__);
  
  char *ptr = (char *)malloc(sizeof(char)*100);
  memset(ptr, 0, sizeof(char)*100);
  strcpy(ptr, msg);
  printf("%c\n", *ptr++);
  printf("%c\n", *ptr);

  ItemType type = CLASSSTM_OFFHOOK; 
  printf("%0x\n", type);

  unsigned long num = 98;
  printf("unsigned long num=%u\n", num);

  char str_for_cpy[100];
  strcpy(str_for_cpy, "1234567890");
  printf("%s\n", str_for_cpy);
  strcpy(str_for_cpy, str_for_cpy+5);
  printf("%s\n", str_for_cpy);

  printf("getstring=%s\n", getstring());

  sprintf(str_for_cpy, "%02X", 0xa);
  printf("%s\n", str_for_cpy);
  fflush(stdout);

  char str_for_test[100];
  memset(str_for_cpy, 0, 100);
  memset(str_for_test, 0, 100);
  strcpy(str_for_test, str_for_cpy);
  printf("%s\n", str_for_cpy);

  char *ptr_malloc;
  ptr_malloc =(char*) malloc(100);
  strcpy(ptr_malloc, "hello world!");
  printf("ptr_malloc=%s\n", ptr_malloc);
  free(ptr_malloc);

  int sum = 1;
  for (i=9; i>=1; i--)
  {
      printf("sum=%d  ", sum);
      sum = 2*(sum+1);
  }
  printf("sum=%d\n", sum);
  printf("sum's address is %p\n", sum);

  char option = '0';
  option = '1';
  printf("option = %c\n", option);
  printf("option = %s\n", &option);
  
  return;
}
