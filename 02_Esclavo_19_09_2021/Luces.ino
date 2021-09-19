
void loop_Luces() {// Bloque de trabajo de los focos

  digitalWrite(HeadLts, rxdata.LEDHdlts1);
  // Enciende los faros en función del estado del boton
  if (rxdata.LEDHdlts1 > 0)
  {
    digitalWrite(HeadLts, LOW);
    Serial.print (F(" \n Focos apagados "));
  }
  else
  {
    (rxdata.LEDHdlts1 < 0);
    digitalWrite(HeadLts, HIGH);
    Serial.println (F(" \n Focos encendidos "));
  }
}
