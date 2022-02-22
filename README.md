
# Laboratorio di Segnali e Misure

This project aims to design a basic transmission system to send some environmental data like temperature, humidity, pressure, air quality and position, and read them from a web application. For the transmission has been used the LoRa technology and LoRaWAN protocol, in particular by relying on a public network such as TTN. The code has been written in Wiring using the Arduino environment and basic libs like LMIC and TinyGPSPlus.

## Table of Contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Code](#code)
* [Authors](#authors)

## General Info

The project followed three main steps to build the prototype and write the code:
1. Tool and technologies learning
2. Full assembling and individual testing
3. Final testing and code improvement

### Tool and technologies learning

The first main step to follow was to understand the technologies we were using. To do that we started analyzing and studying, with the help of Google, every single module, starting from the BME280, MQ-135, GPS module, and finally the LoRa module. The BME280 was relatively easy to make it work since the Adafruit provides a lot of documentation and a really well built library, and the module itself uses a simple I2C connection. A little bit more difficult was working with the MQ-135 sensor since it provides only an analog output as a result, and the online documentation wasn't so accurate, so it was necessary to map in some way those results, to make them human-readable. Also, the GPS module was a little bit tricky: we faced connection problems, meaning the module was unable to detect the GPS satellites, under certain circumstances, due to a not powerful antenna. So we changed the antenna and everything worked fine. Lastly, we tried to send a simple "Hello, World!" over the TTN, using a LoRa module. It wasn't easy since we encountered some problems, but after a few attempts, we made it.

### Full assembling and individual testing

## Technologies

The prototype is made starting from a DOIT ESP32 DEVKIT V1 and uses the following modules:
* **BME280**: used to record outside temperature, humidity and pressure.
* **NEO-M8M** (GPS module): used to track the system position.
* **MQ-135**: used mainly to record the Air Quality of the surrounding environment.
* **RFM-95** / **SX-1278** (LoRa module): used to perform the communication between the end-device (the prototype) and the TTN.

## Code

The code is written using the following custom libraries:
* [MCCI LoRaWAN LMIC library](https://github.com/mcci-catena/arduino-lmic) [v4.1.0]: for the code has been taken inspiration from the **ttn-otaa** example.
* [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) [v1.0.3]: used to read GPS latitude and longitude from the NEO GPS module.
* [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library) [v1.1.0]: used to read temperature, humidity, pressure and altitude from the BME280 sensor.

## Authors

* **Leonardo Beltrame.**
* **Francesco Rossetto.**
* **Edoardo Scarpel.**
