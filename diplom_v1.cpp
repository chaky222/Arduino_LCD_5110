//---------------------------------------------------------------------------

//#pragma hdrstop

#include "diplom_v1.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)




Diplom__V1::Diplom__V1 (uint16_t * n)
{
    
	  LC = new LCD5110(n[0],n[1],n[2],n[3],n[4]);
	  motors = new mot(n);
	  sensors = new sens(n);
	  keyb  = new keyb_1(n);
	  current_timer_tick = 0;
	  automatic_step = 0;
          LC->clear();
      //LC->draw_rus_demo();
}
void Diplom__V1::init_lock_motor(int8_t pin_enable,int8_t pin_direction)
{

}
void Diplom__V1::run_auto_procedure()
{
	if (automatic_step == 0)
	{
		begin_vibration_procedure(200);
		automatic_step = 6;


	}else{
        LC->clear();
        LC->write_str("   Початок \n просiювання. \n   Зачекайте. ",false,0,0);
    }
}
void Diplom__V1::stop_auto_proc()
{
    automatic_step = 0;  
}
void Diplom__V1::KEY_WAS_PRESSED_COUNT(uint16_t button_id)
{
   
   uint16_t count =keyb ->array_key_pressed_count_down_up[button_id];
   keyb ->array_key_pressed_count_down_up[button_id]= 0;
   switch (button_id) {
	   case 0:
              LC->test_drawing = false;
              run_auto_procedure();
	   break;
	   case 1:
              stop_auto_proc();
              LC->test_drawing = false;
              LC->draw_about();
	   break;
           case 2:
                stop_auto_proc();
                LC->test_drawing = true;
  	   break;


   default:

	   break;
   }

}

void Diplom__V1::ON_KEY_PRESSED()
{
	keyb ->key_pressed = false;
	for (int i = 0; i < 4; i++)
	{
		 if ( keyb ->array_key_pressed_count_down_up[i]>0) {
             KEY_WAS_PRESSED_COUNT(i);
		 }
	}

}

void Diplom__V1::timer_20_ms_ON_TIMER()
{
        keyb ->OnTimer_20_ms_check_keyboard();
        if (!(keyb ->stop_all))
        {
          
	 current_timer_tick++;
	 motors->timer_20_miliseconds_ONTimer();
	 LC->draw_demo();
	 
	 chek_what_need_print();
	 if ((current_timer_tick%10)==0) {// Every 0.2 second. 10Hz
          if (keyb ->key_pressed) {
			  ON_KEY_PRESSED();
		 }
	 }

	 if ((current_timer_tick%100)==0) {// Every 2 seconds. 1Hz
		  //chek_what_need_print();
                sensors->read_mouse();
                if (!((sensors->last_move_x==0)&&(sensors->last_move_y==0)))
                {
                     LC->clear();
                     LC->write_string("   MOUSE \n  \nX=     Y= \ndx=    dy=" ,false,0,0); 
                     LC->write_int(sensors->last_move_x,false,3,3);
                     LC->write_int(sensors->last_move_y,false,10,3);
                     LC->write_int(sensors->move_x,false,2,2);
                     LC->write_int(sensors->move_y,false,9,2);
                     sensors->last_move_x = 0;
                     sensors->last_move_y = 0;
                }
	 }
	  if (current_timer_tick>500) {// Every 10 seconds. 0.1Hz

		 current_timer_tick = 0;
	 }
	 if (motors->current_motor_move == 8) {
		 if (!(motors->is_stoping_now))
		 {
			 if (motors->time_out_of_20_milisecs < 100)
			 {
                  begin_stopping_vibration(200);
			 }
		 }
	 }
	 if (automatic_step>0)
	 {
		if (motors->current_motor_move ==0)
		{
		   switch (automatic_step) {
				case 5:
					 if (automatic_step_sleep > 1) {
						 automatic_step_sleep --;
						 if (automatic_step_sleep%50==0)
						 {
						 	  uint16_t tmp = automatic_step_sleep/50;
							  LC->write_string("      ",true,7,4);
							  LC->write_int(tmp,false,7,4);
                         }
					 } else {
						if (automatic_step_sleep ==0) {
							 automatic_step_sleep = 305;
							 motors->bool_printed_last_move_str=true;
							 begin_get_weight();
						}else{
							 automatic_step_sleep = 0;
							 automatic_step--;
						}
					 }
				break;
				case 4:
					 if (automatic_step_sleep > 1) {
						 automatic_step_sleep --;
					 } else {
						if (automatic_step_sleep ==0) {
							 automatic_step_sleep = 200;
							 motors->bool_printed_last_move_str=true;
                             uint16_t new_uint[] =  { 111,222,333,444,555};
							 LC->print_weight_results(new_uint);
						}else{
							 automatic_step_sleep = 0;
							 automatic_step--;
						}
					 }
				break;



		   default:
				automatic_step --;
				automatic_step_sleep = 0;
		   		break;
		   }


		}
	 }
        }

}

void Diplom__V1::begin_get_weight()
{
	LC->clear();
	LC->write_string("  \n  Процедура\n  зважування.",false,0,0);
}


void Diplom__V1::chek_what_need_print()
{
	 if (motors->bool_need_print_last_move_str)
	 {
		if (!( motors->bool_printed_last_move_str ))
		{
			motors->bool_printed_last_move_str = true;
			LC->displays->clearDisplay();
			LC->write_str(motors->print_last_move_str ,false,0,0);
			/*if (motors->current_motor_move==8) {
			   /*	LC->write_str("    " ,true,4,4);
				if (motors->bool_move_array[motors->current_motor_move]) {
					LC->write_str("--->" ,false,4,4);
				}else{
					LC->write_str("<---" ,false,4,4);
				}
			}else {

			}    //*/
			if (motors->current_motor_move>0) {
				LC->write_str("    " ,true,4,4);
				if (motors->bool_move_array[motors->current_motor_move+1]) {
					LC->write_str("--->" ,false,4,4);
				}else{
					LC->write_str("<---" ,false,4,4);
				}
				int32_t i = motors->time_out_of_20_milisecs/50;
				LC->write_int(i,true,8,4);
            }
		}else{
			if (motors->current_motor_move>0) {
				 LC->write_str("    " ,true,4,4);
				if (motors->bool_move_array[motors->current_motor_move+1]) {
					LC->write_str("--->" ,false,4,4);
				}else{
					LC->write_str("<---" ,false,4,4);
				}
				// if ((current_timer_tick%50)==0) {// Every second. 1Hz
					int32_t i = motors->time_out_of_20_milisecs/50;
					LC->write_int(i,true,8,4);
				// }
            }
        }
	 }
      
}

void Diplom__V1::begin_stopping_vibration(uint16_t timeout_20_ms)
{
   LC->clear();
   LC->write_str(" Завершення\n  вiбрацiй\n просiювання" ,false,0,0);
   motors->current_motor_move = 0;
   motors->is_stoping_now = true;
   motors->start_move(8,0,timeout_20_ms);

}
void Diplom__V1::begin_vibration_procedure(uint16_t timeout_20_ms)
{
   LC->clear();
   LC->write_str("  Процедура\n  вiбрацiй\n просiювання" ,false,0,0);
   motors->is_stoping_now = false;
   motors->start_move(8,0,timeout_20_ms);
}
