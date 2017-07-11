/*
 * SB1_UART0_Interrupt.h
 *
 *  Created on: May 29, 2014
 *      Author: jiguo1
 */

#ifndef EFM8SB1_UART0_INTERRUPT_MAIN_H_
#define EFM8SB1_UART0_INTERRUPT_MAIN_H_

extern unsigned char UART_Buffer_Size;
extern unsigned char TX_Ready;
extern unsigned char Byte;

extern void UartWrite( const unsigned char *data_ptr, unsigned int length );
extern unsigned char UartRead( unsigned char *buf, unsigned int length );

#endif /* EFM8SB1_UART0_INTERRUPT_MAIN_H_ */
