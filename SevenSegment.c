/*
 * SevenSegment.c
 *
 * Created: 18/02/2023 06:43:32 م
 *  Author: Alaa Mohamed
 */ 

#include "SevenSegment.h"

void SevenSegmentInitialize()
{
	DIO_setPortDirection(SEVEN_SEGMENT_PORT,0xff);
}

void SevenSegmentWrite(unsigned char Number)
{
	#if defined COMMON_CATHODE
	unsigned char arr_7Seg[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7f,0x39,0x3f,0x79,0x71};
	DIO_writePort(SEVEN_SEGMENT_PORT,arr_7Seg[Number]);
	
	#elif defined COMMON_ANODE
	unsigned char arr_7Seg[] = {~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x07,~0x7f,~0x6f,~0x77,~0x7f,~0x39,~0x3f,~0x79,~0x71};
	DIO_writePort(SEVEN_SEGMENT_PORT,arr_7Seg[Number]);
	
	#endif
}