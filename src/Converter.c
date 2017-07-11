#include "Typedef.h"

code S8 HexChar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void S16toStr(S16 value, S8 *buff)
{
	U8 i, sign;
	U8 j;
	S8 temp;

	if (value == 0)
	{
		buff[0] = '0';
		buff[1] = 0;
		return;
	}

	if (value < 0)
	{
		sign = 1;
		value = 0 - value;
	}
	else
		sign = 0;

	i = 0;
	while (value)
	{
		buff[i] = HexChar[value % 10];
		value /= 10;
		i++;
	}

	if (sign)
	{
		buff[i] = '-';
		i++;
	}
	buff[i] = 0;

	for (j = 0; j < (i / 2); j++)
	{
		temp = buff[j];
		buff[j] = buff[i - j -1];
		buff[i - j -1] = temp;
	}
}

void U16toStr(U16 value, S8 *buff)
{
	U8 i;
	U8 j;
	S8 temp;

	if (value == 0)
	{
		buff[0] = '0';
		buff[1] = 0;
		return;
	}

	i = 0;
	while (value)
	{
		buff[i] = HexChar[value % 10];
		value /= 10;
		i++;
	}

	buff[i] = 0;

	for (j = 0; j < (i / 2); j++)
	{
		temp = buff[j];
		buff[j] = buff[i - j -1];
		buff[i - j -1] = temp;
	}
}


