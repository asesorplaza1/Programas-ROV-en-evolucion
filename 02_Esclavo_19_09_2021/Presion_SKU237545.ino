
void loop_SKU237545_I() { // Bloque de trabajo del sensor de presión interno

  SensorSKU237545_I = analogRead(32);
  float voltage = (SensorSKU237545_I * 5.0) / 1024.0;
  float pressure_pascal = (3.0 * ((float)voltage - 0.475)) * 1000000.0;  //calibrar aquí
  float pressure_bar = pressure_pascal / 10e5;
  float pressure_psi = pressure_bar * 14.5038;
  Serial.print (F("\n Valor del Sensor de Presión Interno =  "));
  Serial.print (SensorSKU237545_I);
  Serial.print (F("\n Presión en Bar = "));
  Serial.print (pressure_bar);
  Serial.print (F("    bars"));
  Serial.print (F("\n Presión en PSI = "));
  Serial.print (pressure_psi);
  Serial.print (F("   psi"));
  txdata.pressure_bar = pressure_bar;
  txdata.pressure_psi = pressure_psi;
}

void loop_SKU237545_E() {  // bloque de trabajo del sensor de presión externo

  SensorSKU237545_E = analogRead(32);
  float voltage1 = (SensorSKU237545_E * 5.0) / 1024.0;
  float pressure_pascal1 = (3.0 * ((float)voltage1 - 0.475)) * 1000000.0;  //calibrar aquí
  float pressure_bar1 = pressure_pascal1 / 10e5;
  float pressure_psi1 = pressure_bar1 * 14.5038;
  Serial.print (F("\n Valor del Sensor de Presión Externo = "));
  Serial.print (SensorSKU237545_E);
  Serial.print (F("\n Presión en Bar = "));
  Serial.print (pressure_bar1);
  Serial.print (F("    bars"));
  Serial.print (F("\n Presión en PSI = "));
  Serial.print (pressure_psi1);
  Serial.print (F("   psi"));
  Serial.print (F("\n Profundidad = "));
  txdata.pressure_bar1 = pressure_bar1;
  txdata.pressure_psi1 = pressure_psi1;

  // Serial.print(rxdata.ROVDepth);
  // Muestra en el Display la profundidad del ROV en metros
}
