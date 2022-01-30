# Laboratorio di Segnali e Misure

This project aims to study the basics of LoRa and LoRaWAN technology using an Arduino Uno and a bunch of other sensors. The code has been written in Wiring using the Arduino environment and basic libs like LMIC and TinyGPSPlus. Everything is better explained down here.

## Table of Contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Code](#code)

## General Info

TBD

## Technologies

The prototype is made starting from an Arduino Uno and uses the following modules:
* **BME280**: used to record outside temperature, humidity and pressure.
* **NEO-M8M** GPS module: used to track the system position.
* **MQ-135** Alcohol and Air Quality sensor: used to record mainly the acmount of CO2in the air.
* **RFM-95** / **SX-1278** LoRa module: used to perform the communication between the end-device (the prototype) and the TTN.
