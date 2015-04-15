//---------------------------------------------------------------------------

#ifndef diplom_v1H
#define diplom_v1H
//---------------------------------------------------------------------------

#include <iostream>
#include "stdlib.h"
#include "stdio.h"
#include <string>


#include "LCD_5110.h"
#include "motors.h"
#include "sensors.h"
#include "keyb_v1.h"


 class Diplom__V1 //: public Adafruit_PCD8544
 {
		public:
		Diplom__V1 (uint16_t * n);
		mot * motors;
		sens * sensors;
		keyb_1 * keyb ;
		uint16_t automatic_step;
		uint16_t automatic_step_sleep;
		LCD5110 * LC;
		uint16_t current_timer_tick;
		void init_lock_motor(int8_t pin_enable,int8_t pin_direction);
		void timer_20_ms_ON_TIMER();
		void chek_what_need_print();
		void begin_stopping_vibration(uint16_t timeout_20_ms);
		void begin_vibration_procedure(uint16_t timeout_20_ms);
		void begin_get_weight();
		void run_auto_procedure();
                void stop_auto_proc();  
		void ON_KEY_PRESSED();
		void KEY_WAS_PRESSED_COUNT(uint16_t button_id);

 };












#endif

