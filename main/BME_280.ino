void setupBME280() {
  Serial.println(F("BME280 Setup"));

  bool status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void get_BME280_data() {
  temperature = bme.readTemperature();
  Serial.println("Temperature: " + String(temperature) + " °C");
  
  pressure = bme.readPressure() / 100.0F;
  Serial.println("Pressure: " + String(pressure) + " hPa");
  
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.println("Altitude: " + String(altitude) + " m");
  
  humidity = bme.readHumidity();
  Serial.println("Humidity: " + String(humidity) + "%");
}
