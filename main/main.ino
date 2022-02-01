
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
static const u1_t PROGMEM DEVEUI[8]={ 0x02, 0xC1, 0x04, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };
static const u1_t PROGMEM APPKEY[16] = { 0x36, 0x4A, 0x20, 0x23, 0x06, 0xFA, 0x23, 0x89, 0x69, 0xBB, 0xD8, 0xCC, 0xE8, 0x08, 0x0D, 0xB1 };

// Schedule TX every this many seconds (might become longer due to duty cycle limitations).
const unsigned TX_INTERVAL = 60;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 26,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 16,
    .dio = {17, 21, 22},
};

/*-----VARIABLES-----*/

static uint8_t mydata[] = "";
static osjob_t sendjob;

unsigned long temperature = 0;
unsigned long humidity = 0;
unsigned long pressure = 0;
unsigned long longitude = 0;
unsigned long latitude = 0;
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
