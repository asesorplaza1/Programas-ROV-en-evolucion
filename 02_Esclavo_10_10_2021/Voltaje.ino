
void loop_V5() {// Bloque de trabajo de medición de voltaje de la batería 5V

  float voltaje =  (float)25 * analogRead(A6) / 1023;
  Serial.print (F(" \n Entrada 5V = "));
  Serial.print(voltaje);
  Serial.print (F("  V"));

  if (voltaje > 5)
  {
    // Si el voltaje final es menor que 5 Voltios, enciende el LED de advertencia
    digitalWrite(led1, HIGH);
    // Escribe el texto
    Serial.print (F(" \n VOLTAJE BAJO !"));
  }
  txdata.V5 = voltaje;
}

void loop_V12() {// Bloque de trabajo de medición de voltaje de la batería 12V

  float voltaje1 =  (float)25 * analogRead(A7) / 1023;
  Serial.print (F(" \n Entrada 12V = "));
  Serial.print(voltaje1);
  Serial.print (F("  V"));

  if (voltaje1 > 12)
  {
    // Si el voltaje final es menor que 12 Voltios, enciende el LED de advertencia
    digitalWrite(led2, HIGH);
    // Escribe el texto
    Serial.print (F(" \n VOLTAJE BAJO !"));
  }
  txdata.V12 = voltaje1;
}
