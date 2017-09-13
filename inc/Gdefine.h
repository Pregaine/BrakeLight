#include "Typedef.h"
#include "SI_EFM8SB1_Register_Enums.h"
#ifndef _GDEFINE_H_
#define _GDEFINE_H_

//-- Flag Control define ------------------------------------------------------- 
#define	Flag_Clr				0
#define	Flag_Set				1

#define	PWM_ON					1
#define	PWM_OFF					0				

//-- Light Control define ------------------------------------------------------
#define	AUTO_MODE				0xAA		// Cohesion Mode
#define	DISCHARGE_MODE			0xAB		// Discharge Mode
#define Light_IDEL				0xAC		// Light idel Mode

#define	Current_TUNING_RANGE	1
#define	HIGH_SPEED_RANGE		5
#define	STABLE_THR				30

#define	PWM_MIN_DUTY			6
#define	PWM_MAX_DUTY			254
#define	PWM_MIN_DUTY1			4
#define	PWM_MAX_DUTY1			254
#define PWM_80Hz				81
#define	PWM_500Hz				13

#define	PWM_DUTY				190

//-- Key define ----------------------------------------------------------------
#define	Release_Key				1
#define	Push_Key				0

#define	COUNTER_3s				60				// 3s
#define	COUNTER_2s				40				// 2s
#define	COUNTER_1s5				75				// 1.5s
#define	COUNTER_1s				50				// 1s
#define	COUNTER_512ms			25				// 512ms
#define	COUNTER_400ms			20				// 400ms
#define	COUNTER_300ms			15				// 300ms
#define	COUNTER_250ms			13				// 250ms
#define	COUNTER_200ms			10				// 200ms
#define	COUNTER_150ms			8				// 300ms
#define	COUNTER_100ms			5				// 100ms
#define	COUNTER_80ms			4				// 80ms
#define	COUNTER_60ms			3				// 60ms
#define	COUNTER_40ms			2				// 40ms
#define	COUNTER_20ms			1				// 40ms

#define	Push_level				250
#define	Push_range				20

//-- 震動開關 define -----------------------------------------------------------
#define	Def_Loop				10000

//-- PWM define ----------------------------------------------------------------
#define	Duty_cal(x,y)			y*(255-x)
#define	Duty_cal1(x,y)			y*x
#define Duty_cal2(x,y)			x-y
#define Duty_cal3(x,y)			(x>>8)*y
#define	Duty_cal4(x,y)			x-((x>>8)*y)

#define SENSOR_RESPONSE			0
#define	SENSOR_DETECT			1
#define	OTHER_LOWDUTY			2
#define	HIGHDUTY_END			3
#define	HIGHDUTY_START			4
#define GENERAL_H				5
#define	GENERAL_L				6
#define	HIGHBAME_END			7

//-- SLEEP Mode Define --------------------------------------------------------
#define	BUTTON					0x01
#define	USB						0x02
#define	VR						0x04
#define	DEFAULT					0x03

//-- Morning Detection Define --------------------------------------------------
#define	MORNING_UP_BOUND		163//185//172		2.5(V) * 0.5(ADC Gain) / 6(mV, 1.65V/256) = 208

//-- G-Sensor Define -----------------------------------------------------------
#define	G_BUF_SIZE				8 //32

// G-Force Value define
#define	G_FORCE_0G01							3
#define	G_FORCE_0G02							5
#define	G_FORCE_0G03							8
#define	G_FORCE_0G04							11
#define	G_FORCE_0G05							13
#define	G_FORCE_0G08							20
#define	G_FORCE_0G1								26
#define	G_FORCE_0G12							31
#define	G_FORCE_0G15							38
#define	G_FORCE_0G16							40
#define	G_FORCE_0G2								51
#define	G_FORCE_0G25							64
#define	G_FORCE_0G3								77
#define	G_FORCE_0G4								102
#define	G_FORCE_0G5								128
#define	G_FORCE_0G55							141
#define	G_FORCE_0G6								154	
#define	G_FORCE_0G65							166
#define	G_FORCE_0G7								179
#define	G_FORCE_0G75							192
#define	G_FORCE_0G8								205
#define	G_FORCE_0G85							213
#define	G_FORCE_0G9								230
#define	G_FORCE_1G0								256
#define	G_FORCE_1G01							259
#define	G_FORCE_1G02							261
#define	G_FORCE_1G03							264
#define	G_FORCE_1G05							269
#define	G_FORCE_1G08							276
#define	G_FORCE_1G1								282
#define	G_FORCE_1G2								307
#define	G_FORCE_1G3								333
#define	G_FORCE_1G4								358
#define	G_FORCE_1G5								384

// -- 煞車判斷狀態 -------------------------------------------
#define	CHECK_START								0xD0
#define WAIT_HOLD_TIME							0xD1

// -- 煞車判斷的Threshold ------------------------------------
#define	BRAKE_THR								G_FORCE_0G05//G_FORCE_0G1//G_FORCE_0G2//G_FORCE_0G3
#define	BRAKE_Gx_THR							G_FORCE_0G2

//------------------------------------------------------------------------------
// Port I/O define
//------------------------------------------------------------------------------
sbit TX = P0 ^ 4;			// 
sbit RX = P0 ^ 5;			// 

sbit M_SPI_CLK = P0 ^ 6;	// ADXL345 SPI
sbit M_SPI_MISO = P0 ^ 7;	//
sbit M_SPI_MOSI = P1 ^ 0;	//
sbit M_SPI_NSS = P1 ^ 1;	//

sbit G_INIT = P1 ^ 2;		//
sbit PWM = P1 ^ 3;			// 

#endif
