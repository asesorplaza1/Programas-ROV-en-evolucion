
void loop_CamServo() {// Bloque de trabajo del Servo de Inmersión

  if (rxdata.PSB_R1state) // Si presionamos el botón R1
  {
    CamPitch = !CamPitch + 1;
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
    Serial.print (F(" \n Subiendo ROV a superficie "));
  }

  if (rxdata.PSB_R2state) // Si presionamos el botón R2
  {
    CamPitch = !CamPitch - 1;
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
    Serial.print (F("\n Inmersion ROV a profundidad "));
  }

  CamPitch = constrain( CamPitch, 30, 149);
  CamServo.write(CamPitch);
}
