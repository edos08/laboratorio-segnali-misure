
# Laboratorio di Segnali e Misure

This project aims to design a basic transmission system to send some environmental data like temperature, humidity, air pressure, air quality and geo-position, and read them from a web application. For the transmission has been used the LoRa technology and LoRaWAN protocol, in particular by relying on a public network such as TTN. The code has been written in Wiring using the Arduino environment and basic libs like LMIC and TinyGPSPlus.

## Table of Contents
* [Technologies](#technologies)
* [General info](#general-info)
* [Code](#code)
* [Authors](#authors)

## Technologies

The prototype is made starting from a DOIT ESP32 DEVKIT V1 and uses the following modules:
* **BME280**: used to record outside temperature, humidity and pressure.
* **NEO-M8M** (GPS module): used to track the system position.
* **MQ-135**: used mainly to record the Air Quality of the surrounding environment.
* **RFM-95** / **SX-1278** (LoRa module): used to perform the communication between the end-device (the prototype) and the TTN.

## General Info

The project followed three main steps to build the prototype and write the code:
1. Tools and technologies learning
2. Hardware and code assembling
3. Final testing and code improvement

### Tools and technologies learning

The first main step to follow was to understand the technologies we were using. To do that we started analyzing and studying, with the help of Google, every single module, starting from the BME280, MQ-135, GPS module, and finally the LoRa module. The BME280 was relatively easy to make it work since the Adafruit provides a lot of documentation and a really well built library, and the module itself uses a simple I2C connection. A little bit more difficult was working with the MQ-135 sensor since it provides only an analog output as a result, and the online documentation wasn't so accurate, so it was necessary to map in some way those results, to make them human-readable. Also, the GPS module was a little bit tricky: we faced connection problems, meaning the module was unable to detect the GPS satellites, under certain circumstances, due to a not powerful antenna. So we changed the antenna and everything worked fine. Lastly, we tried to send a simple "Hello, World!" over the TTN, using a LoRa module. It wasn't easy since we encountered some problems, but after a few attempts, we made it.

### Hardware and code assembling

After we understand how all the hardware components work, we then assembled them all and we started writing the final code:

- BME280: the sensor uses an I2C connection to work: we studied that type of connection during the course. So we've connected the sensor to SDA pin for data transfer, SCL pin to carry the clock signal, VCC and GND pins for the power supply. For the code we've used the official Adafruit library and we called the necessary methods, to record the sensor data, in the `get_BME280_data()` function.
- GPS Module: the sensor uses a serial connection to communicate with the board, so the pins choice is arbitrary. One pin is used as the transmitter (TX) and the other as the receiver (RX). The GPS module triangulates the geo-position after listening to satellites and transmits the resulting data through the TX pin, encoded as NMEA sentences. In the code we've used the TinyGPS++ library to decode those sentences and extract latitude and longitude. All of this is done in the `get_GPS_data()` function.
- MQ-135: this sensor works using an internal resistance, whose value changes according to the presence of a specific component in the air, in our case CO2. Then the sensor provides a value between 0V and 5V through the analog pin of the module. The sensor needs to be connected to an analog pin as there is a need to convert the analog value to a digital value using an ADC. The code relative to this sensor is very simple as we perform a simple `analogRead()` to read the value. We tried with different libraries to convert the value provided by the sensor into a value that describes the CO2 concentration in the air (PPM), but this type of work was too challenging so we opted for a simple mapping that describes three simple scenarios as "Good", "Bad" and "Dangerous" air quality. This is permofed in the `get_MQ135_data()` function.
- 

## Code

The code is written using the following custom libraries:
* [MCCI LoRaWAN LMIC library](https://github.com/mcci-catena/arduino-lmic) [v4.1.0]: for the code has been taken inspiration from the **ttn-otaa** example.
* [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) [v1.0.3]: used to read GPS latitude and longitude from the NEO GPS module.
* [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library) [v1.1.0]: used to read temperature, humidity, pressure and altitude from the BME280 sensor.

## Authors

* **Leonardo Beltrame.**
* **Francesco Rossetto.**
* **Edoardo Scarpel.**
