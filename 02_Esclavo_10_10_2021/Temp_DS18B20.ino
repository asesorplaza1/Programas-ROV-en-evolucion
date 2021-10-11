
void loop_DS18B20() {  // Bloque de trabajo del sensor de temperatura DS18B20

  sensorDS18B20.requestTemperatures();
  Serial.print (F("\n Temperatura sensor DS18B20 = "));
  Serial.print (sensorDS18B20.getTempCByIndex(0));
  Serial.print (F(" ºC"));
  txdata.sensorDS18B20 = sensorDS18B20.getTempCByIndex(0);
}
