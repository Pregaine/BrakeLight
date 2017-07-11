//-----------------------------------------------------------------------------
// SB1_SPI0_Master.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This program configures a EFM8SB1 as a 4-wire SPI Single Master.
//
// The SPI clock in this example is limited to 500 kHz when used with the
// SPI0_Slave code example.  During a SPI_Read, the slave needs some time to
// interpret the command and write the appropriate data to the SPI0DAT
// register, and the slave no longer has enough time to complete the
// SPI_READ_BUFFER command with a clock greater than 500 kHz.  For faster SPI
// clocks, a dummy byte between the command and the first byte of Read data
// will be required.
//
// This example is intended to be used with the SPI0_Slave example.
//
// Pinout:
//
// P0.6 - SPI SCK    (digital output, push-pull)
// P0.7 - SPI MISO   (digital input, open-drain)
// P1.0 - SPI MOSI   (digital output, push-pull)
// P1.1 - SPI NSS    (digital output, push-pull)
//
// P0.1 - TEST_OUT   (digital output, push-pull)
//
// all other port pins unused.
//
// Target:         EFM8SB1
// Tool chain:     Simplicity Studio / Keil C51 9.51
// Command Line:   None
//
// Release 1.0 (BL)
//    - Initial Release
//    - 9 JAN 2015
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <si_toolchain.h>
#include <SI_EFM8SB1_Register_Enums.h>                  // SI_SFR declarations
#include "EFM8SB1_SPI.h"
#include "Typedef.h"

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
unsigned char SPI_Write( unsigned char );
unsigned char SPI_Read( unsigned char );
unsigned char SPI_Array_Write( unsigned char, unsigned char, unsigned char * );
unsigned char SPI_Array_Read( unsigned char, unsigned char, unsigned char * );

//-----------------------------------------------------------------------------
// SPI_Byte_Write
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Note: SPI_Data must contain the data to be sent before calling this
// function.
//
// Writes a single byte to the SPI Slave.  The slave does not respond to this
// command, so the command consists of:
//
// Command = SPI_WRITE
// Length = 1 byte of command, 1 byte of data
//
//-----------------------------------------------------------------------------
unsigned char SPI_Write( unsigned char cmd )
{
	unsigned int timeout = 0xFFFF;

	SPI0CN0_NSSMD0 = 0;				//NSS Pin

	SPI0DAT = cmd;

	while( !SPI0CN0_SPIF )
	{
		if( timeout )
			timeout--;
		else if( timeout == 0 )
			break;
	}

	SPI0CN0_SPIF = 0;				//clear 

	SPI0CN0_NSSMD0 = 1;				//NSS Pin

	return (timeout == 0) ?1 :0;

	// The rest of this command will be handled by the SPI ISR, which will
	// trigger when SPI0CN0_SPIF is set from sending the Command
}

//-----------------------------------------------------------------------------
// SPI_Byte_Read
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Note: SPI_Data will contain the data received after calling this function.
//
// Reads a single byte from the SPI Slave.  The command consists of:
//
// Command = SPI_READ
// Length = 1 byte of command, 1 byte of data
//
//-----------------------------------------------------------------------------
unsigned char SPI_Read( unsigned char cmd )
{
	uint16_t timeout = 0xFFFF;
	unsigned char dummy = 0xFF;

	SPI0CN0_NSSMD0 = 0;

	SPI0DAT = cmd;

	while( !SPI0CN0_SPIF )
	{
		if( timeout )
			timeout--;
		else if( timeout == 0 )
			goto _END;
	}

	SPI0CN0_SPIF = 0;

	timeout = 0xFFFF;

	SPI0DAT = dummy;

	while( !SPI0CN0_SPIF )
	{
		if( timeout )
			timeout--;
		else if( timeout == 0 )
			break;
	}

	_END:

	SPI0CN0_SPIF = 0;

	SPI0CN0_NSSMD0 = 1;

	return (timeout == 0) ?_FAIL :SPI0DAT;
}

//-----------------------------------------------------------------------------
// SPI_Array_Write
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Note: SPI_Data_Array must contain the data to be sent before calling this
// function.
//
// Writes an array of values of size MAX_BUFFER_SIZE to the SPI Slave.  The
// command consists of:
//
// Command = SPI_WRITE_BUFFER
// Length = 1 byte of command, MAX_BUFFER_SIZE bytes of data
//
// Note: Polled mode is used for this function in order to buffer the data
// being sent using the SPI0CN0_TXBMT flag.
//
//-----------------------------------------------------------------------------
unsigned char SPI_Array_Write( unsigned char cmd, unsigned char len,
		unsigned char *buf )
{
	unsigned char array_index;
	uint16_t timeout = 0xFFFF;

	SPI0CN0_NSSMD0 = 0;

	SPI0DAT = cmd;         					// Load the XMIT register

	// Wait until the command is moved into
	// the XMIT buffer
	timeout = 0xFFFF;

	while( !SPI0CN0_SPIF )
	{
		if( timeout )
			timeout--;
		else if( timeout == 0 )
			goto _END;
	}

	SPI0CN0_SPIF = 0;

	for( array_index = 0; array_index < len; array_index++ )
	{
		SPI0DAT = *(buf + array_index); 	// Load the data into the buffer

		// Wait until the data is moved into
		// the XMIT buffer
		timeout = 0xFFFF;

		while( !SPI0CN0_SPIF )
		{
			if( timeout )
				timeout--;
			else if( timeout == 0 )
				goto _END;
		}

		SPI0CN0_SPIF = 0;
	}

	_END:

	SPI0CN0_SPIF = 0;

	SPI0CN0_NSSMD0 = 1;			// Diable the Slave

	return (timeout == 0) ?_FAIL :_SUCCESS;
}

//-----------------------------------------------------------------------------
// SPI_Array_Read
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Note: SPI_Data_Array will contain the data received after calling this
// function.
//
// Reads a single byte from the SPI Slave.  The command consists of:
//
// Command = SPI_READ_BUFFER
// Length = 1 byte of command, MAX_BUFFER_SIZE bytes of data
//
//-----------------------------------------------------------------------------
unsigned char SPI_Array_Read( unsigned char cmd, unsigned char len,
		unsigned char *buf )
{
	unsigned char array_index;
	uint16_t timeout = 0xFFFF;
	unsigned char dummy = 0xFF;

	SPI0CN0_NSSMD0 = 0;

	SPI0DAT = cmd;

	while( !SPI0CN0_SPIF )
	{
		if( timeout )
			timeout--;
		else if( timeout == 0 )
			goto _END;
	}

	SPI0CN0_SPIF = 0;

	for( array_index = 0; array_index < len; array_index++ )
	{
		SPI0DAT = dummy;

		while( !SPI0CN0_SPIF )
		{
			if( timeout )
				timeout--;
			else if( timeout == 0 )
				goto _END;
		}

		SPI0CN0_SPIF = 0;

		*(buf + array_index) = SPI0DAT;
	}

	SPI0CN0_SPIF = 0;

	_END:

	SPI0CN0_NSSMD0 = 1;

	return (timeout == 0) ?_FAIL :_SUCCESS;
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
