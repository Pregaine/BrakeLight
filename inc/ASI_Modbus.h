#ifndef _ASI_MODBUS_H_
#define _ASI_MODBUS_H_

#include"Typedef.h"

#define _ASI_CNOTROL_SLAVE_ID 	1
#define _SMART_BMS_SLAVE_ID		2
#define _SMART_LIGHT_SLAVE_ID 	3

#define _Cmd_ReadHoldReg 			0x03
#define _Cmd_WriteMultipleReg 		0x10

#define _ErrCode_ReadHoldReg 		0x83
#define _ErrCode_WriteMultipleReg	0x90

#define _LightON  0x0000
#define _LightOFF 0x0001

#define _BrakeLightON  0x0000
#define _BrakeLightOFF 0x0001

typedef enum
{
	_LightAdd = 0x00,

	_BrakeLightAdd = 0x01

}_SmartLightAdde;
	
typedef enum
{
	_INVALID_ADD = 0x02,
	_INVALID_NUM_OF_REG = 0x03

}_ExceptionCode;

typedef struct
{

	unsigned char SlaveID;
	unsigned char FunCode;
	_UU16 StartAdd;
	_UU16 NumOfReg;
	_UU16 Crc;

}_ReadHoldReg_Request_Stc;


typedef struct
{
	unsigned char SlaveID;
	unsigned char FunCode;
	unsigned char NumOfDataByte;
	unsigned char *NumOfRegPtr;
	_UU16 Crc;

}_ReadHoldReg_Response_Stc;

typedef struct 
{
	unsigned char SlaveID;
	unsigned char ErrCode;
	unsigned char ExcepCode;
	_UU16 Crc;
	
}_ReadHoldReg_ResponseErr_Stc;

typedef struct
{
	unsigned char SlaveID;
	unsigned char FunCode;
	_UU16 StartAdd;
	_UU16 NumOfReg;
	unsigned char NumOfDataByte;
	unsigned char *NumOfDataBytePtr;
	_UU16 Crc;
	
}_WriteMultipleReg_Request_Stc;

typedef struct
{
	unsigned char SlaveID;
	unsigned char FunCode;
	_UU16 StartAdd;
	_UU16 NumberOfReg;
	_UU16 Crc;

}_WriteMultipleReg_Response_Stc;

typedef struct 
{
	unsigned char SlaveID;
	unsigned char ErrCode;
	_ExceptionCode ExcepCode;
	_UU16 Crc;
	
}_WriteMultipleReg_ResponseErr_Stc;

typedef struct
{
	u16 light;
	u16 brake;
	
}_Reg;

typedef struct
{
	_Reg status;
	
}_ASI_Stc;

extern _ASI_Stc xdata ASI;
extern void ASI_Modbus_Init( );
extern unsigned char ASI_Modbus_Decode( void );
extern void ASI_Modbus_Response( void );

#endif
