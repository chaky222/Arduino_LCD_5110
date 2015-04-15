

#include "motors.h"




mot::mot(uint16_t * n)
{
              pinMode(n[5], OUTPUT);
              digitalWrite(n[5], LOW);
              pinMode(n[6], OUTPUT);
              digitalWrite(n[6], LOW);
		for (int i = 0; i < 10; i++) {
           pins_array[i] = n[i+5];
           bool_move_array[i] = false;
		}
		current_motor_move = 0;
		bool_need_print_last_move_str = true;
		bool_printed_last_move_str = true;
		print_last_move_str="FIRST";
		time_out_of_20_milisecs = 0;
		is_stoping_now = false;

}

void mot::start_move	(uint8_t motor_id,bool dir,uint16_t time_20_ms)
{
	if (current_motor_move == 0) {
	   current_motor_move =  motor_id;
	   bool_move_array[motor_id] = true;
	   bool_move_array[motor_id+1] = dir;
	   time_out_of_20_milisecs = time_20_ms;

	   switch (motor_id)
	   {
			case 2: //sensors


			break;
			case 4://levels
				   if (dir) {
						print_last_move_str = "   Begin\n go UP\n  LEVELS! ";
				   }else{
						print_last_move_str = "   Begin\n go down\n  LEVELS! ";
				   }
				   bool_printed_last_move_str = false;
			break;
			case 8://vibro
                                if (dir){
                                    digitalWrite(pins_array[0], HIGH);
                                }else{
                                    digitalWrite(pins_array[0], LOW);
                                }
				  /*	if (dir) {
						print_last_move_str = "   Begin\n vibro\n  left! ";
				   }else{
						print_last_move_str = "   Begin\n vibro\n  right! ";
				   }
				   bool_printed_last_move_str = false;  */
				  //bool_printed_last_move_str = false;
			break;
			default:   break;
	   }
	}else{
       print_last_move_str = "   Wait\n while\n  move not\n  finished! ";
       bool_printed_last_move_str = false;
    }
}
void mot::stop_move (uint8_t motor_id)
{
	if (current_motor_move>0) {
	   current_motor_move = 0;
	   bool_move_array[motor_id]=false;
	   switch (motor_id)
		   {
				case 2: //sensors


				break;
				case 4://levels
					   if (bool_move_array[motor_id+1]) {
							print_last_move_str = "   Finished\n up\n  LEVELS! ";
					   }else{
							print_last_move_str = "   Finished\n down\n  LEVELS! ";
					   }
					   bool_printed_last_move_str = false;
				break;
				case 8://vibro
					  //print_last_move_str = "  ��������� \n  �i����i�  \n������������";
					  print_last_move_str = " Завершено \n  вiбрування.";
                      bool_printed_last_move_str = false;
				break;
				default:   break;
		}
	} else {
		print_last_move_str = "   Already\n stopped\n    all! ";
		bool_printed_last_move_str = false;
    }
}



void mot::check_move_timeouts()
{
   if (time_out_of_20_milisecs>0) {
      time_out_of_20_milisecs--;
   }
   if (current_motor_move>0) {
		if (current_motor_move==8) {
		  if ((time_out_of_20_milisecs%50)==0)
		  {
			 //bool dir =  ((time_out_of_20_milisecs%100) == 0);
			 bool dir =  (!(bool_move_array[current_motor_move+1] ));
			 current_motor_move = 0;
			 start_move(8,dir,time_out_of_20_milisecs);
		  }

		}
		if (time_out_of_20_milisecs<2) {
             stop_move(current_motor_move);
		}

   }
}

void mot::timer_20_miliseconds_ONTimer()
{
	 check_move_timeouts();
}
