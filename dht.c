#include "dht.h"

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
  

uint8_t dht_init()
{
  uint8_t res = 1u;
  uint8_t pinMask;

  if(DHT_PIN > 7u)
    {
      pinMask = (1u << (DHT_PIN - 8));
    }
  else
    {
      pinMask = (1u << DHT_PIN);
    }
  

  // Set pin to input mode
  DHT_PORT_DIR &= ~pinMask;
  
  // Activate pull-up
  DHT_PORT_LVL |= pinMask;
  
  return res;
}

uint8_t dht_transmit(float *humi, float *temp)
{
  uint8_t res = 1u;

  return res;
}

