#include <avr/io.h>
#include <util/delay.h>

// Host pulls down the line to signal the start of a transmission
#define H_START_SEQ_LOW_MS (1000U)
// Wait time until the sensor pulls down the line as a response to the start signal
// this is given as 20 - 40ms, we choose 30ms here
#define S_RESP_HIGH_MS (30U)
// Sensor pulls down the line at the start of each transmission
#define S_RESP_LOW_MS (80U)
// Sensor pulls down the line at the start of each transmitted bit
#define S_START_BIT_LOW_MS (50U)
// Line stays high for 26 - 28ms to indicate a 0 coming from the sensor
#define S_BIT_0_MS (27U)
// Line stays high for 70ms to indicate a 1 coming from the sensor
#define S_BIT_1_MS (70U)

// Define the pin used to communicate with the sensor
#define DHT_PIN (8u)

// Enum for data line state
typedef enum {
  lineLow_e,
  lineHigh_e
} lineLevel_t;

uint8_t dht_init();
uint8_t dht_transmit(float *humi, float *temp);



void pullLow(uint16_t uSec);
uint16_t measureTime(lineLevel_t level);
