//---------------------------------------------------------------------------

#ifndef keyb_v1H
#define keyb_v1H
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
 	#include "my_arduino.h"
#endif

class keyb_1 //: public Adafruit_PCD8544
{
	public:
		 keyb_1(uint16_t * n);
		 uint16_t pins_array[10];
         uint16_t interval_for_next_keyboard_check;
         void OnTimer_20_ms_check_keyboard();
		 bool key_pressed;
		 uint16_t array_key_pressed_count_down_up	[5];
         uint16_t array_key_pressed_and_hold_counts[5];
		 bool bool_array_key_DOWN[5];
                  bool stop_all;
		 void read_keys();
         void set_some_key_was_pressed(uint8_t keyboard_key);
		 void ON_KEY_DOWN			(uint8_t keyboard_key);
		 void ON_KEY_UP				(uint8_t keyboard_key);
		 void ON_KEY_PRESS_AND_HOLD (uint8_t keyboard_key);

};




#endif

