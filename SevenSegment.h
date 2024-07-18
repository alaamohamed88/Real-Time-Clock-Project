/*
 * SevenSegment.h
 *
 * Created: 18/02/2023 06:41:47 م
 *  Author: Alaa Mohamed
 */ 


#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include "DIO_Driver.h"

#define COMMON_CATHODE
#define SEVEN_SEGMENT_PORT 'B'
void SevenSegmentInitialize();
void SevenSegmentWrite(unsigned char Number);

#endif /* SEVENSEGMENT_H_ */