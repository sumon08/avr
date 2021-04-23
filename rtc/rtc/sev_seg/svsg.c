/*
 * svsg.c
 *
 * Created: 4/22/2021 10:23:01 PM
 *  Author: Asus
 */ 


#include "svsg.h"
#include "svsg_config.h"
#include <string.h>


typedef struct
{
	uint8_t buffer[CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER];
	uint8_t scan_index;
	uint8_t initialized;
}Display;

static Display display;


SegmentDisplay DisplayCreate()
{
	if (display.initialized == 0)
	{
		memset(display.buffer, CONFIG_GLYPH_0, CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER);
		display.initialized = 1;
		display.scan_index = 0;
		CONFIG_SEGMENT_DISPLAY_DATA_DDR = 0xFF;
		CONFIG_SEGMENT_DISPLAY_ADDRESS_DDR = 0xFF;
		DDRD |= 1 << PD0;
	}
	return &display;
}

void DisplayUpdate(SegmentDisplay disp)
{
	Display * d = (Display *)disp;
	PORTD |= (1 << PD0);
	CONFIG_SEGMENT_DISPLAY_DATA_PORT = d->buffer[d->scan_index];
	CONFIG_SEGMENT_DISPLAY_ADDRESS_PORT = d->scan_index;
	PORTD &= ~(1 << PD0);
	d->scan_index++;
	if (d->scan_index == CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER)
	{
		d->scan_index = 0;
	}
}

void DisplayClear(SegmentDisplay disp)
{
	Display * d = (Display *)disp;
	memset(d->buffer, CONFIG_GLYPH_0, CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER);
}

void DisplayWrite(SegmentDisplay disp, uint8_t data, uint8_t index)
{
	if (index >= CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER || data > 9)
	{
		return;
	}
	
	Display * d = (Display *)disp;
	
	switch(data)
	{
		case 0:
		d->buffer[index] = CONFIG_GLYPH_0;
		break;
		case 1:
		d->buffer[index] = CONFIG_GLYPH_1;
		break;
		case 2:
		d->buffer[index] = CONFIG_GLYPH_2;
		break;
		case 3:
		d->buffer[index] = CONFIG_GLYPH_3;
		break;
		case 4:
		d->buffer[index] = CONFIG_GLYPH_4;
		break;
		case 5:
		d->buffer[index] = CONFIG_GLYPH_5;
		break;
		case 6:
		d->buffer[index] = CONFIG_GLYPH_6;
		break;
		case 7:
		d->buffer[index] = CONFIG_GLYPH_7;
		break;
		case 8:
		d->buffer[index] = CONFIG_GLYPH_8;
		break;
		case 9:
		d->buffer[index] = CONFIG_GLYPH_9;
		break;
	}
}

void DisplayDisable(SegmentDisplay disp)
{
	Display * d = (Display *)disp;
	memset(d->buffer, 0, CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER);
}
