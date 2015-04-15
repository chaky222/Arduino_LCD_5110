//---------------------------------------------------------------------------

#ifndef sensorsH
#define sensorsH

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
 	#include "my_arduino.h"
#endif
#include <ps2.h>  
 class sens
{
	public:
		sens(uint16_t * n);
	public:
		//pin section
                uint16_t                pins_array[10];
                int16_t                  last_move_x;
                int16_t                  last_move_y;
                int16_t                  move_x;
                int16_t                  move_y;
                PS2 *  mouse;
                void mouse_init();
                void read_mouse();
                void ON_TIMER_20_ms();
		uint16_t		pin_locker_enable;
		uint16_t		pin_locker_direction;
		uint16_t		pin_up_down_sit_enable;
		uint16_t		pin_up_down_sit_direction;
		uint16_t		pin_vibro_enable;
		uint16_t		pin_vibro_direction;

		//stat section
		bool move_finished;

		//print section
		String print_last_move_str;
		bool printed_last_move_str;



		//int8_t	stepper_pin_1, stepper_pin_2,stepper_pin_3,stepper_pin_4;
};
#endif

