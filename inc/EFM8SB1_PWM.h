#ifndef _EFM8SB1_PWM_H_
#define _EFM8SB1_PWM_H_

#define SYSCLK       24500000L         // Internal oscillator frequency in Hz

#define LED_FREQUENCY 10L               // Frequency to blink LED at in Hz

#define T0_CLOCKS 245L                 // Use 245 clocks per T0 Overflow
                                       // SYSCLK cycles per interrupt

// cycle 10mSec 100Hz
// #define PCA_TIMEOUT_P_50 ( ( SYSCLK / T0_CLOCKS ）/ LED_FREQUENCY　)
// #define PCA_TIMEOUT_01   ( PCA_TIMEOUT_P_50 / 50 )
#define PCA_TIMEOUT_01 200

extern unsigned int PWM_H_TIME;
extern unsigned int PWM_L_TIME;

extern void PWM_Init( void );
extern void PWM_SetDuty( unsigned char duty_cycle );

#endif
