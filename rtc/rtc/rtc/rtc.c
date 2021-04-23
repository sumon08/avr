/*
 * rtc.c
 *
 * Created: 4/22/2021 11:54:06 PM
 *  Author: Asus
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "rtc.h"
#include <string.h>


typedef struct
{
	Time time;
	Time buffer;
	uint8_t is_set;
	uint8_t is_updated;
	uint8_t is_initialized;
}ClockInternal;

static ClockInternal ck;




void InitialiseHardwareTimer()
{
	TCCR1A = 0;
	TCCR1B |= 1 << WGM12 | 1 << CS10 | 1 << CS12;  // 1024 prescaler
	OCR1A = 0x3D08;
	TIMSK |= 1 << OCIE1A;
	sei();
}

Clock		ClockCreate()
{
	if (ck.is_initialized == 0)
	{
		ck.is_initialized = 1;
		memset(&ck.time, 0, sizeof(Time));
		memset(&ck.buffer, 0, sizeof(Time));
		ck.is_set = 0;
		ck.is_updated = 0;		
		InitialiseHardwareTimer();
	}
	return &ck;
}
void		ClockSet(Clock clock, Time * tim)
{
	ClockInternal * clk = (ClockInternal *)clock;
	clk->buffer.date = tim->date;
	clk->buffer.hour = tim->hour;
	clk->buffer.min = tim->min;
	clk->buffer.month = tim->month;
	clk->buffer.sec = tim->sec;
	clk->buffer.year = tim->year;
	clk->is_set = 1;
}
void		ClockGet(Clock clock, Time * tim)
{
	ClockInternal * clk = (ClockInternal *)clock;
	memcpy(tim, &clk->time, sizeof(Time));
}


uint8_t		ClockIsUpdated(Clock clock)
{
	ClockInternal * clk = (ClockInternal *)clock;
	if (clk->is_updated == 1)
	{
		clk->is_updated = 0;
		return 1;
	}
	return 0;
}

uint8_t IsLeapYear(int year)
{
	// not handled right now. will write code later
	return 0;
}

uint8_t GetDayInMonth(Month month)
{
	uint8_t day = 0;
	
	switch(month)
	{
		case MONTH_JANUARY:
		day = 31;
		break;
		case MONTH_FEBRUARY:
		day = IsLeapYear(ck.time.year)? 29 : 28;
		break;
		case MONTH_MARCH:
		day = 31;
		break;
		case MONTH_APRIL:
		day = 30;
		break;
		case MONTH_MAY:
		day = 31;
		break;
		case MONTH_JUNE:
		day = 30;
		break;
		case MONTH_JULY:
		day = 31;
		break;
		case MONTH_AUGUST:
		day = 31;
		break;
		case MONTH_SEPTEMBER:
		day = 30;
		break;
		case MONTH_OCTOBER:
		day = 31;
		break;
		case MONTH_NOVEMBER:
		day = 30;
		break;
		case MONTH_DECEMBER:
		day = 31;
		break;
		default:
		day = 30;
		break;
		
	}
	return day;
}

ISR(TIMER1_COMPA_vect)
{
	if (ck.is_set == 1)
	{
		ck.is_set = 0;
		ck.time = ck.buffer;
	}
	ck.time.sec++;
	if (ck.time.sec == 60)
	{
		ck.time.min++;
		ck.time.sec = 0;
	}			
	else
		return;
			
	if (ck.time.min == 60)
	{
		ck.time.hour++;
		ck.time.min = 0;
	}
	else
		return;
	
	if (ck.time.hour == 24)
	{
		ck.time.hour = 0;
		ck.time.date ++;
	}
	else
		return;
		
	if (ck.time.date == GetDayInMonth(ck.time.month))
	{
		ck.time.date = 1;
		ck.time.month ++;
	}
	else
		return;
	
	if(ck.time.month == 13)
	{
		ck.time.month = MONTH_JANUARY;
		ck.time.year ++;
	}
	
	ck.is_updated = 1;
}