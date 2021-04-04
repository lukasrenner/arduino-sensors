#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"
#include "dht.h"

#define DELAY 10000



int main (){
  lcd_init(LCD_DISP_ON);    // init lcd and turn on
  
  lcd_puts("Swathi ist doof!");  // put string from RAM to display (TEXTMODE) or buffer (GRAPHICMODE)
  lcd_gotoxy(0,2);          // set cursor to first column at line 3
  
  for(;;){
    //main loop
  }
  return 0;
}
