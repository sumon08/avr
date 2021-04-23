/*
 * rtc.c
 *
 * Created: 4/22/2021 10:22:04 PM
 * Author : Asus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "svsg.h"
#include "rtc.h"


volatile uint8_t time_up_flag  = 0;

ISR(TIMER2_COMP_vect)
{
	time_up_flag = 1;
}


void InitTimer()
{
	TCCR2 |= 1 << WGM21 | 1 << CS20 | 1 << CS21 | 1 << CS22;
	OCR2 = 0xB2; // want 5ms but got 4.9920 ms
	TIMSK |= 1 << OCIE2;
	sei();
}


void WriteTime(SegmentDisplay disp, Time * tim)
{
	DisplayWrite(disp, tim->hour / 10, 0);
	DisplayWrite(disp, tim->hour % 10, 1);
	
	DisplayWrite(disp, tim->min / 10, 2);
	DisplayWrite(disp, tim->min % 10, 3);
	
	DisplayWrite(disp, tim->sec / 10, 4);
	DisplayWrite(disp, tim->sec % 10, 5);
	
	DisplayWrite(disp, tim->year / 10, 6);
	DisplayWrite(disp, tim->year % 10, 7);
	
	DisplayWrite(disp, tim->month / 10, 8);
	DisplayWrite(disp, tim->month % 10, 9);
	
	DisplayWrite(disp, tim->date / 10, 10);
	DisplayWrite(disp, tim->date % 10, 11);
}

int main(void)
{
	SegmentDisplay disp = DisplayCreate();
	Clock clk = ClockCreate();
	InitTimer();
	Time tim;
	tim.sec = 11;
	tim.min = 15;
	tim.hour = 18;
	tim.date = 21;
	tim.month = 9;
	tim.year = 21;
	
	ClockSet(clk, &tim);
	
	WriteTime(disp, &tim);
    /* Replace with your application code */
    while (1) 
    {
		if (time_up_flag == 1)
		{
			time_up_flag = 0;
			DisplayUpdate(disp);
		}
		if (ClockIsUpdated(clk) == 1)
		{
			
			ClockGet(clk, &tim);
			WriteTime(disp,&tim);
		}
    }
}

