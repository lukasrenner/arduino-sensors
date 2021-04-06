#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"
#include "dht.h"


int main (){

  char teststr[50];
  int testint = 99;
  char str1[50] = "PullLow() done.";

  //init lcd and turn on
  lcd_init(LCD_DISP_ON);

  // init snsor
  dht_init();
  
  lcd_puts("Dht test");  // put string from RAM to display (TEXTMODE) or buffer (GRAPHICMODE)
  lcd_gotoxy(0,2);          // set cursor to first column at line 3

  lcd_puts(str1);
  pullLow(50u);

  _delay_us(20u);

  testint = measureTime(lineLow_e);
  
  itoa(testint, teststr, 10);
  // lcd_puts(teststr);
  
  
  for(;;){
  
  }
  return 0;
}
