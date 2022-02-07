
/*******************************************************************************
 * Laboratorio di Segnali e Misure
 * 
 * Leonardo Beltrame
 * Francesco Rossetto
 * Edoardo Scarpel
*******************************************************************************/

/*-----LIBRARIES-----*/

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

/*-----CONSTANTS-----*/

#ifdef COMPILE_REGRESSION_TEST
# define FILLMEIN 0
#else
# warning "You must replace the values marked FILLMEIN with real values from the TTN control panel!"
# define FILLMEIN (#dont edit this, edit the lines that use FILLMEIN)
#endif

static const u1_t PROGMEM APPEUI[8]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u1_t PROGMEM DEVEUI[8]={ 0xF8, 0xC4, 0x04, 0xD0, 0x7E, 0xD5, 0xB3, 0x700 };
static const u1_t PROGMEM APPKEY[16] = { 0x01, 0xF7, 0x40, 0x67, 0x62, 0x3A, 0xA6, 0xB7, 0xAB, 0xB1, 0xB9, 0x04, 0xEC, 0x67, 0xD3, 0x7D };

// Schedule TX every this many seconds (might become longer due to duty cycle limitations).
const unsigned TX_INTERVAL = 60;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 17,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 16,
    .dio = {26, 12, 32},
};

/*-----VARIABLES-----*/

static uint8_t mydata[] = "Hello, world!";
static osjob_t sendjob;

long temperature = 0;
long altitude = 0;
long longitude = 0;
long latitude = 0;
unsigned long humidity = 0;
unsigned long pressure = 0;
unsigned long air_quality = 0;

/*------OTHERS------*/


void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting"));

  setupLoRaTTN();
}

void loop() {
  runLoopLoRa();
}

void buildData() {
  get_BME280_data();
  get_GPS_data();
  get_MQ135_data();
  
//  mydata[] = "\\" +
//     String(temperature) + "\" +
//     String(humidity) + "\" +
//     String(pressure) + "\" +
//     String(longitude) + "\" +
//     String(latitude) + "\" +
//     String(air_quality) + "\\";
}
