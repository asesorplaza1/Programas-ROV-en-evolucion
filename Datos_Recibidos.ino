
void loop_Datos()
{
  ROVDepth = (rxdata.ROVDepth);             // Recibe lectura de profundidad de ROV (m)
  ROVHDG = (rxdata.ROVHDG);                 // Recibe lectura de Dirección del ROV (grados)
  AccX = (rxdata.AccX);                     // Recibe lectura de datos de inclinación del eje X
  AccY = (rxdata.AccY);                     // Recibe lectura de datos de inclinación del eje Y
  AccZ = (rxdata.AccZ);                     // Recibe lectura de datos de inclinación del eje Z
  Temp = (rxdata.Temp);                     // Recibe lectura de datos de temperatura del giroscopio
  GyroX = (rxdata.GyroX);                   // Recibe lectura de datos de aceleración en el eje X
  GyroY = (rxdata.GyroY);                   // Recibe lectura de datos de aceleración en el eje Y
  GyroZ = (rxdata.GyroZ);                   // Recibe lectura de datos de aceleración en el eje Z
//  pinLedColision = (rxdata.pinLedColision); // Recibe lectura de encender alarma de colisión
  sensorDS18B20 = (rxdata.sensorDS18B20);   // Recibe lectura de lectura del sensor de temperatura DS18B20
  pressure_bar = (rxdata.pressure_bar);     // Recibe lectura de lectura del sensor de presión SKU237545 en Bares
  pressure_psi = (rxdata.pressure_psi);     // Recibe lectura de lectura del sensor de presión SKU237545 en PSI
  pressure_bar1 = (rxdata.pressure_bar1);   // Recibe lectura de lectura del sensor de presión SKU237545 Interno en Bares
  pressure_psi1 = (rxdata.pressure_psi1);   // Recibe lectura de lectura del sensor de presión SKU237545 Interno en PSI
  E18D80NK = (rxdata.E18D80NK);             // Recibe estado del sensor de infrarrojos
}
