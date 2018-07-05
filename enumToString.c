#include <stdio.h>


enum
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
};

#define P(I)  printf(#I"\n");


void enumToString( int event, char *string )
{
   string[0] = '\0';

#define CASE_EVENT_STRING( event )  \
      case event:                   \
      {                             \
         strcpy( string, #event );  \
      }                             \
      break;

   P(event);

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
      CASE_EVENT_STRING( CLASSSTM_CLID_SAS_ONLY       )
      CASE_EVENT_STRING( CLASSSTM_CLID_INFO           )
      CASE_EVENT_STRING( CLASSSTM_CLID_SAS_CAS_OFF    )
      CASE_EVENT_STRING( CLASSSTM_TONE_GEN_EVT        )
      CASE_EVENT_STRING( CLASSSTM_CLID_ACK_RCVD       )
      CASE_EVENT_STRING( CLASSSTM_VMWI_ON             )
      CASE_EVENT_STRING( CLASSSTM_VMWI_OFF            )
      CASE_EVENT_STRING( CLASSSTM_VMWI_OSI_END        )
      default:
      {
         strcpy( string, "Event unknown!" );
      }
      break;
   }
}


int main(void)
{
    char string[100];
    
    string[0] = '\0';
    enumToString(CLASSSTM_FLASH, string);
    printf("%s\n", string);
    P(CLASSSTM_FLASH);
    
    string[0] = '\0';
    enumToString(CLASSSTM_CLID_FIRST_RINGOFF, string);
    printf("%s\n", string);
    P(CLASSSTM_FLASH);
    
    string[0] = '\0';
    enumToString(CLASSSTM_CLID_SAS_CAS, string);
    printf("%s\n", string);
    P(CLASSSTM_FLASH);
}


