

//#include <LCD_5110.h>
//#include "LCD_5110.h"
//#include "Adafruit_PCD8544.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ps2.h>  
#include <ve_avr.h>
//#include <LCD_5110.h>
//#include "LCD_5110.h"
#include "Diplom_V1.h"
//Adafruit_PCD8544 * display;
//#define CLOCK_TIMES_for_10_miliseconds 1280
#define CLOCK_TIMES_for_10_miliseconds 2560
//#define CLOCK_TIMES_for_10_miliseconds 320
//#define CLOCK_TIMES_for_10_miliseconds 640

uint16_t new_uint[] =  {
	52, 53, 50, 51, 48, //new LCD5110(
 	47,44,1,1,1, //motors
	1,1,1,1,1, //motors_2
	40,42,43,45,1, //keyboard_1
	1,1,1,1,1   //sensors1
 };
/* 
uint16_t new_uint[] =  {
	1,1,1,1,1, //new LCD5110(
	1,1,1,1,1, //motors
	1,1,1,1,1, //motors_2
	1,1,1,1,1, //keyboard_1
	1,1,1,1,1
 };
*/
Diplom__V1 *Dip = new Diplom__V1(new_uint);
//LCD5110 * LC = new LCD5110(52, 53, 50, 51, 48);
uint16_t curr_step = 0;

void setup()   {
  Serial.begin(9600);
  //LC->test_drawing = true;
 // LC = new LCD5110(1);
 
   // DEV_TIMER1.setClockSelect(TimerW::Prescaler_64);	// 16MHz / 64 = 250 kHz. Timer1 will 
    DEV_TIMER1.setClockSelect(TimerW::Prescaler_64);	// 16MHz / 64 = 250 kHz. Timer1 will// increase its TCNT value each 4 us.
 //   DEV_TIMER1.setClockSelect(TimerW::Prescaler_8);	// 16MHz / 64 = 250 kHz. Timer1 will// increase its TCNT value each 4 us.
    DEV_TIMER1.setWaveGenMode(TimerW::FastPWM_OCRA);	// Timer1 will compare its TCNT value
    DEV_TICTRL1.outCompIntEnableA();	// TIMER1_COMPA_vect ISR handler will be called. 
    interrupts();    			// Enable interrupts also. 
   Dip->LC->draw_about(); 
/*  LC->displays->clearDisplay();
  LC->displays->setTextSize(1);
  LC->displays->setTextColor(BLACK);
  LC->displays->setCursor(0,0);
LC->write_string("Andrey ");
LC->write_int(123);
LC->write_string(" Андрей");
LC->write_string("gotАндрейGot");*/
   // LC->draw_rus_demo();
   
}


void loop() {
 // LC->testfilltriangle();  
 //LC->presentation_draw();
 //LC->testdrawchar();
 //delay(1);
 //LC->draw_demo();
 //delay(10);
}

ISR(TIMER1_COMPA_vect)
{ 
       curr_step++;
       if (curr_step>CLOCK_TIMES_for_10_miliseconds) {
           curr_step = 0;
           Dip->timer_20_ms_ON_TIMER();
           // here is 10 miliseconds!
          // LC->draw_demo();
       } 
    //DEV_TIMER1.setOutputCompareA(potValue);	// This sets next interrupt timeout. 
   // bLedOn = ! bLedOn;						// This says the main program to change LED state.
}
