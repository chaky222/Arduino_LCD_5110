

#include "keyb_v1.h"



keyb_1::keyb_1(uint16_t * n)
{
   stop_all = false; 
   for (int i = 0; i < 4; i++) {
	   pins_array[i] = n[i+15];
	   #if defined(ARDUINO) && ARDUINO >= 100
			pinMode(pins_array[i], INPUT);
	   #else
			pinMode(pins_array[i], INPUTs);
	   #endif
	   array_key_pressed_count_down_up	[i] = 0;
	   array_key_pressed_and_hold_counts[i] = 0;
	   bool_array_key_DOWN				[i] = false;
   }
   interval_for_next_keyboard_check = 0;
   key_pressed = false;
}

void keyb_1::OnTimer_20_ms_check_keyboard()
{
   read_keys();
}

void keyb_1::read_keys()
{
int buttonState = 0;
	for (int i = 0; i < 4; i++)
	{
	   buttonState = digitalRead(pins_array[i]);
	   //if (buttonState == HIGH) {  // key down
           if (buttonState == LOW) {  // key down
			if (!(bool_array_key_DOWN[i]))
			{
				ON_KEY_DOWN(i);
			} else { //continue pressing
                ON_KEY_PRESS_AND_HOLD(i);
            }
	   }else{
			if (bool_array_key_DOWN[i])  // KEY WAS DOWN earlier! ON_key_UP_EVENT!
			{
                ON_KEY_UP(i);
            }
       }
   }
}
void keyb_1::ON_KEY_DOWN			(uint8_t keyboard_key)
{
	bool_array_key_DOWN[keyboard_key] = true;
        if (keyboard_key == 3 ){
            stop_all = true;
        }
         set_some_key_was_pressed(keyboard_key);
}
void keyb_1::ON_KEY_UP				(uint8_t keyboard_key)
{
	// array_key_pressed_and_hold_counts	[keyboard_key] = 0;
	 bool_array_key_DOWN[keyboard_key] = false;
        if (keyboard_key == 3 ){
            stop_all = false;
        }
	// set_some_key_was_pressed(keyboard_key);
}
void keyb_1::ON_KEY_PRESS_AND_HOLD (uint8_t keyboard_key)
{
	 array_key_pressed_and_hold_counts		[keyboard_key] ++;
	 if (array_key_pressed_and_hold_counts	[keyboard_key] > 25)
	 {
		 set_some_key_was_pressed(keyboard_key);
	 }
}
void keyb_1::set_some_key_was_pressed(uint8_t keyboard_key)
{
	array_key_pressed_and_hold_counts[keyboard_key] = 0;
	array_key_pressed_count_down_up	[keyboard_key] ++;
        if (!key_pressed) {
		 key_pressed = true;
	}
}




