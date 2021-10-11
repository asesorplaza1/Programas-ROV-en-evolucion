
void loop_MPU6050() {// Bloque de trabajo del giroscopio

  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr, 14, true);
  AccX = Wire.read() << 8 | Wire.read();
  AccY = Wire.read() << 8 | Wire.read();
  AccZ = Wire.read() << 8 | Wire.read();
  Temp = Wire.read() << 8 | Wire.read();
  GyroX = Wire.read() << 8 | Wire.read();
  GyroY = Wire.read() << 8 | Wire.read();
  GyroZ = Wire.read() << 8 | Wire.read();

  txdata.AccX = AccX;
  txdata.AccY = AccY;
  txdata.AccZ = AccZ;
  txdata.Temp = Temp;
  txdata.GyroX = GyroX;
  txdata.GyroY = GyroY;
  txdata.GyroZ = GyroZ;

  Serial.print (F(" \n Inclinación del eje X del ROV = "));
  Serial.print (AccX);
  Serial.print (F(" \n Inclinación del eje Y del ROV = "));
  Serial.print (AccY);
  Serial.print (F(" \n Inclinación del eje Z del ROV = "));
  Serial.print (AccZ);
  Serial.print (F(" \n Temperatura del Giro MPU6050 = "));
  Serial.print (Temp / 340.00 + 36.53);
  Serial.print (F(" \n Aceleración del Giro MPU6050 = "));
  Serial.print (GyroX);
  Serial.print (F(" \n Aceleración del Giro MPU6050 = "));
  Serial.print (GyroY);
  Serial.print (F(" \n Aceleración del Giro MPU6050 = "));
  Serial.print(GyroZ);

  // Serial.print(" \n Dirección del ROV = ");
  // Serial.print(rxdata.ROVHDG);  // muestra la dirección del ROV en una brújula

  Wire.endTransmission(MPU6050_addr); //
}
