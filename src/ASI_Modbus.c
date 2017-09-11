#include "ASI_Modbus.h"
#include "EFM8SB1_UART.h"
#include "Gdefine.h"

#define _MAX_BUF_SIZE 10

_ReadHoldReg_Request_Stc 	 xdata ReadHoldReg_Request;
_ReadHoldReg_Response_Stc 	 xdata ReadHoldReg_Response;
_ReadHoldReg_ResponseErr_Stc xdata ReadHoldReg_Err; 

_WriteMultipleReg_Request_Stc     xdata WriteMultipleReg_Request;
_WriteMultipleReg_Response_Stc    xdata WriteMultipleReg_Response;
_WriteMultipleReg_ResponseErr_Stc xdata WriteMultipleReg_Err;

u8 ASI_buf[ _MAX_BUF_SIZE ] = { 0 };
u8 ASI_cmd = 0;

_ASI_Stc xdata ASI;

// Compute the MODBUS RTU CRC
U16 ModRTU_CRC( u8 *buf, u8 len )
{
	U16 crc = 0xFFFF;
	u8 pos, i;

	for( pos = 0; pos < len; pos++ )
	{
		crc ^= ( U16 ) buf[ pos ];       		// XOR byte into least sig. byte of crc

		for( i = 8; i != 0; i-- )
		{    									// Loop over each bit
			if( (crc & 0x0001) != 0 )
			{						      		// If the LSB is set
				crc >>= 1;                    	// Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else
				// Else LSB is not set
				crc >>= 1;                    	// Just shift right
		}
	}
	// Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)

	crc = ( ( crc & 0xFF00 ) >> 8 ) | ( crc & 0x00FF ) << 8;

	return crc;
}

U16 ASI_Decode_CRC( u8 *buf, u8 len, u16 crc )
{
	u8 pos, i;

	for( pos = 0; pos < len; pos++ )
	{
		crc ^= ( U16 ) buf[ pos ];       		// XOR byte into least sig. byte of crc

		for( i = 8; i != 0; i-- )
		{    									// Loop over each bit
			if( (crc & 0x0001) != 0 )
			{						      		// If the LSB is set
				crc >>= 1;                    	// Shift right and XOR 0xA001
				crc ^= 0xA001;
			}
			else
				// Else LSB is not set
				crc >>= 1;                    	// Just shift right
		}
	}
	
	return crc;
}


void ASI_Modbus_Init()
{
	u8 i;

#if 0
	// u8 code response[] = { 0x03, 0x03, 0x04, 0x00, 0x01, 0x00, 0x01, 0x49, 0xf3 };
	// u8 code response[] = { 0x03, 0x10, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x17 };
	// u8 code response[] = { 0x03, 0x03, 0x04, 0x00, 0x01, 0x00, 0x00, 0x88, 0x33 };
	// u8 code response[] = { 0x03, 0x10, 0x00, 0x01, 0x00, 0x01, 0x51, 0xeb };
	// u8 code response[] = { 0x03, 0x10, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x01, 0x39, 0xD7 };
	u8 code response[] = { 0x03, 0x10, 0x00, 0x00, 0x00, 0x02, 0x40, 0x2a };
	u16 result = 0xFF;
	result = ASI_Decode_CRC( response, sizeof( response ) - 2, 0xFFFF );
#endif

	ASI.status.brake      = _BrakeLightOFF;
	ASI.status.light 	  = _LightOFF;
	ASI.status.brake_save = _BrakeLightOFF;

	/* Begin */
	ReadHoldReg_Request.SlaveID  = _SMART_LIGHT_SLAVE_ID;
	ReadHoldReg_Request.FunCode  = _Cmd_ReadHoldReg;
	ReadHoldReg_Request.StartAdd.word = 0x0000;
	ReadHoldReg_Request.NumOfReg.word = 0x0002;

	// ReadHoldReg_Request.Crc.word 	  = 0xC5E9;
	ReadHoldReg_Request.Crc.word = ModRTU_CRC( &ReadHoldReg_Request.SlaveID, 6 );
	/* End */

	/* Begin Sample ASI Controller Responds Slave ID 1 */
	ReadHoldReg_Response.SlaveID 		= _SMART_LIGHT_SLAVE_ID;
	ReadHoldReg_Response.FunCode 		= _Cmd_ReadHoldReg;
	ReadHoldReg_Response.NumOfDataByte 	= 0x02;
	ReadHoldReg_Response.NumOfRegPtr    = ASI_buf;
	ReadHoldReg_Response.NumOfRegPtr[ 0 ] = 0x00;
	ReadHoldReg_Response.NumOfRegPtr[ 1 ] = 0x03;

	ReadHoldReg_Response.Crc.word = ASI_Decode_CRC( &ReadHoldReg_Response.SlaveID, 3, 0xFFFF );

	ReadHoldReg_Response.Crc.word = ASI_Decode_CRC( ReadHoldReg_Response.NumOfRegPtr, 
													ReadHoldReg_Response.NumOfDataByte, 
		                                            ReadHoldReg_Response.Crc.word );

	// CRC = 0xF845, SWAP CRC
	ReadHoldReg_Response.Crc.word = ( ( ( u16 ) ReadHoldReg_Response.Crc.byte[ 1 ] << 8 ) | \
									            ReadHoldReg_Response.Crc.byte[ 0 ] );
													
	/* End Sample ASI Controller Responds Slave ID 1 */

	/* Begin */
	ReadHoldReg_Err.SlaveID   = _SMART_LIGHT_SLAVE_ID;
	ReadHoldReg_Err.ErrCode   = _ErrCode_ReadHoldReg;
	ReadHoldReg_Err.ExcepCode = _INVALID_ADD;
	ReadHoldReg_Err.Crc.word  = ModRTU_CRC( &ReadHoldReg_Err.SlaveID, 3 );
	/* End */

	/* Begin */
	WriteMultipleReg_Request.SlaveID  		= _SMART_LIGHT_SLAVE_ID;
	WriteMultipleReg_Request.FunCode  		= _Cmd_WriteMultipleReg;
	WriteMultipleReg_Request.StartAdd.word 	= 0x0000;
	WriteMultipleReg_Request.NumOfReg.word 	= 0x0002;	// 有幾個Reg需寫入
	WriteMultipleReg_Request.NumOfDataByte  = 0x04;     // 有幾個Byte需寫入, 1 Reg = 2 Byte
	WriteMultipleReg_Request.NumOfDataBytePtr = ASI_buf; 
	
	WriteMultipleReg_Request.NumOfDataBytePtr[ 0 ] = ( ASI.status.light & 0xFF00 ) >> 8;
	WriteMultipleReg_Request.NumOfDataBytePtr[ 1 ] = ( ASI.status.light & 0x00FF );
	WriteMultipleReg_Request.NumOfDataBytePtr[ 2 ] = ( ASI.status.brake & 0xFF00 ) >> 8;
	WriteMultipleReg_Request.NumOfDataBytePtr[ 3 ] = ( ASI.status.brake & 0x00FF );

	WriteMultipleReg_Request.Crc.word = ASI_Decode_CRC( &WriteMultipleReg_Request.SlaveID,
		                                                7,
		                                                0xFFFF );
	
	WriteMultipleReg_Request.Crc.word = ASI_Decode_CRC( WriteMultipleReg_Request.NumOfDataBytePtr,
														WriteMultipleReg_Request.NumOfDataByte,
														WriteMultipleReg_Request.Crc.word );
	// CRC = 0x6817
	WriteMultipleReg_Request.Crc.word = ( ( WriteMultipleReg_Request.Crc.word & 0x00FF ) << 8 )	| \
										( ( WriteMultipleReg_Request.Crc.word & 0xFF00 ) >> 8 );
												
	/* End */
	
	WriteMultipleReg_Response.SlaveID = _SMART_LIGHT_SLAVE_ID;
	WriteMultipleReg_Response.FunCode = _Cmd_WriteMultipleReg;
	WriteMultipleReg_Response.StartAdd.word = WriteMultipleReg_Request.StartAdd.word;
	WriteMultipleReg_Response.NumberOfReg.word = WriteMultipleReg_Request.NumOfReg.word;
	WriteMultipleReg_Response.Crc.word  = ModRTU_CRC( &WriteMultipleReg_Response.SlaveID, 6 );
	
	WriteMultipleReg_Err.SlaveID   = _SMART_LIGHT_SLAVE_ID;
	WriteMultipleReg_Err.ErrCode   = _ErrCode_WriteMultipleReg;
	WriteMultipleReg_Err.ExcepCode = _INVALID_ADD;
	WriteMultipleReg_Err.Crc.word  = ModRTU_CRC( &WriteMultipleReg_Err.SlaveID, 3 );

	// Erase ASI_buf
	for( i = 0; i < _MAX_BUF_SIZE; i ++ )
		ASI_buf[ i ] = 0;
}

U8 ASI_Modbus_Decode(void)
{
	static u16 index = 0; 
	static u16 crc = 0;

	static u16 result_tmp = 0xFFFF;
	static u16 result_end = 0xFFFF;
	
	u8 buf;
	
	if( UartRead( &buf, 1) == 0 )
		return 0;

	if( index == 0 )
		crc = 0xFFFF;
	
	crc = ASI_Decode_CRC( &buf, 1, crc );

	if( index == 0 )
	{
		if( buf != _SMART_LIGHT_SLAVE_ID )
		{
			index = 0;
			return 0;
		}
		index ++;

		return 0;
	}
	else if ( index == 1 )
	{
		if( buf == _Cmd_ReadHoldReg )
		{
			index ++;
			ASI_cmd = _Cmd_ReadHoldReg;
		}
		else if( buf == _Cmd_WriteMultipleReg )
		{
			index ++;
			ASI_cmd = _Cmd_WriteMultipleReg;
		}
		else
			index = 0;

		return 0;
	}
	else if ( index == 2 )
	{
		if( buf == _Cmd_ReadHoldReg )
			ReadHoldReg_Request.StartAdd.byte[ 0 ] = buf;
		else
			WriteMultipleReg_Request.StartAdd.byte[ 0 ] = buf;
		
		index ++;
		return 0;
	}
	else if ( index == 3 )
	{
		if( ASI_cmd == _Cmd_ReadHoldReg ) 
			ReadHoldReg_Request.StartAdd.byte[ 1 ] = buf;
		else
			WriteMultipleReg_Request.StartAdd.byte[ 1 ] = buf;
		
		index ++;
		return 0;
	}
	else if( index == 4 )
	{
		if( ASI_cmd == _Cmd_ReadHoldReg )
			ReadHoldReg_Request.NumOfReg.byte[ 0 ] = buf;
		else
			WriteMultipleReg_Request.NumOfReg.byte[ 0 ] = buf;

		index ++;
		return 0;
	}
	else if( index == 5 )
	{
		if( ASI_cmd == _Cmd_ReadHoldReg )
			ReadHoldReg_Request.NumOfReg.byte[ 1 ] = buf;
		else
			WriteMultipleReg_Request.NumOfReg.byte[ 1 ] = buf;
		
		result_tmp = crc;

		index ++;
		return 0;
	}
	else if( index == 6 )
	{
		if( ASI_cmd == _Cmd_ReadHoldReg )
		{
			result_end = buf;
		}
		else
		{
			WriteMultipleReg_Request.NumOfDataByte = buf;
		}

		index ++;
		return 0;

	}
	else if( index == 7 && ASI_cmd == _Cmd_ReadHoldReg )
	{

		result_end = ( ( ( u16 ) buf & 0x00FF ) << 8 ) | ( result_end );

		index = 0;

		if( crc == 0 )
		{
			if( result_end == result_tmp )
				return 1;
		}
		else
			return 0;
	}
	else if( ( ASI_cmd == _Cmd_WriteMultipleReg ) &&
			 ( index >= 7 ) &&
		     ( index < ( 7 + WriteMultipleReg_Request.NumOfDataByte ) ) )
	{
		if( ( index - 7 ) < _MAX_BUF_SIZE )
			WriteMultipleReg_Request.NumOfDataBytePtr[ index - 7 ] = buf;

		if( index == ( 6 + WriteMultipleReg_Request.NumOfDataByte ) )
			result_tmp = crc;

		index ++;
		return 0;
	}
	else if( index == ( 7 + WriteMultipleReg_Request.NumOfDataByte ) &&
		     ( ASI_cmd == _Cmd_WriteMultipleReg ) )
	{
		result_end = buf;

		index ++;
		return 0;
	}
	else if( index == ( 8 + WriteMultipleReg_Request.NumOfDataByte ) &&
		     ( ASI_cmd == _Cmd_WriteMultipleReg ) )
	{
		result_end = ( ( ( u16 ) buf & 0x00FF ) << 8 ) | ( result_end );

		index = 0;

		if( crc == 0 )
		{
			if( result_end == result_tmp )
				return 1;
		}
		else
			return 0;
	}

	index = 0;
	return 0;
}


void ASI_Modbus_Response( void )
{
	if( ASI_cmd == _Cmd_WriteMultipleReg  )
	{
		if( WriteMultipleReg_Request.StartAdd.word > _BrakeLightAdd )
		{
			WriteMultipleReg_Err.ExcepCode = _INVALID_ADD;
			WriteMultipleReg_Err.Crc.word  = ModRTU_CRC( &WriteMultipleReg_Err.SlaveID, 3 );
			UartWrite( &WriteMultipleReg_Err.SlaveID, 5 );
			return;
		}

		if( WriteMultipleReg_Request.NumOfReg.word > 2 || WriteMultipleReg_Request.NumOfReg.word == 0 )
		{
			WriteMultipleReg_Err.ExcepCode = _INVALID_NUM_OF_REG;
			WriteMultipleReg_Err.Crc.word  = ModRTU_CRC( &WriteMultipleReg_Err.SlaveID, 3 );
			UartWrite( &WriteMultipleReg_Err.SlaveID, 5 );
			return;
		}

		if( WriteMultipleReg_Request.StartAdd.word == _LightAdd )
		{
			if( WriteMultipleReg_Request.NumOfReg.word == 1 )
			{

				ASI.status.light = ( ( ( ( U16 ) WriteMultipleReg_Request.NumOfDataBytePtr[ 0 ] & 0x00FF ) << 8 ) |
								     WriteMultipleReg_Request.NumOfDataBytePtr[ 1 ]  );
			}
			else if( WriteMultipleReg_Request.NumOfReg.word == 2 )
			{
				ASI.status.light = ( ( ( ( U16 ) WriteMultipleReg_Request.NumOfDataBytePtr[ 0 ] & 0x00FF ) << 8 ) |
							           WriteMultipleReg_Request.NumOfDataBytePtr[ 1 ]  );

				ASI.status.brake = ( ( ( ( U16 ) WriteMultipleReg_Request.NumOfDataBytePtr[ 2 ] & 0x00FF ) << 8 ) |
									   WriteMultipleReg_Request.NumOfDataBytePtr[ 3 ]  );

			    // 重要
				ASI.status.brake_save = ASI.status.brake;
			}
		}
		else if( WriteMultipleReg_Request.StartAdd.word == _BrakeLightAdd )
		{
			if( WriteMultipleReg_Request.NumOfReg.word == 1 )
			{
				ASI.status.brake = ( ( ( ( U16 ) WriteMultipleReg_Request.NumOfDataBytePtr[ 0 ] & 0x00FF ) << 8 ) |
				    				             WriteMultipleReg_Request.NumOfDataBytePtr[ 1 ]  );

			    // 重要
				ASI.status.brake_save = ASI.status.brake;
			}
			else if( WriteMultipleReg_Request.NumOfReg.word == 2 )
			{
				// Fail Num Of Reg
				WriteMultipleReg_Err.ExcepCode = _INVALID_NUM_OF_REG;
				WriteMultipleReg_Err.Crc.word  = ModRTU_CRC( &WriteMultipleReg_Err.SlaveID, 3 );
				UartWrite( &WriteMultipleReg_Err.SlaveID, 5 );
				return;
			}
		}

		WriteMultipleReg_Response.StartAdd.word    = WriteMultipleReg_Request.StartAdd.word;
		WriteMultipleReg_Response.NumberOfReg.word = WriteMultipleReg_Request.NumOfReg.word;
		WriteMultipleReg_Response.Crc.word         = ModRTU_CRC( &WriteMultipleReg_Response.SlaveID, 6 );

		UartWrite( &WriteMultipleReg_Response.SlaveID, 8 );		
	}
	else if( ASI_cmd == _Cmd_ReadHoldReg )
	{
		if( ReadHoldReg_Request.StartAdd.word > _BrakeLightAdd )
		{
			WriteMultipleReg_Err.ExcepCode = _INVALID_ADD;
			WriteMultipleReg_Err.Crc.word  = ModRTU_CRC( &WriteMultipleReg_Err.SlaveID, 3 );
			UartWrite( &WriteMultipleReg_Err.SlaveID, 5 );
			return;
		}

		if( ReadHoldReg_Request.NumOfReg.word > 2 || WriteMultipleReg_Request.NumOfReg.word == 0 )
		{
			ReadHoldReg_Err.ExcepCode = _INVALID_NUM_OF_REG;
			ReadHoldReg_Err.Crc.word  = ModRTU_CRC( &ReadHoldReg_Err.SlaveID, 3 );
			UartWrite( &ReadHoldReg_Err.SlaveID, 5 );
			return;
		}

		ReadHoldReg_Response.NumOfDataByte = ( ReadHoldReg_Request.NumOfReg.word << 1 );

		if( ReadHoldReg_Request.StartAdd.word == _LightAdd )
		{
			if( ReadHoldReg_Response.NumOfDataByte == 2 )
			{
				ReadHoldReg_Response.NumOfRegPtr[ 0 ] = ( ASI.status.light & 0xFF00 ) >> 8;
				ReadHoldReg_Response.NumOfRegPtr[ 1 ] = ( ASI.status.light & 0x00FF );
			}
			else if( ReadHoldReg_Response.NumOfDataByte == 4 )
			{
				ReadHoldReg_Response.NumOfRegPtr[ 0 ] = ( ASI.status.light & 0xFF00 ) >> 8;
				ReadHoldReg_Response.NumOfRegPtr[ 1 ] = ( ASI.status.light & 0x00FF );
				ReadHoldReg_Response.NumOfRegPtr[ 2 ] = ( ASI.status.brake & 0xFF00 ) >> 8;
				ReadHoldReg_Response.NumOfRegPtr[ 3 ] = ( ASI.status.brake & 0x00FF );
			}			
		}
		else if( ReadHoldReg_Request.StartAdd.word == _BrakeLightAdd )
		{
			if( ReadHoldReg_Response.NumOfDataByte == 2 )
			{
				ReadHoldReg_Response.NumOfRegPtr[ 0 ] = ( ASI.status.brake & 0xFF00 ) >> 8;
				ReadHoldReg_Response.NumOfRegPtr[ 1 ] = ( ASI.status.brake & 0x00FF );
			}
			else if( ReadHoldReg_Response.NumOfDataByte == 4 )
			{
				// Fail Reg
				ReadHoldReg_Err.ExcepCode = _INVALID_NUM_OF_REG;
				ReadHoldReg_Err.Crc.word  = ModRTU_CRC( &ReadHoldReg_Err.SlaveID, 3 );
				UartWrite( &ReadHoldReg_Err.SlaveID, 5 );
				return;
			}
		}

		if( ReadHoldReg_Response.NumOfDataByte == 2 )
		{
			ASI_buf[ 3 ] = ASI_buf[ 0 ];
			ASI_buf[ 4 ] = ASI_buf[ 1 ];
		}
		else if( ReadHoldReg_Response.NumOfDataByte == 4 )
		{
			ASI_buf[ 6 ] = ASI_buf[ 3 ];
			ASI_buf[ 5 ] = ASI_buf[ 2 ];
			ASI_buf[ 4 ] = ASI_buf[ 1 ];
			ASI_buf[ 3 ] = ASI_buf[ 0 ];
		}
		
		ASI_buf[ 0 ] = ReadHoldReg_Response.SlaveID;
		ASI_buf[ 1 ] = ReadHoldReg_Response.FunCode;
		ASI_buf[ 2 ] = ReadHoldReg_Response.NumOfDataByte;

		ReadHoldReg_Response.Crc.word = ModRTU_CRC( ASI_buf, 3 + ReadHoldReg_Response.NumOfDataByte );

		ASI_buf[ 3 + ReadHoldReg_Response.NumOfDataByte ] = ReadHoldReg_Response.Crc.byte[ 0 ];
		ASI_buf[ 4 + ReadHoldReg_Response.NumOfDataByte ] = ReadHoldReg_Response.Crc.byte[ 1 ];

		UartWrite( ASI_buf, 5 + ReadHoldReg_Response.NumOfDataByte );
	}

	ASI_cmd = 0;
}
