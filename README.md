# Laboratorio di Segnali e Misure

This project aims to study the basics of LoRa and LoRaWAN technology using an Arduino Uno and a bunch of other sensors. The code has been written in Wiring using the Arduino environment and basic libs like LMIC and TinyGPSPlus. Everything is better explained down here.

## Table of Contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Code](#code)
* [Authors](#authors)

## General Info

TBD

## Technologies

The prototype is made starting from an Arduino Uno and uses the following modules:
* **BME280**: used to record outside temperature, humidity and pressure.
* **NEO-M8M** GPS module: used to track the system position.
* **MQ-135** Alcohol and Air Quality sensor: used to record mainly the amount of CO2in the air.
* **RFM-95** / **SX-1278** LoRa module: used to perform the communication between the end-device (the prototype) and the TTN.

## Code

The code is written using the following custom libraries:
* [MCCI LoRaWAN LMIC library](https://github.com/mcci-catena/arduino-lmic): for the code has been taken inspiration from the **ttn-otaa** example.
* [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus): used to read GPS latitude and longitude from the NEO GPS module.
* [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library): used to read temperature, humidity, pressure and altitude from the BME280 sensor.
* [MQSensorLib](https://github.com/miguel5612/MQSensorsLib): used to read CO2 concentration in PPM in the air.

## Auhtors

* **Leonardo Beltrame.**
* **Francesco Rossetto.**
* **Edoardo Scarpel.**
