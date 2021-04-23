/*
 * rtc.h
 *
 * Created: 4/22/2021 11:53:56 PM
 *  Author: Asus
 */ 


#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>


typedef void * Clock;

typedef enum
{
	MONTH_JANUARY = 1,
	MONTH_FEBRUARY,
	MONTH_MARCH,
	MONTH_APRIL,
	MONTH_MAY,
	MONTH_JUNE,
	MONTH_JULY,
	MONTH_AUGUST,
	MONTH_SEPTEMBER,
	MONTH_OCTOBER,
	MONTH_NOVEMBER,
	MONTH_DECEMBER
}Month;

typedef struct 
{
	uint8_t year;
	Month month;
	uint8_t date;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}Time;

Clock		ClockCreate();
void		ClockSet(Clock clock, Time * tim);
void		ClockGet(Clock clock, Time * tim);
uint8_t		ClockIsUpdated(Clock clock);

#endif /* RTC_H_ */