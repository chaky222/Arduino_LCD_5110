
#include "sensors.h"


sens::sens(uint16_t * n)
{
                mouse = new PS2(49, 46);
		pin_locker_enable = 0;
		pin_locker_direction = 0;
		pin_up_down_sit_enable= 0;
		pin_up_down_sit_direction=0;
		pin_vibro_enable=0;
		pin_vibro_direction=0;
		move_finished =true;
                last_move_x=0;
                last_move_y=0;
                move_x=0;
                move_y=0;
                mouse_init();
}

void sens::mouse_init()
{
  mouse->write(0xff);  // reset
  mouse->read();  // ack byte
  mouse->read();  // blank */
  mouse->read();  // blank */
  mouse->write(0xf0);  // remote mode
  mouse->read();  // ack
  delayMicroseconds(100);
}
void sens::read_mouse()
{  
  char mstat;
  char mx;
  char my;

  /* get a reading from the mouse */
  mouse->write(0xeb);  // give me data!
  mouse->read();      // ignore ack
  mstat = mouse->read();
  mx = mouse->read();
  my = mouse->read();
  last_move_x = mx;
  last_move_y = my;
  move_x += last_move_x;
  move_y += last_move_y;
}

void sens::ON_TIMER_20_ms()
{
  
}
