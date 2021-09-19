
void loop_Led_Mando_PS2()
{

  if (rxdata.PSB_PAD_LEFTstate) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_PAD_UPstate) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_PAD_RIGHTstate) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_GREENstate) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
    Serial.println(F("\n Triangulo presionado"));
  }

  if (rxdata.PSB_REDstate) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
    Serial.println(F("\n Circulo presionado"));
  }

  if (rxdata.PSB_PINKstate) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
    Serial.println(F("\n Cuadrado presinado"));
  }

  if (rxdata.PSB_BLUEstate) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
    Serial.println(F("\n X presionado"));
  }

  if (rxdata.PSB_L1state) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_L2state) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_L3state) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
    Serial.println(F("\n L3 presionado"));
  }

  if (rxdata.PSB_R3state) // Si recibe datos del botón R1
  {
    LEDHdlts = !LEDHdlts;    // Cambia el estado del LED ON / OF
  }

  digitalWrite(led1, LEDHdlts); // Enciende el Led Verde

}
