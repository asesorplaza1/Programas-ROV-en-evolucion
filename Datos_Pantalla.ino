void loop_Pantalla()
{
// #if DEBUG1 { // CUIDADO CON ESTO, des comentar y cambiar 1 si imprime en Monitor Serie, 0 cero no imprime

// A partir de aquí repito las ordenes de lcd, cambiándolas por Serial

Serial.print (F("\n Voltaje línea de 5 V = "));
Serial.print (float(rxdata.V5));
Serial.print (F("\n Voltaje línea de 12 V = "));
Serial.print (float(rxdata.V12));
Serial.print(F("\n Amperios línea 5V"));
Serial.print(rxdata.average);
Serial.print(F("\n Amperios línea 12V"));
Serial.print(rxdata.average1);
Serial.print (F(" \n Temperatura del casco = "));
Serial.print (rxdata.temperatura);
Serial.print (F(" *C "));
Serial.print (F(" \n Temperatura motor DR = "));
Serial.print (rxdata.temperatura1);
Serial.print (F(" *C1 "));
Serial.print (F(" \n Temperatura motor IZ = "));
Serial.print (rxdata.temperatura2);
Serial.print (F(" *C2 "));
Serial.print (F(" \n Humedad en el interior del Casco = "));
Serial.print (rxdata.humedad);
Serial.print (F(" %\t"));
Serial.print (F(" \n Humedad en el motor DR = "));
Serial.print (rxdata.humedad1);
Serial.print (F(" %\t"));
Serial.print (F(" \n Humedad en el motor IZ = "));
Serial.print (rxdata.humedad2);
Serial.print (F(" %\t"));
Serial.print (F(" \n Inclinación del eje X del ROV = "));
Serial.print (AccX);
Serial.print (F(" \n Inclinación del eje Y del ROV = "));
Serial.print (AccY);
Serial.print (F(" \n Inclinación del eje Z del ROV = "));
Serial.print (AccZ);
Serial.print (F(" \n Temperatura del Giro MPU6050 = "));
Serial.print (Temp / 340.00 + 36.53);
Serial.print (F(" \n Aceleración en el eje X del Giro MPU6050 = "));
Serial.print (GyroX);
Serial.print (F(" \n Aceleración en el eje Y del Giro MPU6050 = "));
Serial.print (GyroY);
Serial.print (F(" \n Aceleración en el eje Z del Giro MPU6050 = "));
Serial.print (GyroZ);
Serial.print (F(" \n Profundidad = "));
Serial.print (ROVDepth);      // muestra en el Display la profundidad del ROV en metros
Serial.print (F(" \n Direccion del ROV = "));
Serial.print (ROVHDG);  // muestra la dirección del ROV en una brújula
Serial.print (F(" \n Temperatura sensor DS18B20 = "));
Serial.print (sensorDS18B20);
Serial.print (F(" ºC"));
Serial.print (F(" \n Valor del Sensor de Presión Interno =  "));
Serial.print (F("   Presión en Bar = "));
Serial.print (pressure_bar);
Serial.print (F("    bars"));
Serial.print (F("  || Presión en PSI = "));
Serial.print (pressure_psi);
Serial.print (F("    psi"));
Serial.print (F(" \n Valor del Sensor de Presión Externo = "));
Serial.print (F("   Presión en Bar = "));
Serial.print (pressure_bar1);
Serial.print (F("    bars"));
Serial.print (F("  || Presión en PSI = "));
Serial.print (pressure_psi1);
Serial.print (F("    psi"));
Serial.print (F("\n"));

// } #endif  // descomentar cuando NO quiera imprimir los Serial.print
}
