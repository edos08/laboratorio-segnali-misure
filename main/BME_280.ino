void setupBME280() {
  Serial.println(F("BME280 Setup"));

  bool status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void get_BME280_data() {
  Serial.print("Temperature = ");
  temperature = bme.readTemperature();
  Serial.print(temperature);
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  pressure = bme.readPressure() / 100.0F;
  Serial.print(pressure);
  Serial.println(" hPa");
  
  Serial.print("Approx. Altitude = " );
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.print(altitude);
  Serial.println(" m");
  
  Serial.print("Humidity = ");
  humidity = bme.readHumidity();
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.println();
}
