
void loop_ESC() { // Bloque de trabajo de los ESC de los motores

  upLraw = (128 - UpVal) + (128 - RollLeftVal) / 2; // esto será hasta un valor de 192
  upRraw = (128 - UpVal) - (128 - RollLeftVal) / 2; // esto será hasta un valor de 192
  HLraw = (128 - ForwardVal) + (128 - YawLeftVal); // esto será hasta un valor de 256
  HRraw = (128 - ForwardVal) - (128 - YawLeftVal); // esto será hasta un valor de 256

  // Scala los valores para que sean adecuados para los ESC y los servos
  upLraw = map(upLraw, -193, 193, 0, 179);
  upRraw = map(upRraw, -193, 198, 0, 179);
  HLraw = map(HLraw, -256, 256, 0, 179);
  HRraw = map(HRraw, -256, 256, 0, 179);

  // escribe el valor del mando en los servos

  digitalWrite(3, rxdata.upLraw); //Motor 1
  digitalWrite(4, rxdata.upRraw); //Motor 2
  digitalWrite(5, rxdata.HLraw); //Motor 3
  digitalWrite(6, rxdata.HRraw); //Motor 4

}
