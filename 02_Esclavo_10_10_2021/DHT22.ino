
void loop_DHT22() {// Bloque de trabajo de los sensores DHT22

  {

    if (millis() - prevMillis > 2000)
    {
      humedad = dht.readHumidity();
      temperatura = dht.readTemperature();
      prevMillis = millis();

      humedad = dht1.readHumidity();
      temperatura1 = dht1.readTemperature();
      prevMillis = millis();

      humedad2 = dht2.readHumidity();
      temperatura2 = dht2.readTemperature();
      prevMillis = millis();
    }

    // Comprueba si hay fallo en todas las lecturas y sale rápido y prueba otra vez
    if (isnan(humedad) || isnan(temperatura)) {
      Serial.print (F(" \n Fallo de lectura desde el sensor DHT del Casco!"));
      //      return;
    }
    else if (isnan(humedad1) || isnan(temperatura1))
    {
      Serial.print (F(" \n Fallo de lectura desde el sensor DHT del motor DR!"));
      //      return;
    }
    else if (isnan(humedad2) || isnan(temperatura2))
    {
      Serial.print (F(" \n Fallo de lectura desde el sensor DHT del motor IZ!"));
      //      return;
    }
    else if (temperatura > 40 || temperatura1 > 40 || temperatura2 > 40)
    {
      // Si la temperatura de cualquiera de los sensores DHT22 es demasiado alta (más de 40 grados C)
      // Enciende el LED de advertencia
      digitalWrite(led4, HIGH);
      // Enciende la bomba de refrigeración
      digitalWrite(Refrigeracion, HIGH);
      // Escribe el texto
      Serial.print (F(" \n TEMPERATURA ELEVADA !"));
    }

    txdata.temperatura = temperatura;   // Envía al Maestro la temperatura leída en el casco
    txdata.humedad = humedad;   // Envía al Maestro la humedad leída en el casco
    txdata.temperatura1 = temperatura1; // Envía al Maestro la temperatura leída en el motor derecho
    txdata.humedad1 = humedad1; // Envía al Maestro la humedad leída en el motor derecho
    txdata.temperatura2 = temperatura2; // Envía al Maestro la temperatura leída en el motor izquierdo
    txdata.humedad2 = humedad2; // Envía al Maestro la humedad leída en el motor izquierdo
    auxMillis = millis();

    Serial.print (F(" \n Temperatura en el casco = "));
    Serial.print (temperatura);
    Serial.print (F(" *C "));
    Serial.print (F(" \n Temperatura en el motor DR = "));
    Serial.print (temperatura1);
    Serial.print (F(" *C1 "));
    Serial.print (F(" \n Temperatura en el motor IZ = "));
    Serial.print (temperatura2);
    Serial.print (F(" *C2 "));
    Serial.print (F(" \n Humedad en el Casco = "));
    Serial.print (humedad);
    Serial.print (F(" %\t"));
    Serial.print (F(" \n Humedad en el motor DR = "));
    Serial.print (humedad1);
    Serial.print (F(" %\t"));
    Serial.print (F(" \n Humedad en el motor IZ = "));
    Serial.print (humedad2);
    Serial.print (F(" %\t"));
  }
}
