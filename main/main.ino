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
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

/*-----CONSTANTS-----*/

#ifdef COMPILE_REGRESSION_TEST
# define FILLMEIN 0
#else
# warning "You must replace the values marked FILLMEIN with real values from the TTN control panel!"
# define FILLMEIN (#dont edit this, edit the lines that use FILLMEIN)
#endif

static const u1_t PROGMEM APPEUI[8]={ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u1_t PROGMEM DEVEUI[8]={ 0xF8, 0xC4, 0x04, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };
static const u1_t PROGMEM APPKEY[16] = { 0x01, 0xF7, 0x40, 0x67, 0x62, 0x3A, 0xA6, 0xB7, 0xAB, 0xB1, 0xB9, 0x04, 0xEC, 0x67, 0xD3, 0x7D };

// Schedule TX every this many seconds (might become longer due to duty cycle limitations).
const unsigned TX_INTERVAL = 60;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 25,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 33,
    .dio = {34, 26, 27},
};

#define SEALEVELPRESSURE_HPA (1013.25)
#define MQ135_PIN 14

/*-----VARIABLES-----*/

static uint8_t sensorData[51];
static osjob_t sendjob;

static const int GPSRXPin = 35, GPSTXPin = 32; // TO BE DEFINED!!!
static const uint32_t GPSBaud = 9600;

Adafruit_BME280 bme;
unsigned long delayTime;

TinyGPSPlus gps;
SoftwareSerial ss(GPSRXPin, GPSTXPin);

float temperature = 0;
float humidity = 0;
float pressure = 0;
float altitude = 0;
float latitude = 0;
float longitude = 0;
String air_quality = "null";

unsigned long dataPreviousMillis = 0;
unsigned long dataTimeInterval = 60000;     // 10 mins
unsigned long gpsListenTime = 5000;         // 5 sec
unsigned long dataCollectionTime = 7000;    // 7 sec
unsigned long retryTime = 30000;            // 30 sec

/*------OTHERS------*/


void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting"));
  
  initialData();

  setupGPS();
  setupBME280();
  setupMQ135();
  
  setupLoRaTTN();
}

void loop() {
  os_runloop_once();
  if ((millis() - dataPreviousMillis) > dataTimeInterval) {
    if (!os_queryTimeCriticalJobs(ms2osticks(dataCollectionTime))) {
      Serial.println("\nRetrieving data");
      dataPreviousMillis = millis();
      while ((millis() - dataPreviousMillis) < gpsListenTime) {
        get_GPS_data(millis() + 500);
      }
      Serial.println("Latitude: " + String(latitude, 4));
      Serial.println("Longitude: " + String(longitude, 4));
      get_BME280_data();
      get_MQ135_data();
      buildData();
    } else { //Retry later
      dataPreviousMillis += retryTime;
    }
  }
}

void buildData() {
  String data = "||" + String(temperature, 2) + "|" + String(humidity, 0) + "|" + String(pressure, 0) + "|" + String(altitude, 0) + "|" + String(latitude, 4) + "|" + String(longitude, 4) + "|" + air_quality + "||";
  Serial.println("Payload data: {" + String(data) + "}");
  Serial.println("Payload length: " + String(data.length()) + " byte");

  if (data.length() < 51) {
    int str_len = data.length() + 1;
    char char_array[str_len];
    data.toCharArray(char_array, str_len);

    for (int i=0; i<51; i++) {
      if (i<str_len)
        sensorData[i] = uint8_t(char_array[i]);
      else
        sensorData[i] = uint8_t(' ');
    }
  } else {
    Serial.println("Can't create payload: data too long.");
  }
  Serial.println();
}

void initialData() {
  String data = "Device started normally.";
  int str_len = data.length() + 1;
  char char_array[str_len];
  data.toCharArray(char_array, str_len);

  for (int i=0; i<51; i++) {
    if (i<str_len)
      sensorData[i] = uint8_t(char_array[i]);
    else
      sensorData[i] = uint8_t(' ');
  }
}
