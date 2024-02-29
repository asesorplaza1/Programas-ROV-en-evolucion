
void loop_Mando_PS2()
{

  if ( millis() - auxMillis > intervaloEncendido)
  {
    ps2x.read_gamepad(); // Lee le controlador

    // Lectura de todos los botones del mando
    // Esto será verdad hasta que algún botón cambie de estado, (activado / desactivado)

    if (ps2x.Button(PSB_START))   // Sera verdadero cuando se presione el botón
    {
      Serial.println(F("\n Botón Start esta siendo presionado"));
    }

    if (ps2x.Button(PSB_SELECT))
    {
      Serial.println(F("\n Botón Select esta siendo presionado"));
    }

    if (ps2x.ButtonPressed(PSB_PAD_UP))  // Sera verdad cuando se presione el botón, 1 vez ON / 1 vez OF
    {
      PSB_PAD_UPstate = (!PSB_PAD_UPstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n Botón izquierda arriba presionado:"));
    }

    if (ps2x.ButtonPressed(PSB_PAD_DOWN))
    {
      PSB_PAD_DOWNstate = (!PSB_PAD_DOWNstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n Botón izquierda abajo presinado:"));
    }

    if (ps2x.ButtonPressed(PSB_PAD_RIGHT))
    {
      PSB_PAD_RIGHTstate = (!PSB_PAD_RIGHTstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n Botón izquierda derecha presionado:"));
    }

    if (ps2x.Button(PSB_PAD_LEFT))                     // Lee el valor del botón Izquierda Izquierda al Esclavo
    {
      PSB_PAD_LEFTstate = (!PSB_PAD_LEFTstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
      Serial.println(F("\n Botón izquierda izquierda presionado"));
    }
    else if (!txdata.LEDHdlts1)
    {
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
      Serial.print (F("\n Focos encendidos"));         // Imprime la frase " Focos encendidos"
    }

    else
    {
      Serial.print (F("\n Focos apagados"));           // Imprime la frase "Focos apagados"
    }

    if (ps2x.ButtonPressed(PSB_GREEN))
    {
      PSB_GREENstate = (!PSB_GREENstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n Triangulo presionado"));
    }

    if (ps2x.ButtonPressed(PSB_RED))
    {
      PSB_REDstate = (!PSB_REDstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n Circulo presionado"));
    }

    if (ps2x.ButtonPressed(PSB_PINK))
    {
      PSB_PINKstate = (!PSB_PINKstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n Cuadrado presinado"));
    }

    if (ps2x.ButtonPressed(PSB_BLUE))
    {
      PSB_BLUEstate = (!PSB_BLUEstate);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n Cruz presionado"));
    }

    if (ps2x.Button(PSB_L1))                    // Lee el valor del botón Izquierda delante arriba al Esclavo
    {
      PSB_L1state = (!PSB_L1state);                    // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n L1 presionado"));
    }

    if (ps2x.Button(PSB_L2))                    // Lee el valor del botón Izquierda delante abajo al Esclavo
    {
      PSB_L2state = (!PSB_L2state);                    // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n L2 presionado"));
    }

    if (ps2x.ButtonPressed(PSB_L3))
    {
      PSB_L3state = (!PSB_L3state);   // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n L3 presionado"));
    }

    if (ps2x.Button(PSB_R1))                    // Lee el valor del botón Derecha delante arriba al Esclavo
    {
      CamPitch = CamPitch + 1;
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      PSB_R1state = (!PSB_R1state);                    // Guarda el dato del botón en su variable
      Serial.println(F("\n R1 presionado"));
    }

    if (ps2x.Button(PSB_R2))                    // Lee el valor del botón Derecha delante abajo al Esclavo
    {
      CamPitch = CamPitch - 1;
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      PSB_R2state = (!PSB_R2state);                    // Guarda el dato del botón en su variable
      Serial.println(F("\n R2 presionado"));
    }

    if (ps2x.Button(PSB_R3))                           // Lee el valor del botón Palo derecho abajo al Esclavo
    {
      PSB_R3state = (!PSB_R3state);                    // Guarda el dato del botón en su variable
      LEDHdlts = !LEDHdlts; // Cambia el estado del LED chivato del mando
      Serial.println(F("\n R3 presionado"));
    }

    digitalWrite(led1, LEDHdlts); // Enciende el Led Verde

  }

}
