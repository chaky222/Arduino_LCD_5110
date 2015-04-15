#include "LCD_5110.h"
#include "Math.h"
//#include <iostream>   // std::cout
//#include <string>     // std::string, std::to_string

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16



void LCD5110::LCD_INIT()
{


}





LCD5110::LCD5110 (int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST)
{
	displays = new Adafruit_PCD8544(SCLK, DIN, DC, CS, RST);
        displays->begin();
        displays->setContrast(50);
	count_of_step = 0;
	test_drawing = false;
        finished_draw = true;
}

int LCD5110::get_num()
{
    return 5;
}
void LCD5110::draw_demo()
{
   if (test_drawing) {
        if (finished_draw) {                   
	   count_of_step++;
	   if (count_of_step>60000) {
		  count_of_step = 0;
	   }
	   int num_step = 0;
	   if ((count_of_step%CLOCK_TIMES)==0) {
		   finished_draw = false;
		   num_step  = count_of_step/CLOCK_TIMES;                   
	   }
	   if ((num_step >0)&&(num_step<5)){
		   testdrawline(num_step);
	   }
	   if ((num_step >4)&(num_step<76)){
                  uint8_t tmp = (num_step - 4);
                  tmp=tmp/10;
		  testdrawchar(tmp);
                  //delay(100);
	   }           
	   if (num_step >=76) {
               count_of_step = 0;
	   }
           if (num_step >0) {
               finished_draw = true;
	   }  
       }
   }
}

void LCD5110::clear()
{
  displays->clearDisplay();
  displays->setTextSize(1);
  displays->setTextColor(BLACK);
}
void LCD5110::print_weight_results(uint16_t * weights_sit)
{
   clear();
   write_str(" Вага сит, г:\n 8mm \n 6mm \n 4mm \n 2mm \n 0mm ",false,0,0);
   for (int i = 0; i < 5; i++)
   {
	  write_int(weights_sit[i],false,8,i+1);
   }
}
void LCD5110::draw_about()
{
  clear();
  write_str("  Дипломный\n    проeкт \nГранулометр 1\nЧернуха А. П.\nCУА-10 2014год",false,0,0);
}

void LCD5110::draw_rus_demo()
{
  displays->clearDisplay();
  displays->setTextSize(1);
  displays->setTextColor(BLACK);
  write_str("  Дипломный\n    проeкт \nГранулометр 1\nЧернуха А. П.\nCУА-10 2014год",false,0,0);
 // write_int_chars("Д");
 // displays->setCursor(0,char_height);
 // write_string("Д");
  
  //write_string("Дипломный");
 // write_string("   Дипломный\n    проeкт \nГранулометр 1\nЧернуха А. П.\nCУА-10 2014год");

  // write_string("   Дипломный");//\n    проeкт \nГранулометр 1\nЧернуха А. П.\nCУА-10 2014год");
/*  displays->s etCursor(0,i*char_height); i++;
  write_string("    проeкт");
  displays->setCursor(0,i*char_height);  i++;
  write_string("Гранулометр v1");
  displays->setCursor(0,i*char_height);  i++;
  write_string(" Чернуха А. П.");
  displays->setCursor(0,i*char_height);  i++;
  write_string("CУА-10 2014год");
  //String s222 = "АБВГ";
	char * b  = "Андрей";
    /*int count = (unsigned)strlen(b);
	for (int i =0;i<count;i++)
	{ 
           uint8_t ch = b[i];
           //ch = ch + 48;
           char a[10];
	   itoa(ch,a,10); 
           char *cstr = a;
           write_string(cstr,0); 
           write_string(",",0); 
  
        }
	/*uint8_t ch = s222[2];
	char a[10];
	itoa(ch,a,10);
	String s2 = a;
	//String s3 = b;
	//String str = s3+"="+s2;
        char *cstr = a;
	//char *cstr = new char[str.length() + 1];
	//strcpy(cstr, char*(str));*/
	//delete [] cstr;
}

void LCD5110::write_int_chars(char * in_str)
{
int count = (unsigned)strlen(in_str);

int beg_count = 0;
/*
//char * str3 ="";
int count = 0;
#if defined(ARDUINO) && ARDUINO >= 100
	count = in_str.length()+1;
         beg_count = 1;
		String str3 = in_str;
#else
		count = in_str.Length();
		 beg_count = 0;
        char * str3 = AnsiString(in_str.Unique()).c_str();
#endif            //*/

// str3 = AnsiString(in_str);
// UnicodeString u1 = in_str.Unique();
	for (int i =beg_count;i<count;i++)
	{ 
		   uint8_t ch = in_str[i];
                   displays->write(ch); 
                   displays->write('=');
		   //ch = ch + 48;
                   char a[10];
	   	   itoa(ch,a,10);
		   char *cstr = a;
		   int count1 = (unsigned)strlen(cstr);
           for (int i1 =0;i1<count1;i1++)
           {
               uint8_t ch1 = cstr[i1];
			displays->write(ch1);
           }
		   //write_string(cstr);		   
		  // write_string("=");		   
		   displays->write(',');
		  // write_string(",");
        }
        displays->display();
}

void LCD5110::write_int(int32_t in_int,bool clear,uint8_t x,uint8_t y)
{
  char a[10];
  itoa(in_int,a,10);
  char *cstr = a;
 // write_int_chars(cstr); 
  write_string(cstr,clear,x,y);
}

void LCD5110::write_str(String in_str,bool clear,uint8_t x,uint8_t y)
{
	  #if defined(ARDUINO) && ARDUINO >= 100
			  char str3[500];
			  in_str.toCharArray(str3, 500) ;
	  #else
			  char * str3 = AnsiString(in_str.Unique()).c_str();
	  #endif
 	write_string(str3,clear,x,y);
}

void LCD5110::write_string(char * in_str,bool clear,uint8_t x,uint8_t y)
{
int count = (unsigned)strlen(in_str);
int beg_count = 0;
if (x<254) {
   uint8_t y1 = 0;
   uint8_t x1 = x* char_width;
   if (y<254) {
      y1 = y* char_height;
   }
   displays->setCursor(x1,y1);
}

	for (int i =beg_count;i<count;i++)
	{
		uint8_t ch = in_str[i];
		 //ch = ch+176;
		if ((ch==208)||(ch==209))
		{
			i++;
			if (ch == 208) {
				ch = in_str[i];
				ch = ch + 48;
			} else {
				ch = in_str[i];
				ch = ch + 112;
			}
		}
		if (clear)
		{
			  uint16_t curr_x =  displays->get_cursor_x();
			  uint16_t curr_y =  displays->get_cursor_y();
              displays->setTextSize(1);
			  displays->setTextColor(WHITE);
			  displays->write(7);
			  displays->setCursor(curr_x,curr_y);
			  displays->write(8);
			  displays->setCursor(curr_x,curr_y);
			  displays->setTextColor(BLACK);
		}
		displays->write(ch);

	}
	displays->display();
}

void LCD5110::testdrawchar(uint8_t type) {
  displays->clearDisplay();
  displays->setTextSize(1);
  displays->setTextColor(BLACK);
  displays->setCursor(0,0);
  int low1 = 168*type;
  int hight1= 168+168*type;
 /* if (type == 1) {
      low1 = 169;
      hight1 = 169 + 168;
  }
  if (type == 2) {
      low1 = 169 + 168;
      hight1 = 169 + 168  + 168;
  }//*/
  for (uint16_t i=low1; i < hight1; i++) {
    if (i == '\n') continue;
	displays->write(i);
    //if ((i > 0) && (i % 14 == 0))
      //displays->println();
  }
  displays->display();
}

void LCD5110::testdrawcircle(void) {
  for (int16_t i=0; i<displays->height(); i+=2) {
    displays->drawCircle(displays->width()/2, displays->height()/2, i, BLACK);
    displays->display();
  }
}

void LCD5110::testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<displays->height()/2; i+=3) {
    // alternate colors
    displays->fillRect(i, i, displays->width()-i*2, displays->height()-i*2, color%2);
    displays->display();
    color++;
  }
}

void LCD5110::testdrawtriangle(void) {
  for (int16_t i=0; i<min(displays->width(),displays->height())/2; i+=5) {
    displays->drawTriangle(displays->width()/2, displays->height()/2-i,
                     displays->width()/2-i, displays->height()/2+i,
                     displays->width()/2+i, displays->height()/2+i, BLACK);
    displays->display();
  }
}

void LCD5110::testfilltriangle(void) {
  uint8_t color = BLACK;
  for (int16_t i=min(displays->width(),displays->height())/2; i>0; i-=5) {
    displays->fillTriangle(displays->width()/2, displays->height()/2-i,
                     displays->width()/2-i, displays->height()/2+i,
                     displays->width()/2+i, displays->height()/2+i, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    displays->display();
  }
}

void LCD5110::testdrawroundrect(void) {
  for (int16_t i=0; i<displays->height()/2-2; i+=2) {
    displays->drawRoundRect(i, i, displays->width()-2*i, displays->height()-2*i, displays->height()/4, BLACK);
    displays->display();
  }
}

void LCD5110::testfillroundrect(void) {
  uint8_t color = BLACK;
  for (int16_t i=0; i<displays->height()/2-2; i+=2) {
    displays->fillRoundRect(i, i, displays->width()-2*i, displays->height()-2*i, displays->height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    displays->display();
  }
}

void LCD5110::testdrawrect(void) {
  for (int16_t i=0; i<displays->height()/2; i+=2) {
    displays->drawRect(i, i, displays->width()-2*i, displays->height()-2*i, BLACK);
    displays->display();
  }
}

void LCD5110::testdrawline(int step) {
   switch (step) {
		case 1:
			  displays->clearDisplay();
              for (int16_t i=0; i<displays->width(); i+=4) {
				displays->drawLine(0, 0, i, displays->height()-1, BLACK);
				displays->display();
			  }
			  for (int16_t i=0; i<displays->height(); i+=4) {
				displays->drawLine(0, 0, displays->width()-1, i, BLACK);
				displays->display();
			  }
			  break;
		 case 2:
			  displays->clearDisplay();
              for (int16_t i=0; i<displays->width(); i+=4) {
				displays->drawLine(0, displays->height()-1, i, 0, BLACK);
				displays->display();
			  }
			  for (int8_t i=displays->height()-1; i>=0; i-=4) {
				displays->drawLine(0, displays->height()-1, displays->width()-1, i, BLACK);
				displays->display();
			  }
			  break;
		  case 3:
				 displays->clearDisplay();
                 for (int16_t i=displays->width()-1; i>=0; i-=4) {
					displays->drawLine(displays->width()-1, displays->height()-1, i, 0, BLACK);
					displays->display();
				  }
				  for (int16_t i=displays->height()-1; i>=0; i-=4) {
					displays->drawLine(displays->width()-1, displays->height()-1, 0, i, BLACK);
					displays->display();
				  }
			   break;
		  case 4:
		  		displays->clearDisplay();
                for (int16_t i=0; i<displays->height(); i+=4) {
					displays->drawLine(displays->width()-1, 0, 0, i, BLACK);
					displays->display();
				  }
				  for (int16_t i=0; i<displays->width(); i+=4) {
					displays->drawLine(displays->width()-1, 0, i, displays->height()-1, BLACK);
					displays->display();
				  }
			   break;
   default:

	   		break;
   }
}
void LCD5110::presentation_draw()
{
  displays->drawPixel(10, 10, BLACK);
  displays->display();
  delay(2000);
  displays->clearDisplay();

  // draw many lines
  testdrawline(1);
  displays->display();
  delay(2000);
  displays->clearDisplay();

  // draw rectangles
  testdrawrect();
  displays->display();
  delay(2000);
  displays->clearDisplay();

  // draw multiple rectangles
  testfillrect();
  displays->display();
  delay(2000);
  displays->clearDisplay();

  // draw mulitple circles
  testdrawcircle();
  displays->display();
  delay(2000);
  displays->clearDisplay();

  // draw a circle, 10 pixel radius
  displays->fillCircle(displays->width()/2, displays->height()/2, 10, BLACK);
  displays->display();
  delay(2000);
  displays->clearDisplay();

  testdrawroundrect();
  delay(2000);
  displays->clearDisplay();

  testfillroundrect();
  delay(2000);
  displays->clearDisplay();

  testdrawtriangle();
  delay(2000);
  displays->clearDisplay();

  testfilltriangle();
  delay(2000);
  displays->clearDisplay();

  // draw the first ~12 characters in the font
  testdrawchar(0);
  displays->display();
  delay(2000);
  displays->clearDisplay();

  // text displays tests
  /*displays->setTextSize(1);
  displays->setTextColor(BLACK);
  displays->setCursor(0,0);
  displays->println("Hello, world!");
  displays->setTextColor(WHITE, BLACK); // 'inverted' text
  displays->println(3.141592);
  displays->setTextSize(2);
  displays->setTextColor(BLACK);
  displays->print("0x"); displays->println(0xDEADBEEF, HEX);
  displays->display();
  delay(2000);

  // miniature bitmap displays
  displays->clearDisplay();
  displays->drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  displays->display();      */

  // invert the displays
 /* displays->invertdisplays(true);
  delay(1000);
  displays->invertdisplays(false);
  delay(1000);*/




}

//---------------------------------------------------------------------------
//#endif


// #ifndef LCD_5110H
//#define LCD_5110H
