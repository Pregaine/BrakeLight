//-- Include Define ---------------------------------------------------------------      
#include "Gdefine.h"
#include "adxl345.h"
#include "EFM8SB1_PWM.h"
#include <math.h>
#include "ASI_Modbus.h"
#include "EFM8SB1_UART.h"
#include "Converter.h"

#define _DEBUG 1

// -- Global Function --------------------------------------------------------------
void Init_Device( void );
void Init_RAM( void );
void Init_GPIO( void );

// void Detect_Brake( void );
// void Detect_Brake_2( void );
// void Detect_Brake_3( void );
void Detect_Brake_4( void );
void System_Start( void );
void DBG_Print( S8 *text );


//-- Global Parameter ----------------------------------------------------------
// S16 xdata Gx_DET_BUF[ G_BUF_SIZE ];
S16 xdata Gy_DET_BUF[ G_BUF_SIZE ];
S16 xdata Gz_DET_BUF[ G_BUF_SIZE ];
// S16 Gy_lin_Avage[ 6 ];
S16 Gz_lin_Avage[ 8 ];
S16 Gx, Gy, Gz;

// U8 xdata FW_Verison[ 11 ] _at_ 0x0000;

U8 Hold_Active_Counter = 0;
U8 ExtTime;
u8 Ext50msec;

U16 Next_Compare_Value;       // Next edge to be sent out in HSO mode

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
SI_LOCATED_VARIABLE_NO_INIT( reserved, uint8_t, SI_SEG_XDATA, 0x0000 );

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

	DBG_Print( "Power On" );

#if 0
	while( 1 )
	{
		 ASI.status.light = _LightON;
		PWM_SetDuty( 20 ); // 17.8mA
		// PWM_SetDuty( 60 ); // 35.9mA
	}
#endif

	while( 1 )
	{

		if( ASI_Modbus_Decode( ) )
			ASI_Modbus_Response( );

		if( Ext50msec == Flag_Set && xl345_status == _SUCCESS )
		{
			Ext50msec = Flag_Clr;

			Detect_Brake_4();
		}

		ASI.status.brake = ( Hold_Active_Counter > 0 ) ?_BrakeLightON :ASI.status.brake_save;
			
		if( ASI.status.brake == _BrakeLightON )
		{
			// PWM_SetDuty( 50 );
			// PWM = 1;
		}
		else
		{
			// PWM_SetDuty( 20 );
			// PWM = 0;
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


void DBG_Print( S8 *text )
{
	U8 i;

	for( i = 0; text[i] != 0; ++i );	// Counting how many bytes in test[]

	UartWrite( (const U8 *)text, i );
}

// ============================================================================
//     Detect Brake
// ============================================================================

void Detect_Brake_4( void )
{
	s16 avage_z = 0, tmpz = 0;
	u8 i;

#if _DEBUG
	static u8 cn = 0;
	static u8 xdata str[ 8 ] = { 0 };
#endif

	// -- 讀G-Sensor資料 -------------------------------------------------
	Get_3X( &Gx, &Gy, &Gz );

	for( i = 7; i > 0; i -- )
	{
		Gz_DET_BUF[ i ] = Gz_DET_BUF[ i - 1 ];
	}

	Gz_DET_BUF[ 0 ] = Gz;
	// --------------------------------------

	for( i = 0; i < 8; i ++ )
		avage_z += Gz_DET_BUF[ i ];

	avage_z = avage_z / 8;
	// -------------------------------------

	for( i = 7; i > 0; i-- )
		Gz_lin_Avage[ i ] = Gz_lin_Avage[ i - 1 ];

	Gz_lin_Avage[ 0 ] = Gz - avage_z;

	for( i = 0; i < 8; i ++ )
		tmpz += Gz_lin_Avage[ i ];

	tmpz = tmpz / 8;
	// -------------------------------------

	if( Hold_Active_Counter > 0 )
	{
		Hold_Active_Counter--;
	}
	else if( ( tmpz < -9 ) && ( Gz_lin_Avage[ 0 ] < -25 ) && ( Gy > 265 ) )
	{
		Hold_Active_Counter = COUNTER_2s;
	}

	#if _DEBUG
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

	S16toStr( tmpz, str );
	DBG_Print( str );
	DBG_Print( "," );

	U16toStr( Hold_Active_Counter, str );
	DBG_Print( str );
	DBG_Print( "\r\n" );
	#endif

}

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
//-----------------------------------------------------------------------------
SI_INTERRUPT (PCA0_ISR, PCA0_IRQn)
{
	if( PCA0CN0_CCF0 )			// If Module 0 caused the interrupt
	{
		PCA0CN0_CCF0 = 0;       // Clear module 0 interrupt flag.

		PCA0CPL0 = ( Next_Compare_Value & 0x00FF );
		PCA0CPH0 = ( Next_Compare_Value & 0xFF00 )>>8;

		PWM = ( ASI.status.light == _LightON ) ?( ~PWM ) :( PWM_OFF );

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


