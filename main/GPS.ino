void setupGPS() {
  ss.begin(GPSBaud);

  Serial.println("GPS Started.");
}

void get_GPS_data(int stopTime) {
  while (ss.available() > 0 && millis() < stopTime) {
    //Serial.write(ss.read());
    gps.encode(ss.read());
    if (gps.location.isValid()) {
      if (gps.location.isUpdated()) {
        latitude = gps.location.lat();
        Serial.print(latitude, 6);
        Serial.print(F(","));
        longitude = gps.location.lng();
        Serial.println(longitude, 6);
      }
    }
  }
}
