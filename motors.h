//---------------------------------------------------------------------------

#ifndef motorsH
#define motorsH
//---------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
 	#include "my_arduino.h"
#endif

#define motor_sensors = 0
#define motor_levels = 2


 class mot
{
	public:
		mot(uint16_t * n);



	public:
		//pin section
		uint16_t pins_array[10];
		bool bool_move_array[10];
		/*
		//	2 = sensors ; 3=sensors_dir ;
			4 = levels;   5=levels_dir;
			6 = lockers;
			8 = vibro;	  9= vibro_dir
		*/


		uint16_t 		time_out_of_20_milisecs;

		//stat section

		//bool bool_move_finished;
        uint8_t current_motor_move;


		//print section
		String print_last_move_str;
		bool bool_printed_last_move_str;
		bool bool_need_print_last_move_str;

		bool is_stoping_now;

		void start_move		 	(uint8_t motor_id,bool dir,uint16_t time_20_ms = 500);
		void stop_move          (uint8_t motor_id);


		void check_move_timeouts();

		void timer_20_miliseconds_ONTimer();
		//int8_t	stepper_pin_1, stepper_pin_2,stepper_pin_3,stepper_pin_4;
};














#endif

