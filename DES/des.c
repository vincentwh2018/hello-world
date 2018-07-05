#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "des.h"

ULONG32 g_outkey[16][2] = { 0};
ULONG32 g_bufkey[2] = { 0};
static ULONG8 wz_lefttable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
static ULONG32 wz_leftandtab[3] = {0x0 , 0x80000000 , 0xc0000000 } ;
static ULONG8 wz_keyleft[28] = 
{
       57,49,41,33,25,17,9,1,58,50,42,34,26,18,
       10,2,59,51,43,35,27,19,11,3,60,52,44,36
};
 
static ULONG8 wz_keyright[28] = {
       63,55,47,39,31,23,15,7,62,54,46,38,30,22,
       14,6,61,53,45,37,29,21,13,5,28,20,12,4
};
 
static ULONG8 wz_keychoose[48] ={
       14,17,11,24,1,5,3,28,15,6,21,10,
       23,19,12,4,26,8,16,7,27,20,13,2,
       41,52,31,37,47,55,30,40,51,45,33,48,
       44,49,39,56,34,53,46,42,50,36,29,32
};
 
static ULONG8 wz_pc4[64] = { 
       40,8,48,16,56,24,64,32, 39,7,47,15,55,23,63,31,
       38,6,46,14,54,22,62,30, 37,5,45,13,53,21,61,29,
       36,4,44,12,52,20,60,28, 35,3,43,11,51,19,59,27,
       34,2,42,10,50,18,58,26, 33,1,41,9,49,17,57,25
};
static ULONG8  wz_pc1[64] = {
                 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
                 62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
                 57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
                 61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 
} ;
 
static ULONG8 wz_pc3[32] = {
                        16,7,20,21, 29,12,28,17, 1,15,23,26,
                        5,18,31,10, 2,8,24,14, 32,27,3,9,
                        19,13,30,6, 22,11,4,25
} ;

static ULONG32  wz_pc2[64] = { 
        0x80000000L,0x40000000L,0x20000000L,0x10000000L, 0x8000000L, 
	0x4000000L, 0x2000000L, 0x1000000L, 0x800000L, 0x400000L,
        0x200000L, 0x100000L,  0x80000L, 0x40000L, 0x20000L,0x10000L, 
	0x8000L, 0x4000L, 0x2000L, 0x1000L, 0x800L, 0x400L, 0x200L,
	0x100L, 0x80L,0x40L,0x20L, 0x10L, 0x8L, 0x4L, 0x2L, 0x1L,
	0x80000000L,0x40000000L,0x20000000L,0x10000000L, 0x8000000L,
	0x4000000L, 0x2000000L, 0x1000000L, 0x800000L, 0x400000L,
        0x200000L, 0x100000L,  0x80000L, 0x40000L, 0x20000L, 0x10000L, 
	0x8000L, 0x4000L, 0x2000L, 0x1000L, 0x800L, 0x400L, 0x200L, 
	0x100L, 0x80L, 0x40L,0x20L, 0x10L, 0x8L,  0x4L, 0x2L, 0x1L,     
}; 
   
static ULONG8 exptab3[48] = {
                              32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,
                              12,13,14,15,16,17,16,17,18,19,20,21,
                              20,21,22,23,24,25,24,25,26,27,28,29,
                              28,29,30,31,32,1 
};
                       
static ULONG8 SP[8][64] = 
{
       {
              0xe,0x0,0x4,0xf,0xd,0x7,0x1,0x4,0x2,0xe,0xf,0x2,0xb,
              0xd,0x8,0x1,0x3,0xa,0xa,0x6,0x6,0xc,0xc,0xb,0x5,0x9,
              0x9,0x5,0x0,0x3,0x7,0x8,0x4,0xf,0x1,0xc,0xe,0x8,0x8,
              0x2,0xd,0x4,0x6,0x9,0x2,0x1,0xb,0x7,0xf,0x5,0xc,0xb,
              0x9,0x3,0x7,0xe,0x3,0xa,0xa,0x0,0x5,0x6,0x0,0xd  
       },

       { 
              0xf,0x3,0x1,0xd,0x8,0x4,0xe,0x7,0x6,0xf,0xb,0x2,0x3,
              0x8,0x4,0xf,0x9,0xc,0x7,0x0,0x2,0x1,0xd,0xa,0xc,0x6,
              0x0,0x9,0x5,0xb,0xa,0x5,0x0,0xd,0xe,0x8,0x7,0xa,0xb,
              0x1,0xa,0x3,0x4,0xf,0xd,0x4,0x1,0x2,0x5,0xb,0x8,0x6,
              0xc,0x7,0x6,0xc,0x9,0x0,0x3,0x5,0x2,0xe,0xf,0x9
       },
       { 
              0xa,0xd,0x0,0x7,0x9,0x0,0xe,0x9,0x6,0x3,0x3,0x4,0xf,
              0x6,0x5,0xa,0x1,0x2,0xd,0x8,0xc,0x5,0x7,0xe,0xb,0xc,
              0x4,0xb,0x2,0xf,0x8,0x1,0xd,0x1,0x6,0xa,0x4,0xd,0x9,
              0x0,0x8,0x6,0xf,0x9,0x3,0x8,0x0,0x7,0xb,0x4,0x1,0xf,
              0x2,0xe,0xc,0x3,0x5,0xb,0xa,0x5,0xe,0x2,0x7,0xc                                          
       },
       { 
              0x7,0xd,0xd,0x8,0xe,0xb,0x3,0x5,0x0,0x6,0x6,0xf,0x9,
              0x0,0xa,0x3,0x1,0x4,0x2,0x7,0x8,0x2,0x5,0xc,0xb,0x1,
              0xc,0xa,0x4,0xe,0xf,0x9,0xa,0x3,0x6,0xf,0x9,0x0,0x0,
              0x6,0xc,0xa,0xb,0xa,0x7,0xd,0xd,0x8,0xf,0x9,0x1,0x4,
              0x3,0x5,0xe,0xb,0x5,0xc,0x2,0x7,0x8,0x2,0x4,0xe                         
       },
       { 
              0x2,0xe,0xc,0xb,0x4,0x2,0x1,0xc,0x7,0x4,0xa,0x7,0xb,
              0xd,0x6,0x1,0x8,0x5,0x5,0x0,0x3,0xf,0xf,0xa,0xd,0x3,
              0x0,0x9,0xe,0x8,0x9,0x6,0x4,0xb,0x2,0x8,0x1,0xc,0xb,
              0x7,0xa,0x1,0xd,0xe,0x7,0x2,0x8,0xd,0xf,0x6,0x9,0xf,
              0xc,0x0,0x5,0x9,0x6,0xa,0x3,0x4,0x0,0x5,0xe,0x3
       },
       { 
              0xc,0xa,0x1,0xf,0xa,0x4,0xf,0x2,0x9,0x7,0x2,0xc,0x6,
              0x9,0x8,0x5,0x0,0x6,0xd,0x1,0x3,0xd,0x4,0xe,0xe,0x0,
              0x7,0xb,0x5,0x3,0xb,0x8,0x9,0x4,0xe,0x3,0xf,0x2,0x5,
              0xc,0x2,0x9,0x8,0x5,0xc,0xf,0x3,0xa,0x7,0xb,0x0,0xe,
              0x4,0x1,0xa,0x7,0x1,0x6,0xd,0x0,0xb,0x8,0x6,0xd
       },
       { 
              0x4,0xd,0xb,0x0,0x2,0xb,0xe,0x7,0xf,0x4,0x0,0x9,0x8,
              0x1,0xd,0xa,0x3,0xe,0xc,0x3,0x9,0x5,0x7,0xc,0x5,0x2,
              0xa,0xf,0x6,0x8,0x1,0x6,0x1,0x6,0x4,0xb,0xb,0xd,0xd,
              0x8,0xc,0x1,0x3,0x4,0x7,0xa,0xe,0x7,0xa,0x9,0xf,0x5,
              0x6,0x0,0x8,0xf,0x0,0xe,0x5,0x2,0x9,0x3,0x2,0xc
       },
       { 
              0xd,0x1,0x2,0xf,0x8,0xd,0x4,0x8,0x6,0xa,0xf,0x3,0xb,
              0x7,0x1,0x4,0xa,0xc,0x9,0x5,0x3,0x6,0xe,0xb,0x5,0x0,
              0x0,0xe,0xc,0x9,0x7,0x2,0x7,0x2,0xb,0x1,0x4,0xe,0x1,
              0x7,0x9,0x4,0xc,0xa,0xe,0x8,0x2,0xd,0x0,0xf,0x6,0xc,
              0xa,0x9,0xd,0x0,0xf,0x3,0x3,0x5,0x5,0x6,0x8,0xb
       } 
};

LINT32 DdesN(ULONG8 *data, ULONG8 key[KEYNUMMAX][KEYLENMAX], ULONG32 n_key,ULONG32 readlen)
{
       LINT32 i ;
       DESRES status = DESSUCCESS ;
       
       for ( i = n_key ; i > 0 ; i--)
       {
              Ddes(data,key[i-1],readlen);
       }
       return status;
}

LINT32 desN(ULONG8 *data, ULONG8 key[KEYNUMMAX][KEYLENMAX], ULONG32 n_key,ULONG32 readlen)
{
       DESRES status = DESSUCCESS ;
       ULONG32 i = 0;
       
       for ( i = 0 ; i < n_key ; i++)
       {
              des(data,key[i],readlen);
       }
       return status;
}

LINT32 des(ULONG8 *data, ULONG8 *key,LINT32 readlen)
{
       LINT32 i = 0;   
       DESRES status = DESSUCCESS ;
       
       makefirstkey((ULONG32*)key) ; 
       for ( i = 0 ; i < readlen ; i += 8)
       {
              handle_data( (ULONG32*)&data[i], DESENCRY );
       }
       return status;
}

LINT32 Ddes(ULONG8 *data,ULONG8 *key,LINT32 readlen)
{
       LINT32 i = 0;
       DESRES status = DESSUCCESS ;
       
       makefirstkey((ULONG32*)key) ;  
       for ( i = 0 ; i < readlen ; i += 8)
       {
              handle_data( (ULONG32*)&data[i] ,DESDECRY);
       }
       return status;
}

LINT32 handle_data(ULONG32 *left , ULONG8 choice)
{
       DESRES status = DESSUCCESS ;
       LINT32  number = 0 ;
       LINT32  j = 0;   
       ULONG32 *right = &left[1] ;
       ULONG32 tmp = 0;       
       ULONG32 tmpbuf[2] = { 0 };             

       for ( j = 0 ; j < 64 ; j++)
       {
              if (j < 32 ) 
              {
                     if ( wz_pc1[j] > 32) /* belongs to right part*/
                     {
                            if ( *right&wz_pc2[wz_pc1[j]-1] )
                            {
                                   tmpbuf[0] |= wz_pc2[j] ;
                            }
                     }
                     else
                     {
                            if ( *left&wz_pc2[wz_pc1[j]-1] )
                            {
                                   tmpbuf[0] |= wz_pc2[j] ;
                            }
                     }
              }
              else
              {
                     if ( wz_pc1[j] > 32) /* belongs to right part */
                     {
                            if ( *right&wz_pc2[wz_pc1[j]-1] )
                            {
                                   tmpbuf[1] |= wz_pc2[j] ;
                            }
                     }
                     else
                     {
                            if ( *left&wz_pc2[wz_pc1[j]-1] )
                            {
                                   tmpbuf[1] |= wz_pc2[j] ;
                            }
                     }
              }
       }
       *left  = tmpbuf[0] ;
       *right = tmpbuf[1];
       tmpbuf[0] = 0 ;
       tmpbuf[1] = 0 ;
    switch( choice )
       {
       case DESENCRY:
              for ( number = 0 ; number < 16 ; number++)
              {            
                     makedata( left , right , (ULONG32)number) ;
              }
              break;
       case DESDECRY:
              for ( number = 15 ; number >= 0 ; number--)
              {            
                     makedata( left , right ,(ULONG32)number) ;
              }
              break;
       default:
              break;
       }

       tmp = *left ;
       *left = *right ;
       *right = tmp ;        

       for ( j = 0 ; j < 64 ; j++)
       {
              if (j < 32 ) 
              {
                     if ( wz_pc4[j] > 32)
                     {
                            if ( *right&wz_pc2[wz_pc4[j]-1] )
                            {
                                   tmpbuf[0] |= wz_pc2[j] ;
                            }
                     }
                     else
                     {
                            if ( *left&wz_pc2[wz_pc4[j]-1] )
                            {
                                   tmpbuf[0] |= wz_pc2[j] ;
                            }
                     }
              }
              else
              {
                     if ( wz_pc4[j] > 32)
                     {
                            if ( *right&wz_pc2[wz_pc4[j]-1] )
                            {
                                   tmpbuf[1] |= wz_pc2[j] ;
                            }
                     }
                     else
                     {
                            if ( *left&wz_pc2[wz_pc4[j]-1] )
                            {
                                   tmpbuf[1] |= wz_pc2[j] ;
                            }
                     }
              }
       }
  
       *left =  tmpbuf[0] ;
       *right = tmpbuf[1];

       return status;
}


LINT32 makedata(ULONG32  *left ,ULONG32  *right ,ULONG32 number) 
{
        LINT32 j; 
	DESRES status = DESSUCCESS ;
        ULONG32 oldright = *right;         
        ULONG8 rexpbuf[8] = { 0} ;
        ULONG32 datatmp = 0;        
        ULONG32 exp[2] = { 0} ;        
                 
       //enlarge from 32bits to 48 bits
       for ( j = 0 ; j < 48 ; j++)
       {
              /* two 32 bits, store 24bit each */
              if ( j < 24 )
              {
                     if ( *right&wz_pc2[exptab3[j]-1] )
                     {
                            exp[0] |= wz_pc2[j] ;
                     }            
              }            
              else
              {
                     if ( *right&wz_pc2[exptab3[j]-1] )
                     {
                            exp[1] |= wz_pc2[j-24] ;
                     }
              }
       }

       for ( j = 0 ; j < 2 ; j++)
       {            
              exp[j] ^= g_outkey[number][j] ;
       }    

       /* from 48 bits to 32 bits */      

       exp[1] >>= 8 ;
       rexpbuf[7] = (ULONG8) (exp[1]&0x0000003fL) ;
       exp[1] >>= 6 ;
       rexpbuf[6] = (ULONG8) (exp[1]&0x0000003fL) ;
       exp[1] >>= 6 ;
       rexpbuf[5] = (ULONG8) (exp[1]&0x0000003fL) ;
       exp[1] >>= 6 ;
       rexpbuf[4] = (ULONG8) (exp[1]&0x0000003fL) ;
       exp[0]  >>=  8 ;
       rexpbuf[3] = (ULONG8) (exp[0]&0x0000003fL) ;     
       exp[0] >>= 6 ;
       rexpbuf[2] = (ULONG8) (exp[0]&0x0000003fL) ;
       exp[0] >>= 6 ;
       rexpbuf[1] = (ULONG8) (exp[0]&0x0000003fL) ;
       exp[0] >>= 6 ;
       rexpbuf[0] = (ULONG8) (exp[0]&0x0000003fL) ;     
       exp[0] = 0 ;
       exp[1] = 0 ;
 
       /* from 48 bits to 32 bits */

       *right = 0 ;
       for ( j = 0 ; j < 7 ; j++)
       {
              *right |= SP[j][rexpbuf[j]] ;
              *right <<= 4 ;
       }
       *right |= SP[j][rexpbuf[j]] ;

       datatmp = 0;
       for ( j = 0 ; j < 32 ; j++)
       {
              if ( *right&wz_pc2[wz_pc3[j]-1] )
              {
                     datatmp |= wz_pc2[j] ;
              }
       }
       *right = datatmp ;

       /* the end operation in the first round */                

       *right ^= *left;       
       *left = oldright;
 
       return status;
}

LINT32 makefirstkey( ULONG32 *keyP )
{
       DESRES status = DESSUCCESS ;
       ULONG32 key[2] = {0};
       ULONG32 *Pkey ;
       ULONG32 *Pbufkey ;
       LINT32 j; 
       Pbufkey = (ULONG32*)g_bufkey ;
       Pkey = (ULONG32*)key;
              
       memset((ULONG8*)g_bufkey,0,sizeof(g_bufkey));    
       memcpy((ULONG8*)&key,(ULONG8*)keyP ,8) ;      
       memset((ULONG8*)g_outkey,0,sizeof(g_outkey));

       // to get the initial 56 bits key
       for(  j = 0 ; j < 28 ; j++)
       {
              if ( wz_keyleft[j] > 32 ) 
              {
                     if ( Pkey[1]&wz_pc2[wz_keyleft[j]-1] )
                     {
                            Pbufkey[0] |= wz_pc2[j] ;
                     }
              }
              else
              {
                     if ( Pkey[0]&wz_pc2[wz_keyleft[j]-1] )
                     {
                            Pbufkey[0] |= wz_pc2[j] ;
                     }
              }
              
              if ( wz_keyright[j] > 32 ) 
              {
                     if ( Pkey[1]&wz_pc2[wz_keyright[j]-1] )
                     {
                            Pbufkey[1] |= wz_pc2[j];
                     }
              }
              else
              {
                     if ( Pkey[0]&wz_pc2[wz_keyright[j]-1] )
                     {
                            Pbufkey[1] |= wz_pc2[j];
                     }
              }
       }

       // 
       for (j = 0 ; j < 16 ; j++)
       {
              makekey(&Pbufkey[0],&Pbufkey[1] , j ) ;
       }
       return status;
}


LINT32 makekey(  ULONG32 *keyleft,ULONG32 *keyright ,ULONG32 number)
{
       DESRES status = DESSUCCESS ;
       ULONG32 tmpkey[2] ={0};
       ULONG32 *Ptmpkey = (ULONG32*)tmpkey;     
       ULONG32 *Poutkey = (ULONG32*)&g_outkey[number]; 
       LINT32 j;        
       memset((ULONG8*)tmpkey,0,sizeof(tmpkey));          
              /* get the top one or two bits */
              *Ptmpkey = *keyleft&wz_leftandtab[wz_lefttable[number]] ;           
              Ptmpkey[1] = *keyright&wz_leftandtab[wz_lefttable[number]] ;              
              if ( wz_lefttable[number] == 1)
              {
                     *Ptmpkey >>= 27;
                     Ptmpkey[1] >>= 27;
              }
              else
              {
                     *Ptmpkey >>= 26;
                     Ptmpkey[1] >>= 26;                    
              }
              Ptmpkey[0] &= 0xfffffff0;
              Ptmpkey[1] &= 0xfffffff0;
              /*get the value of the highest bits */
              *keyleft <<= wz_lefttable[number] ;
              *keyright <<= wz_lefttable[number] ;
              *keyleft |= Ptmpkey[0] ;
              *keyright |= Ptmpkey[1] ;            
              Ptmpkey[0] = 0;
              Ptmpkey[1] = 0;
    
       /* select 48 bits from 56 bits, it consist of 3 16bits */
       for ( j = 0 ; j < 48 ; j++)
       {
              if ( j < 24 )
              {
              
                            if ( *keyleft&wz_pc2[wz_keychoose[j]-1])
                            {
                                   Poutkey[0] |= wz_pc2[j] ;
                            }                   
              }            
              
              else /*j>=24*/
              {                   
                            if ( *keyright&wz_pc2[(wz_keychoose[j]-28)])
                            {
                                   Poutkey[1] |= wz_pc2[j-24] ;
                            }                   
              }
       }
       return status;
}


int handle_head_info(int fd, FILE_INFO *buf, MODE mode)
{
	int   offset ;
	FILE *fp ;
	fp = NULL ;

	if (mode == DESENCRY)
	{
		fp = fdopen(fd, "w") ;
	} 

	if (buf == NULL || fp == NULL)
	{
		fprintf(stderr, "handle_head_info: invalid parameter fp or buf.\n") ;
		return 1 ;
	}

	if (mode == DESENCRY)
	{
		fprintf(fp, "version=%s\n", buf->version) ;
		fprintf(fp, "padSize=%d\n", buf->padSiz) ;
		fflush(fp) ;
	}
	else
	{
		fprintf(stderr, "handle_head_info: invalid mode.\n") ;
		return 1 ;
	}

	fgetpos(fp, (fpos_t *)&offset);

	return offset;
}


DESRES do_des_encry(char *filename, char *desKey)
{
	ULONG8 	 key[16];	
	ULONG8	 keyLong[KEYNUMMAX][KEYLENMAX] ;	// if the length of key above 8, then 
					// divide it into two key
	ULONG8	 data[1024] ;
	ULONG32	 dlen ;		// the length of data we get each time
	int    	 klen ;		// length of key
	int   	 infd ;		// input file descriptor
	int	 outfd ;	// output file descriptor
	char	 tmpFnam[32] ;	
	int	 numRd ;
	int    	 left ;
	int	 offset ;
	struct stat statBuf ;
	FILE_INFO  finfo ;


	// initialize the key
      memset(key, 0, sizeof(key));
      klen =  strlen (desKey);
      if (klen <= 7) {
     	   pre_process_key (key, desKey, klen);
      }
      else if (klen <= 14){
	   pre_process_key (key, desKey, 7);
	   pre_process_key (key+8, desKey+7, klen-7);
      }
      else {
	   fprintf (stderr, "invalid key len") ;
	   return DESFAILED;
      }
	klen = strlen (key);
	printf("real key len=%d\n", klen);
	if (klen < 8)
	{
		if (klen == 6)
		{
			key[6] = ((key[0] + key[2] + key[4])/3) + 5 ;
			key[7] = (key[1] + key[3] + key[5])/3 + 5 ;
		}
		else if (klen == 7)
		{
			key[7] = (key[1] + key[3] + key[5])/3 ;
		}
		else
		{
			fprintf (stderr, "invalid key len") ;
			return DESFAILED;
		}

		key[8] = '\0' ;
	}
	else if (klen > 8)
	{
		memset(keyLong[0], '\0', 10) ;
		memset(keyLong[1], '\0', 10) ;
		strncpy(keyLong[0], key, 8) ;
		strncpy(keyLong[1], &key[klen-8], 8) ;
	}
	else // klen equals 8
	{
		;
	} //if

	// process the data to be handlered
	infd = open (filename, O_RDONLY) ;
	if (infd < 0)
	{
		fprintf (stderr, "Open input file %s failed.\n", filename) ;
		return DESFAILED;
	}

	strcpy(tmpFnam, filename) ;
	strncat(tmpFnam,  "XXXXXX", 6) ;
	outfd = mkstemp(tmpFnam) ;
	if (outfd < 0)
	{
		fprintf (stderr, "Open tmp file failed.\n") ;
		return DESFAILED;
	}

	memset(&finfo, '\0', sizeof(finfo)) ;
	memset(&statBuf, '\0', sizeof(statBuf)) ;
	fstat(infd, &statBuf) ;

	left = (statBuf.st_size)%8 ;
	if (left != 0)
	{
		finfo.padSiz = 8 - left ;
	}
	sprintf(finfo.version,"%s", "12.34.567") ;
	offset = handle_head_info(outfd, &finfo, DESENCRY) ;
	lseek(outfd, offset, SEEK_SET);

	do {
		numRd = 0 ;
		memset(data, '\0', 1024) ;
		numRd = read(infd, data, 1024) ;
		if (numRd < 0)
		{
			fprintf(stderr, "Error occurs when reading data from input file\n ") ;
			return DESFAILED;
		}
		
		dlen = numRd ;
		// to see if the size is the multiple of 8, if
		// not, fill with '0'
		left = numRd % 8 ;
		if (left != 0) {
			dlen = numRd + 8 - left ;
			strncat (&(data[numRd]), "00000000", 8-left) ;
		}

		if (klen > 8)
		{
			desN(data, keyLong, 2, dlen) ;
			
		} 
		else 
		{
			des(data, key, dlen) ;
		}
	
		write(outfd, data, dlen) ;
	} while (numRd == 1024) ;

	close(infd) ;
	close(outfd) ;

	unlink(filename) ;
	rename(tmpFnam, filename) ;
	
	return  DESSUCCESS ;

}

DESRES do_des_decry(const char *src, char *dst, char *desKey, FILE_INFO *buf, int curSiz)
{
	ULONG8 	 key[16];	
	ULONG8	 keyLong[KEYNUMMAX][KEYLENMAX] ;	// if the length of key above 8, then 
					// divide it into two key
	int    	 klen ;			// length of key

	memcpy(dst, src, curSiz) ;
	// initialize the key 
      memset(key, 0, sizeof(key));
      klen =  strlen (desKey);
      if (klen <= 7) {
     	   pre_process_key (key, desKey, klen);
      }
      else if (klen <= 14){
	   pre_process_key (key, desKey, 7);
	   pre_process_key (key+8, desKey+7, klen-7);
      }
      else {
	   fprintf (stderr, "invalid key len") ;
	   return DESFAILED;
      }
	klen = strlen (key);
	if (klen < 8)
	{
		if (klen == 6)
		{
			key[6] = ((key[0] + key[2] + key[4])/3) + 5 ;
			key[7] = (key[1] + key[3] + key[5])/3 + 5 ;
		}
		else if (klen == 7)
		{
			key[7] = (key[1] + key[3] + key[5])/3 ;
		}
		else
		{
			fprintf (stderr, "invalid key len") ;
			return DESFAILED;
		}

		key[8] = '\0' ;
	}
	else if (klen > 8)
	{
		memset(keyLong[0], '\0', 10) ;
		memset(keyLong[1], '\0', 10) ;
		strncpy(keyLong[0], key, 8) ;
		strncpy(keyLong[1], &key[klen-8], 8) ;
	}
	else // klen equals 8
	{
		;
	}
	
	if (klen > 8)
	{
		DdesN(dst, keyLong, 2, curSiz) ;
	} 
	else 
	{
		Ddes(dst, key, curSiz) ;
	}
	
	dst[curSiz -(buf->padSiz)] = '\0' ;
	
	return DESSUCCESS ;
}

/*
	Name :pre_process_key
	Parm: 
		src:  source key.
		dest: destination key.
		length: lenght of source key.
	Description:
		To fix the DES algorithm weakness.
		The key for DES encryption and decryption must lost 8 bits information.
		So some process are need to avoid it.s
*/

int pre_process_key(char *dest, char *src, int length){
        int i = 0;
        char added_byte = 0;
        strncpy(dest, src, length);
        dest[length] = '\0';
        for (; i<length; i++){
                added_byte = added_byte << 1;
                added_byte |= src[i] & MASKBIT;
        }
        added_byte = added_byte << 1;
        added_byte |= 1;
        dest[length] = added_byte;
        return 0;
}

int main()
{
  return 0;
}
