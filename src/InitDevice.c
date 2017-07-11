/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "SI_EFM8SB1_Register_Enums.h"

//================================================================================
// PCA_0_enter_DefaultMode_from_RESET
//================================================================================
void PCA_0_enter_DefaultMode_from_RESET( void )
{
	// $[PCA0MD - PCA Mode]
	/*
	 // WDTE (Watchdog Timer Enable) = DISABLED (Disable Watchdog Timer.)
	 // CPS (PCA Counter/Timer Pulse Select) = SYSCLK_DIV_12 (System clock
	 //     divided by 12.)
	 // CIDL (PCA Counter/Timer Idle Control) = NORMAL (PCA continues to
	 //     function normally while the system controller is in Idle Mode.)
	 // ECF (PCA Counter/Timer Overflow Interrupt Enable) = OVF_INT_DISABLED
	 //     (Disable the CF interrupt.)
	 // WDTE (Watchdog Timer Enable) = DISABLED (Disable Watchdog Timer.)
	 // WDLCK (Watchdog Timer Lock) = UNLOCKED (Watchdog Timer Enable
	 //     unlocked.)
	 */
	SFRPAGE = 0x00;
	PCA0MD &= ~PCA0MD_WDTE__BMASK;
	PCA0MD = PCA0MD_CPS__SYSCLK_DIV_12 | PCA0MD_CIDL__NORMAL
			| PCA0MD_ECF__OVF_INT_DISABLED
			| PCA0MD_WDTE__DISABLED | PCA0MD_WDLCK__UNLOCKED;
	// [PCA0MD - PCA Mode]$

	// $[PCA0H - PCA Counter/Timer High Byte]
	// [PCA0H - PCA Counter/Timer High Byte]$

	// $[PCA0L - PCA Counter/Timer Low Byte]
	// [PCA0L - PCA Counter/Timer Low Byte]$

	// $[PCA0PWM - PCA PWM Configuration]
	// [PCA0PWM - PCA PWM Configuration]$

	// $[PCA0CN0 - PCA Control 0]
	/*
	 // CR (PCA Counter/Timer Run Control) = RUN (Start the PCA Counter/Timer
	 //     running.)
	 */
	PCA0CN0 |= PCA0CN0_CR__RUN;
	// [PCA0CN0 - PCA Control 0]$
}

//================================================================================
// VREG_0_enter_DefaultMode_from_RESET
//================================================================================
void VREG_0_enter_DefaultMode_from_RESET( void )
{
	// $[REG0CN - Voltage Regulator Control]
	/*
	 // OSCBIAS (High Frequency Oscillator Bias) = ENABLED (Enable the
	 //     precision High Frequency Oscillator bias.)
	 */
	REG0CN = REG0CN_OSCBIAS__ENABLED;
	// [REG0CN - Voltage Regulator Control]$

}

//================================================================================
// PORTS_0_enter_DefaultMode_from_RESET
//================================================================================
void PORTS_0_enter_DefaultMode_from_RESET( void )
{
	// $[P0 - Port 0 Pin Latch]
	// [P0 - Port 0 Pin Latch]$

	// $[P0MDOUT - Port 0 Output Mode]
	/*
	 // B0 (Port 0 Bit 0 Output Mode) = OPEN_DRAIN (P0.0 output is open-
	 //     drain.)
	 // B1 (Port 0 Bit 1 Output Mode) = OPEN_DRAIN (P0.1 output is open-
	 //     drain.)
	 // B2 (Port 0 Bit 2 Output Mode) = OPEN_DRAIN (P0.2 output is open-
	 //     drain.)
	 // B3 (Port 0 Bit 3 Output Mode) = OPEN_DRAIN (P0.3 output is open-
	 //     drain.)
	 // B4 (Port 0 Bit 4 Output Mode) = PUSH_PULL (P0.4 output is push-pull.)
	 // B5 (Port 0 Bit 5 Output Mode) = OPEN_DRAIN (P0.5 output is open-
	 //     drain.)
	 // B6 (Port 0 Bit 6 Output Mode) = PUSH_PULL (P0.6 output is push-pull.)
	 // B7 (Port 0 Bit 7 Output Mode) = OPEN_DRAIN (P0.7 output is open-
	 //     drain.)
	 */
	P0MDOUT = P0MDOUT_B0__OPEN_DRAIN | P0MDOUT_B1__OPEN_DRAIN
			| P0MDOUT_B2__OPEN_DRAIN
			| P0MDOUT_B3__OPEN_DRAIN | P0MDOUT_B4__PUSH_PULL
			| P0MDOUT_B5__OPEN_DRAIN
			| P0MDOUT_B6__PUSH_PULL | P0MDOUT_B7__OPEN_DRAIN;
	// [P0MDOUT - Port 0 Output Mode]$

	// $[P0MDIN - Port 0 Input Mode]
	// [P0MDIN - Port 0 Input Mode]$

	// $[P0SKIP - Port 0 Skip]
	/*
	 // B0 (Port 0 Bit 0 Skip) = SKIPPED (P0.0 pin is skipped by the
	 //     crossbar.)
	 // B1 (Port 0 Bit 1 Skip) = SKIPPED (P0.1 pin is skipped by the
	 //     crossbar.)
	 // B2 (Port 0 Bit 2 Skip) = SKIPPED (P0.2 pin is skipped by the
	 //     crossbar.)
	 // B3 (Port 0 Bit 3 Skip) = SKIPPED (P0.3 pin is skipped by the
	 //     crossbar.)
	 // B4 (Port 0 Bit 4 Skip) = NOT_SKIPPED (P0.4 pin is not skipped by the
	 //     crossbar.)
	 // B5 (Port 0 Bit 5 Skip) = NOT_SKIPPED (P0.5 pin is not skipped by the
	 //     crossbar.)
	 // B6 (Port 0 Bit 6 Skip) = NOT_SKIPPED (P0.6 pin is not skipped by the
	 //     crossbar.)
	 // B7 (Port 0 Bit 7 Skip) = NOT_SKIPPED (P0.7 pin is not skipped by the
	 //     crossbar.)
	 */
	P0SKIP = P0SKIP_B0__SKIPPED | P0SKIP_B1__SKIPPED | P0SKIP_B2__SKIPPED
			| P0SKIP_B3__SKIPPED | P0SKIP_B4__NOT_SKIPPED
			| P0SKIP_B5__NOT_SKIPPED
			| P0SKIP_B6__NOT_SKIPPED | P0SKIP_B7__NOT_SKIPPED;
	// [P0SKIP - Port 0 Skip]$

	// $[P0MASK - Port 0 Mask]
	// [P0MASK - Port 0 Mask]$

	// $[P0MAT - Port 0 Match]
	// [P0MAT - Port 0 Match]$

	// $[P0DRV - Port 0 Drive Strength]
	// [P0DRV - Port 0 Drive Strength]$

}

//================================================================================
// PORTS_1_enter_DefaultMode_from_RESET
//================================================================================
void PORTS_1_enter_DefaultMode_from_RESET( void )
{
	// $[P1 - Port 1 Pin Latch]
	// [P1 - Port 1 Pin Latch]$

	// $[P1MDOUT - Port 1 Output Mode]
	/*
	 // B0 (Port 1 Bit 0 Output Mode) = PUSH_PULL (P1.0 output is push-pull.)
	 // B1 (Port 1 Bit 1 Output Mode) = PUSH_PULL (P1.1 output is push-pull.)
	 // B2 (Port 1 Bit 2 Output Mode) = OPEN_DRAIN (P1.2 output is open-
	 //     drain.)
	 // B3 (Port 1 Bit 3 Output Mode) = OPEN_DRAIN (P1.3 output is open-
	 //     drain.)
	 // B4 (Port 1 Bit 4 Output Mode) = OPEN_DRAIN (P1.4 output is open-
	 //     drain.)
	 // B5 (Port 1 Bit 5 Output Mode) = PUSH_PULL (P1.5 output is push-pull.)
	 // B6 (Port 1 Bit 6 Output Mode) = OPEN_DRAIN (P1.6 output is open-
	 //     drain.)
	 // B7 (Port 1 Bit 7 Output Mode) = OPEN_DRAIN (P1.7 output is open-
	 //     drain.)
	 */
	P1MDOUT = P1MDOUT_B0__PUSH_PULL | P1MDOUT_B1__PUSH_PULL
			| P1MDOUT_B2__PUSH_PULL
			| P1MDOUT_B3__PUSH_PULL | P1MDOUT_B4__OPEN_DRAIN
			| P1MDOUT_B5__PUSH_PULL
			| P1MDOUT_B6__OPEN_DRAIN | P1MDOUT_B7__OPEN_DRAIN;
	// [P1MDOUT - Port 1 Output Mode]$

	// $[P1MDIN - Port 1 Input Mode]
	// [P1MDIN - Port 1 Input Mode]$

	// $[P1SKIP - Port 1 Skip]
	P1SKIP = P1SKIP_B2__SKIPPED | P1SKIP_B3__SKIPPED;
	// [P1SKIP - Port 1 Skip]$

	// $[P1MASK - Port 1 Mask]
	// [P1MASK - Port 1 Mask]$

	// $[P1MAT - Port 1 Match]
	// [P1MAT - Port 1 Match]$

	// $[P1DRV - Port 1 Drive Strength]
	// [P1DRV - Port 1 Drive Strength]$

}

//================================================================================
// PBCFG_0_enter_DefaultMode_from_RESET
//================================================================================
void PBCFG_0_enter_DefaultMode_from_RESET( void )
{
	// $[XBR2 - Port I/O Crossbar 2]
	/*
	 // WEAKPUD (Port I/O Weak Pullup Disable) = PULL_UPS_ENABLED (Weak
	 //     Pullups enabled (except for Ports whose I/O are configured for analog
	 //     mode).)
	 // XBARE (Crossbar Enable) = ENABLED (Crossbar enabled.)
	 */
	XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED;
	// [XBR2 - Port I/O Crossbar 2]$

	// $[XBR0 - Port I/O Crossbar 0]
	/*
	 // URT0E (UART I/O Output Enable) = ENABLED (UART TX, RX routed to Port
	 //     pins P0.4 and P0.5.)
	 // SPI0E (SPI I/O Enable) = ENABLED (SPI I/O routed to Port pins. The SPI
	 //     can be assigned either 3 or 4 GPIO pins.)
	 // SMB0E (SMBus0 I/O Enable) = DISABLED (SMBus0 I/O unavailable at Port
	 //     pins.)
	 // CP0E (Comparator0 Output Enable) = DISABLED (CP0 unavailable at Port
	 //     pin.)
	 // CP0AE (Comparator0 Asynchronous Output Enable) = DISABLED
	 //     (Asynchronous CP0 unavailable at Port pin.)
	 // SYSCKE (SYSCLK Output Enable) = DISABLED (SYSCLK unavailable at Port
	 //     pin.)
	 */
	XBR0 = XBR0_URT0E__ENABLED | XBR0_SPI0E__ENABLED | XBR0_SMB0E__DISABLED
			| XBR0_CP0E__DISABLED | XBR0_CP0AE__DISABLED
			| XBR0_SYSCKE__DISABLED;
	// [XBR0 - Port I/O Crossbar 0]$

	// $[XBR1 - Port I/O Crossbar 1]
	/*
	 // PCA0ME (PCA Module I/O Enable) = CEX0 (CEX0 routed to Port pin.)
	 // ECIE (PCA0 External Counter Input Enable) = DISABLED (ECI unavailable
	 //     at Port pin.)
	 // T0E (T0 Enable) = DISABLED (T0 unavailable at Port pin.)
	 // T1E (T1 Enable) = DISABLED (T1 unavailable at Port pin.)
	 */
	XBR1 = XBR1_PCA0ME__CEX0 | XBR1_ECIE__DISABLED | XBR1_T0E__DISABLED
			| XBR1_T1E__DISABLED;
	// [XBR1 - Port I/O Crossbar 1]$

}

//================================================================================
// RSTSRC_0_enter_DefaultMode_from_RESET
//================================================================================
void RSTSRC_0_enter_DefaultMode_from_RESET( void )
{
	// $[RSTSRC - Reset Source]
	/*
	 // PORSF (Power-On / Supply Monitor Reset Flag, and Supply Monitor Reset
	 //     Enable) = SET (A power-on or supply monitor reset occurred.)
	 // MCDRSF (Missing Clock Detector Enable and Flag) = SET (A missing clock
	 //     detector reset occurred.)
	 // C0RSEF (Comparator0 Reset Enable and Flag) = NOT_SET (A Comparator 0
	 //     reset did not occur.)
	 // RTC0RE (RTC Reset Enable and Flag) = NOT_SET (A RTC alarm or
	 //     oscillator fail reset did not occur.)
	 */
	RSTSRC = RSTSRC_PORSF__SET | RSTSRC_MCDRSF__SET | RSTSRC_C0RSEF__NOT_SET
			| RSTSRC_RTC0RE__NOT_SET;
	// [RSTSRC - Reset Source]$

}

//================================================================================
// HFOSC_0_enter_DefaultMode_from_RESET
//================================================================================
void HFOSC_0_enter_DefaultMode_from_RESET( void )
{
	// $[HFO#CAL - High Frequency Oscillator Calibration]
	// [HFO#CAL - High Frequency Oscillator Calibration]$

	// $[HFO#CN - High Frequency Oscillator Control]
	/*
	 // IOSCEN (High Frequency Oscillator Enable) = ENABLED (High Frequency
	 //     Oscillator enabled.)
	 */
	HFO0CN |= HFO0CN_IOSCEN__ENABLED;
	// [HFO#CN - High Frequency Oscillator Control]$

	// $[Oscillator Ready]
	while( (HFO0CN & HFO0CN_IFRDY__BMASK) == HFO0CN_IFRDY__NOT_SET )
		;
	// [Oscillator Ready]$

}

//================================================================================
// CLOCK_0_enter_DefaultMode_from_RESET
//================================================================================
void CLOCK_0_enter_DefaultMode_from_RESET( void )
{
	// $[CLKSEL - Clock Select]
	/*
	 // CLKDIV (Clock Source Divider) = SYSCLK_DIV_1 (SYSCLK is equal to
	 //     selected clock source divided by 1.)
	 // CLKSL (Clock Source Select) = HFOSC (Clock derived from the internal
	 //     precision High-Frequency Oscillator.)
	 */
	CLKSEL = CLKSEL_CLKDIV__SYSCLK_DIV_1 | CLKSEL_CLKSL__HFOSC;
	// Wait for the clock to be ready
	while( (CLKSEL & CLKSEL_CLKRDY__BMASK) != CLKSEL_CLKRDY__SET )
		;
	// [CLKSEL - Clock Select]$

}

//================================================================================
// TIMER01_0_enter_DefaultMode_from_RESET
//================================================================================
void TIMER01_0_enter_DefaultMode_from_RESET( void )
{
	// $[Timer Initialization]
	//Save Timer Configuration
	uint8_t TCON_save = TCON;
	//Stop Timers
	TCON &= TCON_TR0__BMASK & TCON_TR1__BMASK;

	// [Timer Initialization]$

	// $[TH0 - Timer 0 High Byte]
	// [TH0 - Timer 0 High Byte]$

	// $[TL0 - Timer 0 Low Byte]
	// [TL0 - Timer 0 Low Byte]$

	// $[TH1 - Timer 1 High Byte]
	/*
	 // TH1 (Timer 1 High Byte) = 0x96
	 */
	TH1 = (0x96 << TH1_TH1__SHIFT);
	// [TH1 - Timer 1 High Byte]$

	// $[TL1 - Timer 1 Low Byte]
	/*
	 // TL1 (Timer 1 Low Byte) = 0xCB
	 */
	TL1 = (0xCB << TL1_TL1__SHIFT);
	// [TL1 - Timer 1 Low Byte]$

	// $[Timer Restoration]
	//Restore Timer Configuration
	TCON = TCON_save;

	// [Timer Restoration]$

}

//================================================================================
// TIMER16_2_enter_DefaultMode_from_RESET
//================================================================================
void TIMER16_2_enter_DefaultMode_from_RESET( void )
{
	// $[Timer Initialization]
	// Save Timer Configuration
	uint8_t TMR2CN0_TR2_save = TMR2CN0 & TMR2CN0_TR2__BMASK;
	// Stop Timer
	TMR2CN0 &= ~(TMR2CN0_TR2__BMASK);
	// [Timer Initialization]$

	// $[TMR2CN0 - Timer 2 Control]
	// [TMR2CN0 - Timer 2 Control]$

	// $[TMR2H - Timer 2 High Byte]
	/*
	 // TMR2H (Timer 2 High Byte) = 0xD7
	 */
	TMR2H = (0xD7 << TMR2H_TMR2H__SHIFT);
	// [TMR2H - Timer 2 High Byte]$

	// $[TMR2L - Timer 2 Low Byte]
	/*
	 // TMR2L (Timer 2 Low Byte) = 0x60
	 */
	TMR2L = (0x60 << TMR2L_TMR2L__SHIFT);
	// [TMR2L - Timer 2 Low Byte]$

	// $[TMR2RLH - Timer 2 Reload High Byte]
	/*
	 // TMR2RLH (Timer 2 Reload High Byte) = 0xD7
	 */
	// TMR2 1 Clock 24.5MHz / 12 = 2.04MHz
	// 1Colok = 0.49uSec
	// 1mSec = ( 0xFFFF - 0xF800 ) * 0.49uSec
	TMR2RLH = (0xF8 << TMR2RLH_TMR2RLH__SHIFT);
	// [TMR2RLH - Timer 2 Reload High Byte]$

	// $[TMR2RLL - Timer 2 Reload Low Byte]
	/*
	 // TMR2RLL (Timer 2 Reload Low Byte) = 0x4F
	 */
	TMR2RLL = (0x00 << TMR2RLL_TMR2RLL__SHIFT);
	// [TMR2RLL - Timer 2 Reload Low Byte]$

	// $[TMR2CN0]
	/*
	 // TR2 (Timer 2 Run Control) = RUN (Start Timer 2 running.)
	 */
	TMR2CN0 |= TMR2CN0_TR2__RUN;
	// [TMR2CN0]$

	// $[Timer Restoration]
	// Restore Timer Configuration
	TMR2CN0 |= TMR2CN0_TR2_save;
	// [Timer Restoration]$
}

//================================================================================
// TIMER_SETUP_0_enter_DefaultMode_from_RESET
//================================================================================
void TIMER_SETUP_0_enter_DefaultMode_from_RESET( void )
{
	// $[CKCON0 - Clock Control 0]
	/*
	 // SCA (Timer 0/1 Prescale) = SYSCLK_DIV_12 (System clock divided by 12.)
	 // T0M (Timer 0 Clock Select) = PRESCALE (Counter/Timer 0 uses the clock
	 //     defined by the prescale field, SCA.)
	 // T2MH (Timer 2 High Byte Clock Select) = EXTERNAL_CLOCK (Timer 2 high
	 //     byte uses the clock defined by T2XCLK in TMR2CN0.)
	 // T2ML (Timer 2 Low Byte Clock Select) = SYSCLK (Timer 2 low byte uses
	 //     the system clock.)
	 // T3MH (Timer 3 High Byte Clock Select) = EXTERNAL_CLOCK (Timer 3 high
	 //     byte uses the clock defined by T3XCLK in TMR3CN0.)
	 // T3ML (Timer 3 Low Byte Clock Select) = EXTERNAL_CLOCK (Timer 3 low
	 //     byte uses the clock defined by T3XCLK in TMR3CN0.)
	 // T1M (Timer 1 Clock Select) = SYSCLK (Timer 1 uses the system clock.)
	 */
	CKCON0 = CKCON0_SCA__SYSCLK_DIV_12 | CKCON0_T0M__PRESCALE
			| CKCON0_T2MH__EXTERNAL_CLOCK
			| CKCON0_T2ML__EXTERNAL_CLOCK | CKCON0_T3MH__EXTERNAL_CLOCK
			| CKCON0_T3ML__EXTERNAL_CLOCK
			| CKCON0_T1M__SYSCLK;
	// [CKCON0 - Clock Control 0]$

	// $[TMOD - Timer 0/1 Mode]
	/*
	 // T0M (Timer 0 Mode Select) = MODE0 (Mode 0, 13-bit Counter/Timer)
	 // T1M (Timer 1 Mode Select) = MODE2 (Mode 2, 8-bit Counter/Timer with
	 //     Auto-Reload)
	 // CT0 (Counter/Timer 0 Select) = TIMER (Timer Mode. Timer 0 increments
	 //     on the clock defined by T0M in the CKCON register.)
	 // GATE0 (Timer 0 Gate Control) = DISABLED (Timer 0 enabled when TR0 = 1
	 //     irrespective of INT0 logic level.)
	 // CT1 (Counter/Timer 1 Select) = TIMER (Timer Mode. Timer 1 increments
	 //     on the clock defined by T1M in the CKCON register.)
	 // GATE1 (Timer 1 Gate Control) = DISABLED (Timer 1 enabled when TR1 = 1
	 //     irrespective of INT1 logic level.)
	 */
	TMOD = TMOD_T0M__MODE0 | TMOD_T1M__MODE2 | TMOD_CT0__TIMER
			| TMOD_GATE0__DISABLED
			| TMOD_CT1__TIMER | TMOD_GATE1__DISABLED;
	// [TMOD - Timer 0/1 Mode]$

	// $[TCON - Timer 0/1 Control]
	/*
	 // TR1 (Timer 1 Run Control) = RUN (Start Timer 1 running.)
	 */
	TCON |= TCON_TR1__RUN;
	// [TCON - Timer 0/1 Control]$

}

//================================================================================
// SPI_0_enter_DefaultMode_from_RESET
//================================================================================
void SPI_0_enter_DefaultMode_from_RESET( void )
{
	// $[SPI0CKR - SPI0 Clock Rate]
	/*
	 // SPI0CKR (SPI0 Clock Rate) = 0x06
	 */
	SPI0CKR = (0x06 << SPI0CKR_SPI0CKR__SHIFT);
	// [SPI0CKR - SPI0 Clock Rate]$

	// $[SPI0CFG - SPI0 Configuration]
	/*
	 // MSTEN (Master Mode Enable) = MASTER_ENABLED (Enable master mode.
	 //     Operate as a master.)
	 */
	SPI0CFG |= SPI0CFG_MSTEN__MASTER_ENABLED | SPI0CFG_CKPOL__IDLE_HIGH
			| SPI0CFG_CKPHA__DATA_CENTERED_SECOND;
	// [SPI0CFG - SPI0 Configuration]$

	// $[SPI0CN0 - SPI0 Control]
	/*
	 // SPIEN (SPI0 Enable) = ENABLED (Enable the SPI module.)
	 // NSSMD (Slave Select Mode) = 4_WIRE_MASTER_NSS_HIGH (4-Wire Single-
	 //     Master Mode. NSS is an output and logic high.)
	 */
	SPI0CN0 |= SPI0CN0_SPIEN__ENABLED | SPI0CN0_NSSMD__4_WIRE_MASTER_NSS_HIGH;
	// [SPI0CN0 - SPI0 Control]$

}

//================================================================================
// UART_0_enter_DefaultMode_from_RESET
//================================================================================
void UART_0_enter_DefaultMode_from_RESET( void )
{
	// $[SCON0 - UART0 Serial Port Control]
	/*
	 // REN (Receive Enable) = RECEIVE_ENABLED (UART0 reception enabled.)
	 */
	SCON0 |= SCON0_REN__RECEIVE_ENABLED;
	// [SCON0 - UART0 Serial Port Control]$

}

//================================================================================
// PCACH_0_enter_DefaultMode_from_RESET
//================================================================================
void PCACH_0_enter_DefaultMode_from_RESET( void )
{
	#if 0
	// $[PCA0 Settings Save]
	uint8_t PCA0CN0_CR_save = PCA0CN0 & PCA0CN0_CR__BMASK;
	uint8_t PCA0PWM_ARSEL_save = PCA0PWM & PCA0PWM_ARSEL__BMASK;

	// Turn PCA0 off while updating PCACH0
	PCA0CN0 &= ~PCA0CN0_CR__BMASK;
	// Select Capture/Compare register)
	PCA0PWM &= ~PCA0PWM_ARSEL__BMASK;
	// [PCA0 Settings Save]$

	// $[PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]
	/*
	 // CAPN (Channel 0 Capture Negative Function Enable) = DISABLED (Disable
	 //     negative edge capture.)
	 // ECCF (Channel 0 Capture/Compare Flag Interrupt Enable) = DISABLED
	 //     (Disable CCF0 interrupts.)
	 // MAT (Channel 0 Match Function Enable) = DISABLED (Disable match
	 //     function.)
	 // PWM16 (Channel 0 16-bit Pulse Width Modulation Enable) = 8_BIT (8 to
	 //     11-bit PWM selected.)
	 // CAPP (Channel 0 Capture Positive Function Enable) = DISABLED (Disable
	 //     positive edge capture.)
	 // ECOM (Channel 0 Comparator Function Enable) = ENABLED (Enable
	 //     comparator function.)
	 // PWM (Channel 0 Pulse Width Modulation Mode Enable) = ENABLED (Enable
	 //     PWM function.)
	 // TOG (Channel 0 Toggle Function Enable) = DISABLED (Disable toggle
	 //     function.)
	 */
	PCA0CPM0 = PCA0CPM0_CAPN__DISABLED | PCA0CPM0_ECCF__DISABLED
			| PCA0CPM0_MAT__DISABLED
			| PCA0CPM0_PWM16__8_BIT | PCA0CPM0_CAPP__DISABLED
			| PCA0CPM0_ECOM__ENABLED
			| PCA0CPM0_PWM__ENABLED | PCA0CPM0_TOG__DISABLED;
	// [PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]$

	// $[PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]
	// [PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]$

	// $[PCA0CPH0 - PCA Channel 0 Capture Module High Byte]
	// [PCA0CPH0 - PCA Channel 0 Capture Module High Byte]$

	// $[Auto-reload]
	// [Auto-reload]$

	// $[PCA0 Settings Restore]
	PCA0CN0 |= PCA0CN0_CR_save;
	PCA0PWM |= PCA0PWM_ARSEL_save;
	// [PCA0 Settings Restore]$
	#endif

	// $[PCA0 Settings Save]
		uint8_t PCA0CN0_CR_save = PCA0CN0 & PCA0CN0_CR__BMASK;
		uint8_t PCA0PWM_ARSEL_save = PCA0PWM & PCA0PWM_ARSEL__BMASK;
	
		// Turn PCA0 off while updating PCACH0
		PCA0CN0 &= ~PCA0CN0_CR__BMASK;
		// Select Capture/Compare register)
		PCA0PWM &= ~PCA0PWM_ARSEL__BMASK;
		// [PCA0 Settings Save]$
	
		// $[PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]
		/*
		// CAPN (Channel 0 Capture Negative Function Enable) = DISABLED (Disable
		//	   negative edge capture.)
		// ECCF (Channel 0 Capture/Compare Flag Interrupt Enable) = ENABLED
		//	   (Enable a Capture/Compare Flag interrupt request when CCF0 is set.)
		// MAT (Channel 0 Match Function Enable) = ENABLED (Enable match
		//	   function.)
		// PWM16 (Channel 0 16-bit Pulse Width Modulation Enable) = 8_BIT (8 to
		//	   11-bit PWM selected.)
		// CAPP (Channel 0 Capture Positive Function Enable) = DISABLED (Disable
		//	   positive edge capture.)
		// ECOM (Channel 0 Comparator Function Enable) = ENABLED (Enable
		//	   comparator function.)
		// PWM (Channel 0 Pulse Width Modulation Mode Enable) = DISABLED (Disable
		//	   PWM function.)
		// TOG (Channel 0 Toggle Function Enable) = DISABLED (Disable toggle
		//	   function.)
		*/
		PCA0CPM0 = PCA0CPM0_CAPN__DISABLED | PCA0CPM0_ECCF__ENABLED | PCA0CPM0_MAT__ENABLED
			 | PCA0CPM0_PWM16__8_BIT | PCA0CPM0_CAPP__DISABLED | PCA0CPM0_ECOM__ENABLED
			 | PCA0CPM0_PWM__DISABLED | PCA0CPM0_TOG__DISABLED;
		// [PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]$
	
		// $[PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]
		/*
		// PCA0CPL0 (PCA Channel 0 Capture Module Low Byte) = 0x10
		*/
		PCA0CPL0 = (0x10 << PCA0CPL0_PCA0CPL0__SHIFT);
		// [PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]$
	
		// $[PCA0CPH0 - PCA Channel 0 Capture Module High Byte]
		/*
		// PCA0CPH0 (PCA Channel 0 Capture Module High Byte) = 0x27
		*/
		PCA0CPH0 = (0x27 << PCA0CPH0_PCA0CPH0__SHIFT);
		// [PCA0CPH0 - PCA Channel 0 Capture Module High Byte]$
	
		// $[Auto-reload]
		// [Auto-reload]$
	
		// $[PCA0 Settings Restore]
		PCA0CN0 |= PCA0CN0_CR_save;
		PCA0PWM |= PCA0PWM_ARSEL_save;
		// [PCA0 Settings Restore]$

}

//================================================================================
// INTERRUPT_0_enter_DefaultMode_from_RESET
//================================================================================
void INTERRUPT_0_enter_DefaultMode_from_RESET( void )
{
	// $[EIE1 - Extended Interrupt Enable 1]
	/*
	// EADC0 (ADC0 Conversion Complete Interrupt Enable) = DISABLED (Disable
	//     ADC0 Conversion Complete interrupt.)
	// EWADC0 (ADC0 Window Comparison Interrupt Enable) = DISABLED (Disable
	//     ADC0 Window Comparison interrupt.)
	// ECP0 (Comparator0 (CP0) Interrupt Enable) = DISABLED (Disable CP0
	//     interrupts.)
	// EPCA0 (Programmable Counter Array (PCA0) Interrupt Enable) = ENABLED
	//     (Enable interrupt requests generated by PCA0.)
	// ERTC0A (RTC Alarm Interrupt Enable) = DISABLED (Disable RTC Alarm
	//     interrupts.)
	// ESMB0 (SMBus (SMB0) Interrupt Enable) = DISABLED (Disable all SMB0
	//     interrupts.)
	// ET3 (Timer 3 Interrupt Enable) = DISABLED (Disable Timer 3
	//     interrupts.)
	*/
	EIE1 = EIE1_EADC0__DISABLED | EIE1_EWADC0__DISABLED | EIE1_ECP0__DISABLED
		 | EIE1_EPCA0__ENABLED | EIE1_ERTC0A__DISABLED | EIE1_ESMB0__DISABLED
		 | EIE1_ET3__DISABLED;


	// $[EIP1 - Extended Interrupt Priority 1]
	// [EIP1 - Extended Interrupt Priority 1]$

	// $[IE - Interrupt Enable]
	/*
	 // EA (All Interrupts Enable) = ENABLED (Enable each interrupt according
	 //     to its individual mask setting.)
	 // EX0 (External Interrupt 0 Enable) = DISABLED (Disable external
	 //     interrupt 0.)
	 // EX1 (External Interrupt 1 Enable) = DISABLED (Disable external
	 //     interrupt 1.)
	 // ESPI0 (SPI0 Interrupt Enable) = DISABLED (Disable all SPI0
	 //     interrupts.)
	 // ET0 (Timer 0 Interrupt Enable) = DISABLED (Disable all Timer 0
	 //     interrupt.)
	 // ET1 (Timer 1 Interrupt Enable) = DISABLED (Disable all Timer 1
	 //     interrupt.)
	 // ET2 (Timer 2 Interrupt Enable) = DISABLED (Disable Timer 2 interrupt.)
	 // ES0 (UART0 Interrupt Enable) = ENABLED (Enable UART0 interrupt.)
	 */
	IE = IE_EA__ENABLED | IE_EX0__DISABLED | IE_EX1__DISABLED
			| IE_ESPI0__DISABLED
			| IE_ET0__DISABLED | IE_ET1__DISABLED | IE_ET2__ENABLED
			| IE_ES0__ENABLED;
	// [IE - Interrupt Enable]$

	// $[IP - Interrupt Priority]
	/*
	 // PX0 (External Interrupt 0 Priority Control) = LOW (External Interrupt
	 //     0 set to low priority level.)
	 // PX1 (External Interrupt 1 Priority Control) = LOW (External Interrupt
	 //     1 set to low priority level.)
	 // PSPI0 (Serial Peripheral Interface (SPI0) Interrupt Priority Control)
	 //     = LOW (SPI0 interrupt set to low priority level.)
	 // PT0 (Timer 0 Interrupt Priority Control) = LOW (Timer 0 interrupt set
	 //     to low priority level.)
	 // PT1 (Timer 1 Interrupt Priority Control) = LOW (Timer 1 interrupt set
	 //     to low priority level.)
	 // PT2 (Timer 2 Interrupt Priority Control) = LOW (Timer 2 interrupt set
	 //     to low priority level.)
	 // PS0 (UART0 Interrupt Priority Control) = HIGH (UART0 interrupt set to
	 //     high priority level.)
	 */
	IP = IP_PX0__LOW | IP_PX1__LOW | IP_PSPI0__LOW | IP_PT0__LOW | IP_PT1__LOW
			| IP_PT2__LOW | IP_PS0__HIGH;
	// [IP - Interrupt Priority]$

	// $[EIE2 - Extended Interrupt Enable 2]
	// [EIE2 - Extended Interrupt Enable 2]$

	// $[EIP2 - Extended Interrupt Priority 2]
	// [EIP2 - Extended Interrupt Priority 2]$
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device( void )
{
	unsigned char SFRPAGE_save = SFRPAGE;

	PCA_0_enter_DefaultMode_from_RESET();
	PCACH_0_enter_DefaultMode_from_RESET();
	VREG_0_enter_DefaultMode_from_RESET();
	PORTS_0_enter_DefaultMode_from_RESET();
	PORTS_1_enter_DefaultMode_from_RESET();
	PBCFG_0_enter_DefaultMode_from_RESET();
	RSTSRC_0_enter_DefaultMode_from_RESET();
	HFOSC_0_enter_DefaultMode_from_RESET();
	CLOCK_0_enter_DefaultMode_from_RESET();
	TIMER01_0_enter_DefaultMode_from_RESET();
	TIMER16_2_enter_DefaultMode_from_RESET();
	TIMER_SETUP_0_enter_DefaultMode_from_RESET();
	SPI_0_enter_DefaultMode_from_RESET();
	UART_0_enter_DefaultMode_from_RESET();
	INTERRUPT_0_enter_DefaultMode_from_RESET();
	SFRPAGE = SFRPAGE_save;
}
