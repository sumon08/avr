/*
 * svsg_config.h
 *
 * Created: 4/22/2021 10:24:44 PM
 *  Author: Asus
 */ 


#ifndef SVSG_CONFIG_H_
#define SVSG_CONFIG_H_

#include <avr/io.h>

#define CONFIG_SEGMENT_DISPLAY

#ifdef CONFIG_SEGMENT_DISPLAY

#ifndef CONFIG_SEGMENT_DISPLAY_DATA_PORT
#define CONFIG_SEGMENT_DISPLAY_DATA_PORT				PORTB
#endif

#ifndef CONFIG_SEGMENT_DISPLAY_DATA_DDR		
#define CONFIG_SEGMENT_DISPLAY_DATA_DDR					DDRB	
#endif

#ifndef CONFIG_SEGMENT_DISPLAY_ADDRESS_DDR				
#define CONFIG_SEGMENT_DISPLAY_ADDRESS_DDR				DDRC
#endif

#ifndef CONFIG_SEGMENT_DISPLAY_ADDRESS_PORT
#define CONFIG_SEGMENT_DISPLAY_ADDRESS_PORT				PORTC
#endif

#ifndef CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER			
#define CONFIG_SEGMENT_DISPLAY_SEGMENT_NUMBER			12 
#endif

#define CONFIG_GLYPH_0									0x7E
#define CONFIG_GLYPH_1									0x30
#define CONFIG_GLYPH_2									0x6D
#define CONFIG_GLYPH_3									0x79
#define CONFIG_GLYPH_4									0x33
#define CONFIG_GLYPH_5									0x5B
#define CONFIG_GLYPH_6									0x5F
#define CONFIG_GLYPH_7									0x70
#define CONFIG_GLYPH_8									0x7F
#define CONFIG_GLYPH_9									0x7B

#endif


#endif /* SVSG_CONFIG_H_ */