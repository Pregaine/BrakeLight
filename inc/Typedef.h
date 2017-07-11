#ifndef _TYPEDEF_
#define _TYPEDEF_
#include <stdint.h>
#include <stddef.h>

typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32;
typedef char S8;
typedef int S16;
typedef long S32;

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
typedef char s8;
typedef int s16;
typedef long s32;

typedef union
{
  U16 word;   		//< The two byte value as a 16-bit unsigned integer.
  U8 byte[ 2 ];  	//< The two byte value as two unsigned 8-bit integers.

}_UU16;


typedef union
{

  u32 dword;    //< The 4-byte value as a 32-bit unsigned integer.
  u16 word[2];    	//< The 4-byte value as two unsigned 16-bit integers.
  u8  byte[4];      //< The 4-byte value as 4 unsigned 8-bit integers.
  
}_UU32;


#define _SUCCESS  0
#define _FAIL     1

#define ON		 1
#define OFF		 0

#define HIGH_LEVEL	1
#define LOW_LEVEL	0

#define ArrayLength(x)  (sizeof(x) / sizeof(x[0]))
#endif

