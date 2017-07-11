//-- Include Define ---------------------------------------------------------------      
#include "Gdefine.h"
#include "adxl345.h"
#include "EFM8SB1_PWM.h"
#include <math.h>
#include "ASI_Modbus.h"
#include "EFM8SB1_UART.h"
#include "Converter.h"

// #define _DEBUG

// -- Global Function --------------------------------------------------------------
void Init_Device( void );
void Init_RAM( void );
void Init_GPIO( void );

void System_Sleep( void );

//void Detect_Brake( void );
void Detect_Brake_2( void );
void System_Start( void );

//-- Global Parameter ----------------------------------------------------------
S16 Gz_DET_BUF[ G_BUF_SIZE ];
S16 Gx_DET_BUF[ G_BUF_SIZE ];
S16 Gy_DET_BUF[ G_BUF_SIZE ];
S16 Gx, Gy, Gz;

// U8 xdata FW_Verison[ 11 ] _at_ 0x0000;

U8 Hold_Active_Counter = 0;

U8 ExtTime;
// bit SYS_SLEEP;
u8 Ext50msec;
// bit Power_State;

/*
struct
{
	u8 EN_Correction :1;
	u8 Correction_DO :1;
	u8 G_BUF_Full :1;
	u8 Brake_Flag :1;

	u8 :4;
}xdata G;
*/

U16 Next_Compare_Value;       // Next edge to be sent out in HSO mode

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
// SI_LOCATED_VARIABLE_NO_INIT (reserved, uint8_t, SI_SEG_XDATA, 0x0000);

//=============================================================================
//    Main Function
//=============================================================================
void main( void )
{
	u8 xl345_status = _FAIL;

	Init_Device();						// HW Device Initial
	Init_GPIO();						// Initial GPIO
	Init_RAM();

	ASI_Modbus_Init();
	System_Start();

	xl345_status = ADXL345_Initiate();

	PWM_Init();

#if 0
	while( 1 )
	{
		// PWM_SetDuty( 30 ); // 17.8mA
		PWM_SetDuty( 60 ); // 35.9mA
	}
#endif

	while( 1 )
	{
		if( ASI_Modbus_Decode( ) )
			ASI_Modbus_Response();

		if( Ext50msec == Flag_Set && xl345_status == _SUCCESS )
		{
			Ext50msec = Flag_Clr;

			// Detect_Brake();
			Detect_Brake_2();
		}

		if( ASI.status.brake == _BrakeLightON || 
			ASI.status.light == _LightON ||
			Hold_Active_Counter > 0 )
		{
			PWM_SetDuty( 60 );
		}
		else
		{
			PWM_SetDuty( 20 );
		}
	}
}
// ============================================================================
//     Initial RAM 
// ============================================================================
void Init_RAM( void )
{

	ExtTime = 0;									// Clear Timer0 Counter

	TX_Ready = 1;                       // Flag showing that UART can transmit

	/*
	FW_Verison[ 0 ] = '0';
	FW_Verison[ 1 ] = 'N';
	FW_Verison[ 2 ] = 'K';
	FW_Verison[ 3 ] = 'G';
	FW_Verison[ 4 ] = '7';
	FW_Verison[ 5 ] = 'K';
	FW_Verison[ 6 ] = '0';
	FW_Verison[ 7 ] = '0';
	FW_Verison[ 8 ] = 'B';		// B: ET-3175-R
	FW_Verison[ 9 ] = '0';
	FW_Verison[ 10 ] = '0';
	*/

}
// ============================================================================
//     Initial Pin state
// ============================================================================
void Init_GPIO( void )
{
	PWM = PWM_OFF;		// Turn Off Main LED
	TX = 1;				// Disable Light Sensor
	RX = 1;

	M_SPI_CLK = 1;
	M_SPI_MISO = 1;
	M_SPI_MOSI = 1;
	M_SPI_NSS = 1;
	G_INIT = 1;
}

void System_Start( void )
{
	// == 設定開機抓G-Sensor的參考值 ==================
	// G.EN_Correction = Flag_Set;
	// G.Correction_DO = Flag_Clr;
	// G.Brake_Flag    = Flag_Clr;							// LED保持全亮
	Ext50msec      = Flag_Clr;
	// ================================================ 

	/*
	if( Power_State == Flag_Clr )
	{
		PWM = PWM_OFF;
		Flicker_Time = 0;
		Flicker_Flag = Flag_Set;

		// == 設定開機抓G-Sensor的參考值 ==================
		G.EN_Correction = Flag_Set;
		G.Correction_DO = Flag_Clr;
		G.Brake_Flag = Flag_Set;						// LED保持全亮
		// ================================================					

		Light_Mode = AUTO_MODE;							// Light Mode = Cohesion Mode
		Power_State = Flag_Set;
	}
	else
	{
		Power_State = Flag_Clr;
		Light_Mode = Light_IDEL;
		PWM = PWM_OFF;
		SYS_SLEEP = Flag_Set;							// Enable Sleep Mode					
	}
	*/
}

// ============================================================================
//     System Sleep
// ============================================================================
void System_Sleep( void )
{
	U8 CLKSEL_save;
	U8 EA_save;
	U8 IP_save;

	// Save current interrupt state and disable interrupts
	EA_save = IE_EA;
	IE_EA = 0;
	IP_save = IP;

	// Save current system clock selection and select the low power oscillator
	// divided by 2 as the system clock
	CLKSEL_save = CLKSEL;
	CLKSEL = 0x04;
	while( (!CLKSEL & 0x80) )
		;           	// Wait until CLKRDY -> 1

	// Enable the Flash read one-shot timer
	FLSCL &= ~0x40;                 	// Clear the one-shot bypass bit
	IP = 0x01;							// Write a "dummy" value to FLWR

	PMU0CF = 0x20;

	// ~~~ Device in Low Power Mode ~~~
	PMU0CF = 0x82;
	NOP();
	NOP();
	NOP();
	NOP();
	//----------------------------------

	// Restore the System Clock
	CLKSEL = CLKSEL_save;
	while( !(CLKSEL & 0x80) )
		;            	// Wait until CLKRDY -> 1

	// Disable (Bypass) the Flash Read one-shot timer if the system clock
	FLSCL |= 0x40;                	// Set the one-shot bypass bit

	// Capture the wake-up source and clear all wake-up source flags
	PMU0CF = 0x20;

	// Restore Interrupt State
	IP = IP_save;
	IE_EA = EA_save;
}

// ============================================================================
//     Sleep Processor 
// ============================================================================
#if 0
void Sleep_Process( void )
{
	if( SYS_SLEEP == Flag_Set )
	{
		Init_GPIO();
		Init_RAM();

		PCA0CPM0 = 0x00;
		PCA0CN0_CR = 0;

		// Power_State = Flag_Clr;

		P0MDIN = 0xC0;
		P0MASK = 0xC0;
		P0MAT = 0x40;

		P1MDIN = 0x00;
		P1MDOUT = 0x00;
		XBR2 = 0xC0;

		ADC0CN0_ADEN = 0;

		System_Sleep();
		// SYS_SLEEP = Flag_Clr;

		P0MDIN = 0x79;
		P0MASK = 0x00;
		P1MDIN = 0x03;
		P1MDOUT = 0x03;
		XBR2 = 0x40;

		Init_GPIO();
	}
}
#endif


void DBG_Print( S8 *text )
{
	U8 i;

	for( i = 0; text[i] != 0; ++i );	// Counting how many bytes in test[]

	UartWrite( (const U8 *)text, i );
}

// ============================================================================
//     Detect Brake
// ============================================================================
#if 0
void Detect_Brake( void )
{
	U8 i;
	s16 tmpx = 0, tmpy = 0, tmpz = 0;


	// -- 讀G-Sensor資料 -------------------------------------------------
	Get_3X(&Gx, &Gy, &Gz);

	for( i = 7; i > 0; i -- )
	{
		Gz_DET_BUF[ i ] = Gz_DET_BUF[ i - 1 ];
		Gx_DET_BUF[ i ] = Gx_DET_BUF[ i - 1 ];
		Gy_DET_BUF[ i ] = Gy_DET_BUF[ i - 1 ];
	}

	Gz_DET_BUF[ 0 ] = Gz;
	Gx_DET_BUF[ 0 ] = Gx;
	Gy_DET_BUF[ 0 ] = Gy;

	for( i = 0; i < 8; i ++ )
	{
		tmpx += Gx_DET_BUF[ i ];
		tmpy += Gy_DET_BUF[ i ];
		tmpz += Gz_DET_BUF[ i ];
	}

	tmpx = tmpx / 8;
	tmpy = tmpy / 8;
	tmpz = tmpz / 8;

	if( ( abs( tmpx - Gx ) > 20 ) || ( abs( tmpy - Gy ) > 20 ) )
	{
		Gz_DET_BUF[ 0 ] = tmpz;
		Gx_DET_BUF[ 0 ] = tmpx;
		Gy_DET_BUF[ 0 ] = tmpy;
	}
	else if( Hold_Active_Counter > 0 )
	{
		NOP();
	}
	else if( ( Gz_DET_BUF[ 0 ] < 35 ) && 
		     ( Gz_DET_BUF[ 0 ] > -20 ) &&
			 ( Gz_DET_BUF[ 0 ] < ( tmpz - 20 ) ) )
	{
		Hold_Active_Counter = COUNTER_2s;
	}
	// ----------------------------------

	if( Hold_Active_Counter > 0 )
		Hold_Active_Counter--;

	#if 0
	static u8 cn = 0;
	static u8 xdata str[ 8 ] = { 0 };
	cn = cn + 1;
	U16toStr( cn, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( Gx, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( Gy, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( Gz, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( tmpx, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( tmpy, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( tmpz, str );
	DBG_Print( str );
	DBG_Print( "," );

	U16toStr( Hold_Active_Counter, str );
	DBG_Print( str );
	DBG_Print( "\n" );
	#endif
}
#endif

#if 1
void Detect_Brake_2( void )
{
	U8 i;
	s16 tmpx = 0, tmpy = 0, tmpz = 0, tmpdz = 0;

#ifdef _DEBUG
	static u8 cn = 0;
	static u8 xdata str[ 8 ] = { 0 };
#endif

	// -- 讀G-Sensor資料 -------------------------------------------------
	Get_3X(&Gx, &Gy, &Gz);

	for( i = 5; i > 0; i -- )
	{
		Gz_DET_BUF[ i ] = Gz_DET_BUF[ i - 1 ];
		Gy_DET_BUF[ i ] = Gy_DET_BUF[ i - 1 ];
	}

	Gz_DET_BUF[ 0 ] = Gz;
	Gy_DET_BUF[ 0 ] = Gy;

	for( i = 0; i < 4; i ++ )
	{
		tmpy += ( Gy_DET_BUF[ i ] );
		tmpz += ( Gz_DET_BUF[ i ] );
	}

	for( i = 0; i < 4; i ++ )
	{
		tmpdz += ( Gz_DET_BUF[ i ] - Gz_DET_BUF[ i + 1 ] );
	}

	tmpy  = tmpy / 4;
	tmpz  = tmpz / 4;
	tmpdz = tmpdz / 4;

	if( Hold_Active_Counter > 0 )
	{
		NOP();
	}
	else if( ( tmpz < 50 ) && ( tmpdz <= -2 ) &&
			 ( ( tmpy >= 267 ) || ( tmpy <= -245 ) ) )
	{
		Hold_Active_Counter = COUNTER_2s;
	}
	// ----------------------------------

	if( Hold_Active_Counter > 0 )
		Hold_Active_Counter--;

#ifdef _DEBUG
	cn = cn + 1;
	U16toStr( cn, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( Gy, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( Gz, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( tmpy, str );
	DBG_Print( str );
	DBG_Print( "," );


	S16toStr( tmpz, str );
	DBG_Print( str );
	DBG_Print( "," );

	S16toStr( tmpdz, str );
	DBG_Print( str );
	DBG_Print( "," );

	U16toStr( Hold_Active_Counter, str );
	DBG_Print( str );
	DBG_Print( "\n" );
	#endif
}
#endif
// ============================================================================
//     LED Control 
// ============================================================================

//-----------------------------------------------------------------------------
// TIMER2_ISR
//-----------------------------------------------------------------------------
//
// TIMER2 ISR Content goes here. Remember to clear flag bits:
// TMR2CN0::TF2H (Timer # High Byte Overflow Flag)
// TMR2CN0::TF2L (Timer # Low Byte Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER2_ISR, TIMER2_IRQn)
{
	if( ExtTime )
	{
		ExtTime--;
	}
	else if( ExtTime == 0 )
	{
		ExtTime   = 50;
		Ext50msec = Flag_Set;
	}

	TMR2CN0_TF2H = 0;                   // Reset Interrupt
}

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
//
// PCA0 ISR Content goes here. Remember to clear flag bits:
// PCA0CN0::CCF0 (PCA Module 0 Capture/Compare Flag)
// PCA0CN0::CCF1 (PCA Module 1 Capture/Compare Flag)
// PCA0CN0::CCF2 (PCA Module 2 Capture/Compare Flag)
// PCA0CN0::CF (PCA Counter/Timer Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (PCA0_ISR, PCA0_IRQn)
{
	if (PCA0CN0_CCF0)                           // If Module 0 caused the interrupt
	{
	  PCA0CN0_CCF0 = 0;                        // Clear module 0 interrupt flag.

	  PCA0CPL0 = ( Next_Compare_Value & 0x00FF );
	  PCA0CPH0 = ( Next_Compare_Value & 0xFF00 )>>8;

	  PWM = ~PWM;			// Invert the LED pin

	  if( PWM == PWM_ON )
	  {
	  	// Set up the variable for the following edge
	  	Next_Compare_Value = PCA0CP0 + PWM_H_TIME;
	  }
	  else
	  {
	  	// Set up the variable for the following edge
	  	Next_Compare_Value = PCA0CP0 + PWM_L_TIME;
	  }
	}
	else                                // Interrupt was caused by other bits.
	{
	  PCA0CN0 &= ~0x86;                 // Clear other interrupt flags for PCA
	}
}


