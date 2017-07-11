#include <si_toolchain.h>
#include "adxl345.h"
#include "EFM8SB1_SPI.h"
#include "Typedef.h"


// ============================================================================
//     G Sensor Write Data Function
// ============================================================================
void XL345Write( unsigned char count, unsigned char regaddr,
		unsigned char *buf )
{
	unsigned char state = 0xFF;

	if( count > 1 )
		regaddr |= 0x40;

	// 寫入資料	
	state = SPI_Array_Write(regaddr, count, buf);

	NOP();
}

// ============================================================================
//     G Sensor Read Byte data Function
// ============================================================================
unsigned char XL345ReadByte( unsigned char regaddr )
{
	unsigned char GET_DATA;

	GET_DATA = SPI_Read(0x80 | regaddr); 			// 讀取資料

	return GET_DATA;
}

// ============================================================================
//     G Sensor initial Function
// ============================================================================
unsigned char ADXL345_Initiate( void ) // ADXL345 initialization, refer to ADXL345 data sheet
{
	unsigned char spi_tmp;

	spi_tmp = 0x0B;
	XL345Write(1, 0x31, &spi_tmp);

	spi_tmp = 0x08;
	XL345Write(1, 0x2D, &spi_tmp);

	spi_tmp = XL345ReadByte( XL345_DEVID );

	if( spi_tmp != _XL345_ID )
		return _FAIL;

	return _SUCCESS;
}

// ============================================================================
//     G Sensor Sleep Function
// ============================================================================
void ADXL345_Sleep( void ) // ADXL345 initialization, refer to ADXL345 data sheet
{
	unsigned char spi_tmp;

	spi_tmp = 0x04;
	XL345Write(1, XL345_POWER_CTL, &spi_tmp);
}

// ============================================================================
//     G Sensor wakeup Function
// ============================================================================
void ADXL345_Wakeup( void ) // ADXL345 initialization, refer to ADXL345 data sheet
{
	unsigned char spi_tmp;

	spi_tmp = 0x00;
	XL345Write(1, XL345_POWER_CTL, &spi_tmp);

	spi_tmp = 0x08;
	XL345Write(1, XL345_POWER_CTL, &spi_tmp);
}

// ============================================================================
//     G Sensor Get 3X Data Function
// ============================================================================
void Get_3X( S16 *GGx, S16 *GGy, S16 *GGz )
{
	*GGx = XL345ReadByte(XL345_DATAX1);
	*GGx = (*GGx << 8) + XL345ReadByte(XL345_DATAX0);
	*GGy = XL345ReadByte(XL345_DATAY1);
	*GGy = (*GGy << 8) + XL345ReadByte(XL345_DATAY0);
	*GGz = XL345ReadByte(XL345_DATAZ1);
	*GGz = (*GGz << 8) + XL345ReadByte(XL345_DATAZ0);
}

