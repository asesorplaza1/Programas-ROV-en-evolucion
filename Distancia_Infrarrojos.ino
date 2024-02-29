
void loop_SensorE18D80NK() // Bloque de trabajo del sensor infrarrojo
{
  if (rxdata.E18D80NK > 0)    // Si la entrada del E18D80NK es baja, no hay ningún objeto
  {
    Serial.println (F(" \n Todo Despejado  !"));   // manda imprimir al Monitor Serie la frase
    digitalWrite(led6, LOW);    // Apague el LED si no se detecta objeto
  }

  else   // por el contrario, si la entrada del E18D80NK es alta
  {
    Serial.println (F(" \n PELIGRO Obstaculo detectado  !")); // manda imprimir la frase
    digitalWrite(led6, HIGH);   // encienda el LED de Peligro Colisión
  }
}
