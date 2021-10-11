
void loop_Led()
{
  if (rxdata.V5 < LowV5)
  {
    digitalWrite(led4, HIGH);
    //si el voltaje de la batería es demasiado bajo, enciende el LED de advertencia
  }
  else
  {
    digitalWrite(led4, LOW);
    //de lo contrario, si el voltaje está por encima del umbral de bajo voltaje definido
    //deje el LED apagado
  }

  if (rxdata.V12 < LowV12)
  {
    digitalWrite(led4, HIGH);
    //si el voltaje de la batería es demasiado bajo, enciende el LED de advertencia
  }
  else
  {
    digitalWrite(led4, LOW);
    //de lo contrario, si el voltaje está por encima del umbral de bajo voltaje definido
    //deje el LED apagado
  }

  if (rxdata.average)
  {
    Serial.print (F(" \n Amperios Circuito 5 V  "));
    Serial.print(rxdata.average);
    Serial.print (F("  A"));
  }

  if (rxdata.average1)
  {
    Serial.print (F(" \n Amperios Circuito 12 V  "));
    Serial.print (rxdata.average1);
    Serial.print (F("  A"));
  }


  ROVTMP = (rxdata.temperatura);    // Recibe los datos del Esclavo
  ROVTMP1 = (rxdata.temperatura1);  // Recibe los datos del Esclavo
  ROVTMP2 = (rxdata.temperatura2);  // Recibe los datos del Esclavo
  //convierte el valor de datos 0-1024 en temperatura

  if (rxdata.temperatura > 40 || rxdata.temperatura1 > 40 || rxdata.temperatura2 > 40)
  {
    // Si la temperatura de cualquiera de los sensores DHT22 es demasiado alta (más de 50 grados C)
    // enciende el LED de advertencia
    digitalWrite(led5, HIGH);
    Serial.print (F(" \n TEMPERATURA ELEVADA !"));
  }
  else
  {
    digitalWrite(led5, LOW);
    Serial.print (F(" \n Temperatura Normal"));
    // De lo contrario, si la temperatura interior está en un nivel aceptable
    // Deje el LED apagado y deje el relé de la bomba de refrigeración apagado
  }

  ROVDHThumid = (rxdata.humedad);    // Recibe los datos del Esclavo
  ROVDHThumid1 = (rxdata.humedad1);  // Recibe los datos del Esclavo
  ROVDHThumid2 = (rxdata.humedad2);  // Recibe los datos del Esclavo

}
