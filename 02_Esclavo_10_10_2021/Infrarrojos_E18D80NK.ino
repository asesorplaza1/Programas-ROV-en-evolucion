
void loop_SensorE18D80NK() {// Bloque de trabajo del sensor infrarrojo

  int E18D80NK = digitalRead(pinSensorE18D80NK); // leer el Sensor

  if (E18D80NK > 0) {
    Serial.println (F(" \n Todo despejado"));
    digitalWrite(led5, LOW); // encender el LED de peligro
  }
  else {
    Serial.println (F(" \n Peligro Objeto detectado"));
    digitalWrite(led5, HIGH); // Apagar el LED de peligro
  }
  txdata.E18D80NK = E18D80NK;
}
