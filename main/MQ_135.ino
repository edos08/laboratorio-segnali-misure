void setupMQ135() {
  pinMode(MQ135_PIN, INPUT);
}

void get_MQ135_data() {
  float mqValue = analogRead(MQ135_PIN);
  float air_quality_percentage = (mqValue/1023.0)*100.0;
  if (air_quality_percentage > 25) {
    air_quality = "Dangerous";
  } else if (air_quality_percentage > 6) {
    air_quality = "Bad";
  } else {
    air_quality = "Good";
  }

  Serial.println("Air Quality: " + air_quality);
}
