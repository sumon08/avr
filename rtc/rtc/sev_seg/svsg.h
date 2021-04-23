/*
 * svsg.h
 *
 * Created: 4/22/2021 10:22:47 PM
 *  Author: Asus
 */ 


#ifndef SVSG_H_
#define SVSG_H_

#include <stdint.h>

typedef void * SegmentDisplay;

SegmentDisplay DisplayCreate();
void DisplayUpdate(SegmentDisplay disp);
void DisplayClear(SegmentDisplay disp);
void DisplayWrite(SegmentDisplay disp, uint8_t data, uint8_t index);
void DisplayDisable(SegmentDisplay disp);

#endif /* SVSG_H_ */