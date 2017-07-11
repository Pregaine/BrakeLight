/*
 * SB1_SPI0_Master.h
 *
 *  Created on: May 29, 2014
 *      Author: jiguo1
 */

#ifndef _EFM8SB1_SPI_H_
#define _EFM8SB1_SPI_H_

extern unsigned char SPI_Write( unsigned char );
extern unsigned char SPI_Read( unsigned char cmd );
extern unsigned char SPI_Array_Read( unsigned char cmd, unsigned char len,
		unsigned char * buf );
extern unsigned char SPI_Array_Write( unsigned char cmd, unsigned char len,
		unsigned char * buf );

#endif /* EFM8SB1_SPI0_MASTER_MAIN_H_ */
