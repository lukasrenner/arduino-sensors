#include "dht.h"
// todo: remove
#include <avr/io.h>

#ifndef DHT_PIN
#error No pin defined! Define DHT_PIN as 0u .. 13u.
#endif

#if (DHT_PIN > 7u)
#define DHT_PORT_DIR (DDRB)
#define DHT_PORT_LVL (PORTB)
#else
#define DHT_PORT_DIR (DDRC)
#define DHT_PORT_LVL (PORTC)
#endif

#include "lcd.h"

static inline void setPinIn();
static inline void setPinOut();
void pullLow(uint16_t uSec);
uint16_t measureTime(lineLevel_t level);

// Bitmask used to change/read the state of the pin
uint8_t pinMask;
uint16_t tStart;
uint16_t tStop;


// todo: remove
int debugInt = 99;
char debugStr[50];

uint8_t dht_init()
{
  uint8_t res = 1u;

  tStart = 0u;
  tStop = 0u;

  // Translate Pin Number to port pin
  if(DHT_PIN > 7u)
    {
      pinMask = (1u << (DHT_PIN - 8));
    }
  else
    {
      pinMask = (1u << DHT_PIN);
    }
  
  // Set pin to input mode
  setPinIn();

  // Enable noise canceller of input capture unit
  TCCR1B |= (1<<ICNC1);

  // Enable timer - no prescaler
  TCCR1B |= (1<<CS10);

    
  return res;
}

uint8_t dht_transmit(float *humi, float *temp)
{
  uint8_t res = 1u;

  // pull data line low for at least 1ms to start transmission
  pullLow(1000u);
  
  return res;
}


static inline void setPinIn()
{
  DHT_PORT_DIR &= ~pinMask;
  DHT_PORT_LVL &= ~pinMask;
  return;
}

static inline void setPinOut()
{
  DHT_PORT_DIR |= pinMask;
  DHT_PORT_LVL &= ~pinMask;
  return;
}

void pullLow(uint16_t timeUSec)
{
  uint8_t n = timeUSec;
  
  setPinOut();
  while(0 < n)
    {
      _delay_us(1u);
      n--;
    }
  setPinIn();

  // Clear edge detection bit in flag register
  TIFR1 |= (1<<ICF1);
  
  return;
}

uint16_t measureTime(lineLevel_t level)
{
  uint16_t timeStart, timeStop, timeDiff;
  
  if(level == lineLow_e)
    {
      // Set capure unit of timer1 to detect a falling edge
      TCCR1B &= ~(1<<ICES1);
    }
  else
    {
      // Set capure unit of timer1 to detect a rising edge
      TCCR1B |= (1<<ICES1);
    }
 
  // Wait for first edge
  while( !(TIFR1 & (1<<ICF1)) );


  // Save timer value
  timeStart = ICR1;

        // todo: remove
  utoa(timeStart, debugStr, 10);
  lcd_gotoxy(0,4);
lcd_puts(debugStr);

  // Set capure unit of timer1 to detect a falling edgeWait for the opposite edge
  TCCR1B ^= (1<<ICES1);

  // Clear edge detection bit in flag register
  TIFR1 |= (1<<ICF1);
  
  // Wait for second edge
  while( !(TIFR1 & (1<<ICF1)) );

  // Save timer value
  timeStop = ICR1;

  // Check for overflow of the timer and calculate time difference
  if(timeStop < timeStart)
    {
      timeDiff = timeStart + (0xFFFFu - timeStop);
    }
  else
    {
      timeDiff = timeStop - timeStart;
    }
  
  return timeDiff;
}
