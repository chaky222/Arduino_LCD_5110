#ifndef LCD_5110H
#define LCD_5110H
#if defined(ARDUINO) && ARDUINO >= 100
		#include <Adafruit_GFX.h>
		#include <Adafruit_PCD8544.h>
		#define CLOCK_TIMES 12
#else
		#include "Adafruit_GFX.h"
		#include "Adafruit_PCD8544.h"
		#include "my_arduino.h"
		#define CLOCK_TIMES 12
#endif
	#define char_height 8;
	#define char_width  6;

    class LCD5110 //: public Adafruit_PCD8544
    {
	public:
         LCD5110 (int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST);
         bool finished_draw; 
    
    public:		// User declarations
    	 Adafruit_PCD8544 * displays;
    public:
    	 uint16_t count_of_step;
    	 bool test_drawing;
    	 void LCD_INIT();
		 int get_num();
		 void clear();
		 void print_weight_results(uint16_t * weights_sit);
    	 //int min(int x,int y);
    

	void draw_demo();
	void draw_rus_demo();
	void draw_about();
	void write_string	(char * in_str,	bool clear = false,uint8_t x=254,uint8_t y=254);
	void write_str		(String in_str,	bool clear = false,uint8_t x=254,uint8_t y=254);
	void write_int		(int32_t in_int,bool clear = false,uint8_t x=254,uint8_t y=254);

	void write_int_chars(char * in_str);


	void presentation_draw();

	void testdrawchar(uint8_t type);
	void testdrawcircle();
	void testfillrect();
	void testdrawtriangle();
	void testfilltriangle();
	void testdrawroundrect();
	void testfillroundrect();
	void testdrawrect();
	void testdrawline(int step);


    };

#endif










