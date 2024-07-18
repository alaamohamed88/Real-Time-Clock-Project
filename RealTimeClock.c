/*
 * RealTimeClock.c
 *
 * Created: 06/08/2023 01:26:22 م
 *  Author: Alaa Mohamed
 */ 


#define  F_CPU 8000000UL
#include <util/delay.h>
#include "TIMER.h"
#include "INTERRUPT_CONFIG.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "SevenSegment.h"

volatile unsigned char seconds_counter = 0;
unsigned char minutes_counter = 0, hours_counter = 0;
unsigned char character, first_digit, second_digit;
int main(void)
{
	TIMER2_OVERFLOWInitializeInterrupt();
	LCD_Initialize();
	KEYPAD_Initialize();
	SevenSegmentInitialize();
	SET_BIT(MyDDRC,0);
	SET_BIT(MyDDRC,1);
	SET_BIT(MyDDRC,2);
	SET_BIT(MyDDRC,3);
	SET_BIT(MyDDRC,4);
	SET_BIT(MyDDRC,5);
	LCD_SendString("1: Set Clock");
	while(1)
    {
        character = KEYPAD_ReadPress();
		if (character != NOT_PRESSED)
		{
			if (character == '1')
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Hours:");
				LCD_MoveCursor(1,7);
				_delay_ms(500);
				do 
				{
					first_digit = KEYPAD_ReadPress();
				} while (first_digit == NOT_PRESSED);
				LCD_SendCharacter(first_digit);
				_delay_ms(300);
				do
				{
					second_digit = KEYPAD_ReadPress();
				} while (second_digit == NOT_PRESSED);
				LCD_SendCharacter(second_digit);
				_delay_ms(300);
				hours_counter = ((first_digit-48)*10)+(second_digit-48);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Minutes:");
				LCD_MoveCursor(1,9);
				do
				{
					first_digit = KEYPAD_ReadPress();
				} while (first_digit == NOT_PRESSED);
				LCD_SendCharacter(first_digit);
				_delay_ms(300);
				do
				{
					second_digit = KEYPAD_ReadPress();
				} while (second_digit == NOT_PRESSED);
				LCD_SendCharacter(second_digit);
				_delay_ms(300);
				minutes_counter = ((first_digit-48)*10)+(second_digit-48);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Seconds:");
				LCD_MoveCursor(1,9);
				do
				{
					first_digit = KEYPAD_ReadPress();
				} while (first_digit == NOT_PRESSED);
				LCD_SendCharacter(first_digit);
				_delay_ms(300);
				do
				{
					second_digit = KEYPAD_ReadPress();
				} while (second_digit == NOT_PRESSED);
				LCD_SendCharacter(second_digit);
				_delay_ms(300);
				seconds_counter = ((first_digit-48)*10)+(second_digit-48);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("1: Set Clock");
			}
			else
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Wrong choice");
				_delay_ms(1000);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("1: Set Clock");
			}
		}
		
		SET_BIT(MyPORTC,1);
		SET_BIT(MyPORTC,2);
		SET_BIT(MyPORTC,3);
		SET_BIT(MyPORTC,4);
		SET_BIT(MyPORTC,5);
		CLEAR_BIT(MyPORTC,0);
		SevenSegmentWrite(seconds_counter%10);
		_delay_ms(5);
		SET_BIT(MyPORTC,0);
		SET_BIT(MyPORTC,2);
		SET_BIT(MyPORTC,3);
		SET_BIT(MyPORTC,4);
		SET_BIT(MyPORTC,5);
		CLEAR_BIT(MyPORTC,1);
		SevenSegmentWrite(seconds_counter/10);
		_delay_ms(5);
		SET_BIT(MyPORTC,0);
		SET_BIT(MyPORTC,1);
		SET_BIT(MyPORTC,3);
		SET_BIT(MyPORTC,4);
		SET_BIT(MyPORTC,5);
		CLEAR_BIT(MyPORTC,2);
		SevenSegmentWrite(minutes_counter%10);
		_delay_ms(5);
		SET_BIT(MyPORTC,0);
		SET_BIT(MyPORTC,1);
		SET_BIT(MyPORTC,2);
		SET_BIT(MyPORTC,4);
		SET_BIT(MyPORTC,5);
		CLEAR_BIT(MyPORTC,3);
		SevenSegmentWrite(minutes_counter/10);
		_delay_ms(5);
		SET_BIT(MyPORTC,0);
		SET_BIT(MyPORTC,1);
		SET_BIT(MyPORTC,2);
		SET_BIT(MyPORTC,3);
		SET_BIT(MyPORTC,5);
		CLEAR_BIT(MyPORTC,4);
		SevenSegmentWrite(hours_counter%10);
		_delay_ms(5);
		SET_BIT(MyPORTC,0);
		SET_BIT(MyPORTC,1);
		SET_BIT(MyPORTC,2);
		SET_BIT(MyPORTC,3);
		SET_BIT(MyPORTC,4);
		CLEAR_BIT(MyPORTC,5);
		SevenSegmentWrite(hours_counter/10);
		_delay_ms(5);
		if (seconds_counter >= 60)
		{
			seconds_counter = 0;
			minutes_counter++;
		}
		if (minutes_counter == 60)
		{
			minutes_counter = 0;
			hours_counter++;
		}
		if (hours_counter == 24)
		{
			hours_counter = 0;
		}			
    }
}
ISR(TIMER2_OVF_vect)
{
	seconds_counter++;
}