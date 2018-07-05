#ifndef _DES_H_
#define _DES_H_
#if defined(__cplusplus)
extern "C" {
#endif

/************************** DATA type Defining ***********************/
typedef unsigned char ULONG8 ;
typedef int  LINT32 ;
typedef unsigned long  ULONG32 ;

typedef enum 
{
	DESSUCCESS,
	DESFAILED
} DESRES ;

typedef enum
{
	DESENCRY,
	DESDECRY
} MODE ;

typedef struct 
{
	char	version[32] ;	// current psi version
	LINT32	padSiz ;		// the number of '0' added to the end of the file
} FILE_INFO ;

#define KEYLENMAX  10
#define KEYNUMMAX  2

/*Bit mask for pre_process_key*/
#define MASKBIT 0x01

/************************** Function Declaration **************************/
LINT32 DdesN(ULONG8 *data, ULONG8 key[KEYNUMMAX][KEYLENMAX], ULONG32 n_key,ULONG32 readlen) ;
LINT32 desN(ULONG8 *data, ULONG8 key[KEYNUMMAX][KEYLENMAX], ULONG32 n_key,ULONG32 readlen) ;
LINT32 des(ULONG8 *data, ULONG8 *key,LINT32 readlen) ;
LINT32 Ddes(ULONG8 *data,ULONG8 *key,LINT32 readlen) ;
LINT32 handle_data(ULONG32 *left , ULONG8 choice) ;
LINT32 makedata(ULONG32  *left ,ULONG32  *right ,ULONG32 number)  ;
LINT32 makefirstkey( ULONG32 *keyP ) ;
LINT32 makekey(  ULONG32 *keyleft,ULONG32 *keyright ,ULONG32 number) ;

int handle_head_info(int fd, FILE_INFO *buf, MODE mode) ;
DESRES do_des_encry(char *filename, char *desKey) ;
DESRES do_des_decry(const char *src, char *dst, char *desKey, FILE_INFO *buf, int curSiz);
int pre_process_key(char * dest, char * src, int length);

#if defined (__cplusplus)
}
#endif
#endif 

