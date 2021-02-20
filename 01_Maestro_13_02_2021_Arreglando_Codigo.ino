/*
  Programa Maestro que es el que está en superficie y controla los movimientos del ROV
  Por favor, lea el archivo LÉAME

  Master Program that is the one that is on the surface and controls the movements of the ROV
  Please read the README or Readme English file

*/

#include <PS2X_lib.h> // Librería PS2 de Bill Porter
#include <EasyTransfer.h> // Librería Easy Transfer de Bill Porter

PS2X ps2x;         // Crea la clase del controlador PS2

volatile boolean LEDHdlts;  // Para el control de los focos
volatile boolean LEDHdlts1; // Para el control del LED chivato del mando


EasyTransfer ETin, ETout;  //Cree los objetos de EasyTransfer para la comunicación bidireccional

const int led1 = 40;  // LED verde    esta encendido en pin Digital 40
const int led2 = 42;  // LED rojo     esta encendido en pin Digital 42
const int led3 = 44;  // LED amarillo esta encendido en pin Digital 44
const int led4 = 46;  // LED de advertencia de voltaje esta encendido en el Pin digital 46
const int led5 = 48;  // LED de advertencia de temperatura esta encendido en el pin 48
const int led6 = 50;  // LED de advertencia de peligro colisión en el pin 50

const int LowvIN = 4.6;     // esto es para mantener el valor de advertencia de voltaje de bateria bajo en el umbral de 4.6 V
const int LowvIN1 = 11.6;   // esto es para mantener el valor de advertencia de voltaje de bateria bajo en el umbral de 11.6 V

int ForwardVal = 0;             // valor leído en palo PS2 derecho arriba/abajo
int YawLeftVal = 0;             // valor leído en palo PS2 derecho derecha/izquierda
int UpVal = 0;                  // valor leído en palo PS2 izquierdo arriba/abajo
int RollLeftVal = 0;            // valor leído en palo PS2 izquierdo derecha/izquierda

unsigned long auxMillis = 0;
unsigned long intervaloEncendido = 1000;

boolean PSB_PAD_LEFTstate = false;   // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_L1state = false;         // Genera variable para guardar y mandar los datos del botón Izquierda delante arriba al Esclavo
boolean PSB_L2state = false;         // Genera variable para guardar y mandar los datos del botón Izquierda delante abajo al Esclavo
boolean PSB_L3state = false;         // Genera variable para guardar y mandar los datos del botón Palo izquierdo abajo al Esclavo
boolean PSB_R1state = false;         // Genera variable para guardar y mandar los datos del botón Derecha delante arriba al Esclavo
boolean PSB_R2state = false;         // Genera variable para guardar y mandar los datos del botón Derecha delante abajo al Esclavo
boolean PSB_R3state = false;         // Genera variable para guardar y mandar los datos del botón Palo derecho abajo al Esclavo


float ROVTMP = 0;                                  // Variable para recibir los datos de la temperatura interior del ROV
float ROVTMP1 = 0;                                 // Variable para recibir los datos de la temperatura motor derecho del ROV
float ROVTMP2 = 0;                                 // Variable para recibir los datos de la temperatura motor izquierdo del ROV
float ROVDHThumid;                                 // Variable para recibir los datos de la humedad interior del ROV
float ROVDHThumid1;                                // Variable para recibir los datos de la humedad del motor derecho del ROV
float ROVDHThumid2;                                // Variable para recibir los datos de la humedad del motor izquierda del ROV
float AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ; // Variable para recibir los datos del Giroscopio del ROV
float E18D80NK;                                    // Variable para recibir los datos del sensor E18D80NK del ROV
float sensorDS18B20;                               // Variable para recibir los datos del sensor DS18B20 del ROV
float pressure_bar;                                // Variable para recibir los datos del sensor de presión interior SKU237545 en Bares del ROV
float pressure_psi;                                // Variable para recibir los datos del sensor de presión interior SKU237545 en PSI del ROV
float pressure_bar1;                               // Variable para recibir los datos del sensor de presión exterior SKU237545 en Bares del ROV
float pressure_psi1;                               // Variable para recibir los datos del sensor de presión interior SKU237545 en PSI del ROV
float ROVDepth;                                    // Variable para recibir los datos de la profundidad a la que se encuentra el ROV
float ROVHDG;                                      // Variable para recibir los datos de la dirección del ROV en grados
float vIN;                                         // Variable para recibir los datos del Voltaje del ROV 5V
float vIN1;                                        // Variable para recibir los datos del Voltaje del ROV 12V
float average;                                     // Variable para recibir los datos del consumo de Amperios del ROV en 5V
float average1;                                     // Variable para recibir los datos del consumo de Amperios del ROV en 12V

struct RECEIVE_DATA_STRUCTURE  // estructura de mensaje de datos recibidos de los sensores
{
  int vIN;                  // Recibe mensaje de voltaje de batería de 5V
  int vIN1;                 // Recibe mensaje de voltaje de batería de 12V
  int average;              // Manda mensaje de datos del Amperimetro de 5V
  int average1;              // Manda mensaje de datos del Amperimetro de 12V
  int t;                    // Recibe mensaje de temperatura interior del ROV
  int t1;                   // Recibe mensaje de temperatura del motor derecho
  int t2;                   // Recibe mensaje de temperatura del motor izquierdo
  int ROVDepth;             // Recibe mensaje de lectura de profundidad de ROV (m)
  int ROVHDG;               // Recibe mensaje de Dirección del ROV (grados)
  int h;                    // Recibe mensaje de humedad del interior del ROV
  int h1;                   // Recibe mensaje de humedad del motor derecho
  int h2;                   // Recibe mensaje de humedad del motor izquierdo
  int AccX;                 // Recibe mensaje de datos de inclinación del eje X
  int AccY;                 // Recibe mensaje de datos de inclinación del eje Y
  int AccZ;                 // Recibe mensaje de datos de inclinación del eje Z
  int Temp;                 // Recibe mensaje de datos de temperatura del giroscopio
  int GyroX;                // Recibe mensaje de datos de aceleración en el eje X
  int GyroY;                // Recibe mensaje de datos de aceleración en el eje Y
  int GyroZ;                // Recibe mensaje de datos de aceleración en el eje Z
  int E18D80NK;             // Recibe mensaje de lectura del sensor infrarrojo E18-D80NK
  int pinLedColision;       // Recibe mensaje de encender alarma de colisión
  int sensorDS18B20;        // Recibe mensaje de lectura del sensor de temperatura DS18B20
  int pressure_bar;         // Recibe mensaje de lectura del sensor de presión SKU237545 en Bares
  int pressure_psi;         // Recibe mensaje de lectura del sensor de presión SKU237545 en PSI
  int pressure_bar1;        // Recibe mensaje de lectura del sensor de presión SKU237545 Interno en Bares
  int pressure_psi1;        // Recibe mensaje de lectura del sensor de presión SKU237545 Interno en PSI
};

struct SEND_DATA_STRUCTURE  // estructura de mensaje de datos enviados
{
  int upLraw = 0;  //Variables para transportar los datos reales sin procesar de los ESCs
  int upRraw = 0;
  int HLraw = 0;
  int HRraw = 0;
  volatile boolean PSB_PAD_LEFTstate;   // Manda lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_L1state;         // Manda lectura del botón Izquierda delante arriba al Esclavo
  volatile boolean PSB_L2state;         // Manda lectura del botón Izquierda delante abajo al Esclavo
  volatile boolean PSB_L3state;         // Manda lectura del botón Palo izquierdo abajo al Esclavo
  volatile boolean PSB_R1state;         // Manda lectura del botón Derecha delante arriba al Esclavo
  volatile boolean PSB_R2state;         // Manda lectura del botón Derecha delante abajo al Esclavo
  volatile boolean PSB_R3state;         // Manda lectura del botón Palo derecho abajo al Esclavo
  volatile boolean LEDHdlts;            // Manda que hacer con los Focos, encendidos/apagados
  volatile boolean LEDHdlts1;
};

//dar un nombre al grupo de datos
RECEIVE_DATA_STRUCTURE rxdata;
SEND_DATA_STRUCTURE txdata;

void setup()
{

  Serial.begin(9600);      // Comienza la Comunicación en Serie para hablar con el ordenador a 9600 Baudios
  Serial1.begin(115200);    // Comienza la comunicación Serie en el puerto 1, pines 18 y 19, para hablar con el Arduino Esclavo
  Serial1.flush();         // Depura la información del Puerto Serie
  ETin.begin(details(rxdata), &Serial1);    // Comienza la recepción de datos a través de Serial, en los pines 18 y 19
  ETout.begin(details(txdata), &Serial1);   // Comienza el envío de datos a través de Serial, en los pines 18 y 19

  pinMode(led1, OUTPUT);  //se establece grnLEDpin como salida
  pinMode(led2, OUTPUT);  //se establece redLEDpin como salida
  pinMode(led3, OUTPUT);  //se establece yelLEDpin como salida
  pinMode(led4, OUTPUT);  //se establece el pin de advertencia de batería baja como salida
  pinMode(led5, OUTPUT);  //se establece el pin de sobre temperatura como salida
  pinMode(led6, OUTPUT);

  // Pines y ajustes de configuración: GamePad(clock, command, attention, data, Pressures?, Rumble?)
  ps2x.config_gamepad(22, 23, 24, 25, true, true);

  delay(1000); // Detiene el programa para dar tiempo a que se inicie el mando PS2
}

void loop()
{
  // Controlador DualShock
  ps2x.read_gamepad();

  if ( millis() - auxMillis > intervaloEncendido) {

    // Lectura de todos los botones del mando
    // Esto será verdad hasta que algún botón cambie de estado, (activado / desactivado)

    if (ps2x.Button(PSB_PAD_LEFT))                     // Lee el valor del botón Izquierda Izquierda al Esclavo
    {
      PSB_PAD_LEFTstate = (!PSB_PAD_LEFTstate);        // Lectura del estado del botón
      txdata.LEDHdlts = PSB_PAD_LEFTstate;             // Guarda que hacer con el estado de los focos, encendido / apagado
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
      Serial.print (F("\n Focos apagados"));           // Imprime la frase "Focos apagados"
    }
    else if (!txdata.LEDHdlts)
    {
      LEDHdlts = !LEDHdlts;                      // Cambia el estado del LED ON / OF
      Serial.print (F("\n Focos encendidos"));         // Imprime la frase " Focos encendidos"
    }

    if (ps2x.Button(PSB_R1))                    // Lee el valor del botón Derecha delante arriba al Esclavo
    {
      PSB_R1state = (!PSB_R1state);                    // Guarda el dato del botón en su variable
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
    }
    txdata.PSB_R1state = (PSB_R1state);                // Manda el estado del botón al Esclavo

    if (ps2x.Button(PSB_R2))                    // Lee el valor del botón Derecha delante abajo al Esclavo
    {
      PSB_R2state = (!PSB_R2state);                    // Guarda el dato del botón en su variable
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
    }
    txdata.PSB_R2state = (PSB_R2state);                // Manda el estado del botón al Esclavo

    if (ps2x.Button(PSB_R3))                           // Lee el valor del botón Palo derecho abajo al Esclavo
    {
      PSB_R3state = (!PSB_R3state);                    // Guarda el dato del botón en su variable
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
    }
    txdata.PSB_R3state = (PSB_R3state);                // Manda el estado del botón al Esclavo

    if (ps2x.Button(PSB_L1))                    // Lee el valor del botón Izquierda delante arriba al Esclavo
    {
      PSB_L1state = (!PSB_L1state);                    // Guarda el dato del botón en su variable
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
    }
    txdata.PSB_L1state = (PSB_L1state);                // Manda el estado del botón al Esclavo

    if (ps2x.Button(PSB_L2))                    // Lee el valor del botón Izquierda delante abajo al Esclavo
    {
      PSB_L2state = (!PSB_L2state);                    // Guarda el dato del botón en su variable
      LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
    }
    txdata.PSB_L2state = (PSB_L2state);                // Manda el estado del botón al Esclavo

    //lecturas analógicas del palo
    //traduce las lecturas del palo al las instrucciones del ESC
    //las lecturas de los palos del controlador PS2 son de 0 a 255
    //con el neutro en 128. Las posiciones cero son
    //a la izquierda para movimientos del eje X y arriba para los movimientos del eje Y

    ForwardVal = ps2x.Analog(PSS_RY);
    YawLeftVal = ps2x.Analog(PSS_RX);
    UpVal = ps2x.Analog(PSS_LY);
    RollLeftVal = ps2x.Analog(PSS_LX);

    //variables para transportar los datos en bruto reales para los ESCs y servos
    txdata.upLraw = (128 - UpVal) - (128 - RollLeftVal) / 2; //esto será hasta un valor de 192
    txdata.upRraw = (128 - UpVal) + (128 - RollLeftVal) / 2; //esto será hasta un valor de 192
    txdata.HLraw = -(128 - ForwardVal) + (128 - YawLeftVal); //esto será hasta un valor de 256
    txdata.HRraw = -(128 - ForwardVal) - (128 - YawLeftVal); //esto será hasta un valor de 256
    //escala los valores para que sean adecuados para los ESCs y para los Servos
    //estos valores podrán escribirse directamente en los  ESCs y en los Servos
    txdata.upLraw = map(txdata.upLraw, -193, 193, 0, 179);
    txdata.upRraw = map(txdata.upRraw, -193, 198, 0, 179);
    txdata.HLraw = map(txdata.HLraw, -256, 256, 0, 179);
    txdata.HRraw = map(txdata.HRraw, -256, 256, 0, 179);

    ETout.sendData();          // Enviar el mensaje al puerto serie para el Arduino del ROV

    for (int i = 0; i < 5; i++) { // Esta función, cambia el estado de envio a recepción cada 5 segundos

      if (ETin.receiveData())    // Recibe el mensaje al puerto serie para el Arduino del ROV
      {

        if (rxdata.vIN < LowvIN)
        {
          digitalWrite(led4, HIGH);
          //si el voltaje de la batería es demasiado bajo, enciende el LED de advertencia
        }
        else
        {
          digitalWrite(led4, LOW);
          //de lo contrario, si el voltaje está por encima del umbral de bajo voltaje definido
          //deje el LED apagado
        }

        if (rxdata.vIN1 < LowvIN1)
        {
          digitalWrite(led4, HIGH);
          //si el voltaje de la batería es demasiado bajo, enciende el LED de advertencia
        }
        else
        {
          digitalWrite(led4, LOW);
          //de lo contrario, si el voltaje está por encima del umbral de bajo voltaje definido
          //deje el LED apagado
        }
      }

      if (rxdata.average)
      {
        Serial.print (F(" \n Amperios Circuito 5 V  "));
        Serial.print(average);
        Serial.print (F("  A"));
      }

      if (rxdata.average1)
      {
        Serial.print (F(" \n Amperios Circuito 12 V  "));
        Serial.print (average1);
        Serial.print (F("  A"));
      }


      ROVTMP = (rxdata.t);    // Recibe los datos del Esclavo
      ROVTMP1 = (rxdata.t1);  // Recibe los datos del Esclavo
      ROVTMP2 = (rxdata.t2);  // Recibe los datos del Esclavo
      //convierte el valor de datos 0-1024 en temperatura

      if (ROVTMP > 40 || ROVTMP1 > 40 || ROVTMP2 > 40)
      {
        // Si la temperatura de cualquiera de los sensores DHT22 es demasiado alta (más de 50 grados C)
        // enciende el LED de advertencia
        digitalWrite(led5, HIGH);
        Serial.print (F(" \n TEMPERATURA ELEVADA !"));
      }
      else
      {
        digitalWrite(led5, LOW);
        Serial.print (F(" \n Temperatura Normal"));
        // De lo contrario, si la temperatura interior está en un nivel aceptable
        // Deje el LED apagado y deje el relé de la bomba de refrigeración apagado
      }

      ROVDHThumid = (rxdata.h);    // Recibe los datos del Esclavo
      ROVDHThumid1 = (rxdata.h1);  // Recibe los datos del Esclavo
      ROVDHThumid2 = (rxdata.h2);  // Recibe los datos del Esclavo

      if (rxdata.E18D80NK > 0)    // Si la entrada del E18D80NK es baja, no hay ningún objeto
      {
        digitalWrite(led6, LOW);    // Apague el LED si no se detecta objeto
        Serial.print (F(" \n Todo Despejado  !"));   // manda imprimir al Monitor Serie la frase
      }
      else                                    // por el contrario, si la entrada del E18D80NK es alta
      {
        digitalWrite(led6, HIGH);   // encienda el LED de Peligro Colisión
        Serial.print (F(" \n PELIGRO Obstaculo detectado  !")); // manda imprimir la frase
      }

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

      // #if DEBUG1 { // CUIDADO CON ESTO, des comentar y cambiar 1 si imprime en Monitor Serie, 0 cero no imprime

      // A partir de aquí repito las ordenes de lcd, cambiándolas por Serial

      Serial.print (F("\n Voltaje línea de 5 V = "));
      Serial.print (float(rxdata.vIN), 3);
      Serial.print (F("\n Voltaje línea de 12 V = "));
      Serial.print (float(rxdata.vIN1), 3);
      Serial.print (F(" \n Temperatura del casco = "));
      Serial.print (ROVTMP);
      Serial.print (F(" *C "));
      Serial.print (F(" \n Temperatura motor DR = "));
      Serial.print (ROVTMP1);
      Serial.print (F(" *C1 "));
      Serial.print (F(" \n Temperatura motor IZ = "));
      Serial.print (ROVTMP2);
      Serial.print (F(" *C2 "));
      Serial.print (F(" \n Humedad en el interior del Casco = "));
      Serial.print (ROVDHThumid);
      Serial.print (F(" %\t"));
      Serial.print (F(" \n Humedad en el motor DR = "));
      Serial.print (ROVDHThumid1);
      Serial.print (F(" %\t"));
      Serial.print (F(" \n Humedad en el motor IZ = "));
      Serial.print (ROVDHThumid2);
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
    }
    // } #endif  // descomentar cuando NO quiera imprimir los Serial.print

  }
}
