
void loop_ACS712_5V()  // Bloque de trabajo del Amperimetro de 5V
{

  float average = 0;
  for (int i = 0; i < 1000; i++) {
    average = average + (.044 * analogRead(A0) - 3.78) / 1000;
  }
  Serial.print (F("\n Amperios Circuito 5V = "));
  Serial.println(average);

}

void loop_ACS712_12V()  // Bloque de trabajo del Amperimetro de 5V
{

  float average1 = 0;
  for (int i = 0; i < 1000; i++) {
    average1 = average1 + (.044 * analogRead(A1) - 3.78) / 1000;
  }
  Serial.print (F("\n Amperios Circuito 12V = "));
  Serial.println(average1);

}
