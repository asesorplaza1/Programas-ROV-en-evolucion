/*
  Programa Maestro que es el que está en superficie y controla los movimientos del ROV
  Por favor, lea el archivo LÉAME

  Master Program that is the one that is on the surface and controls the movements of the ROV
  Please read the README or Readme English file

*/

#include "PS2X_lib.h" // Librería PS2 de Bill Porter
#include <EasyTransfer.h> // Librería Easy Transfer de Bill Porter

EasyTransfer ETin, ETout;  //Cree los objetos de EasyTransfer para la comunicación bidireccional

PS2X ps2x;         // Crea la clase del controlador PS2

const int led1 = 30; // Creamos un LED Verde en el pin 30 chivato del mando
const int led2 = 42;  // LED rojo     esta encendido en pin Digital 42
const int led3 = 44;  // LED amarillo esta encendido en pin Digital 44
const int led4 = 46;  // LED de advertencia de voltaje esta encendido en el Pin digital 46
const int led5 = 48;  // LED de advertencia de temperatura esta encendido en el pin 48
const int led6 = 50;  // LED de advertencia de peligro colisión en el pin 50

const int LowV5 = 4.6;     // esto es para mantener el valor de advertencia de voltaje de bateria bajo en el umbral de 4.6 V
const int LowV12 = 11.6;   // esto es para mantener el valor de advertencia de voltaje de bateria bajo en el umbral de 11.6 V

volatile boolean LEDHdlts;   // Cambia el estado del LED chivato del mando
volatile boolean LEDHdlts1;  // Cambia el estado de los focos exteriores

int ForwardVal = 0;   // valor leído en palo PS2 derecho arriba/abajo
int YawLeftVal = 0;   // valor leído en palo PS2 derecho derecha/izquierda
int UpVal = 0;        // valor leído en palo PS2 izquierdo arriba/abajo
int RollLeftVal = 0;  // valor leído en palo PS2 izquierdo derecha/izquierda
int CamPitch = 90;

int upLraw = 0;  // Variables para transportar el valor actual de los datos a los ESC
int upRraw = 0;
int HLraw = 0;
int HRraw = 0;

int auxMillis = 0;
int intervaloEncendido = 1000;

boolean PSB_PAD_LEFTstate = false;   // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_PAD_UPstate = false;     // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_PAD_DOWNstate = false;   // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_PAD_RIGHTstate = false;  // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_GREENstate = false;      // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_PINKstate = false;       // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_BLUEstate = false;       // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
boolean PSB_REDstate = false;        // Genera variable para guardar y mandar los datos del botón Izquierda izquierdo al Esclavo
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
float V5;                                          // Variable para recibir los datos del Voltaje del ROV 5V
float V12;                                         // Variable para recibir los datos del Voltaje del ROV 12V
float Amp5;                                        // Variable para recibir los datos del consumo de Amperios del ROV en 5V
float Amp12;                                       // Variable para recibir los datos del consumo de Amperios del ROV en 12V

struct RECEIVE_DATA_STRUCTURE  // estructura de mensaje de datos recibidos de los sensores
{
  int average;              // Recibe mensaje de voltaje de batería de 5V
  int average1;             // Recibe mensaje de voltaje de batería de 12V
  int temperatura;          // Recibe mensaje de temperatura interior del ROV
  int temperatura1;         // Recibe mensaje de temperatura del motor derecho
  int temperatura2;         // Recibe mensaje de temperatura del motor izquierdo
  int humedad;              // Recibe mensaje de humedad del interior del ROV
  int humedad1;             // Recibe mensaje de humedad del motor derecho
  int humedad2;             // Recibe mensaje de humedad del motor izquierdo
  int AccX;                 // Recibe mensaje de datos de inclinación del eje X
  int AccY;                 // Recibe mensaje de datos de inclinación del eje Y
  int AccZ;                 // Recibe mensaje de datos de inclinación del eje Z
  int Temp;                 // Recibe mensaje de datos de temperatura del giroscopio
  int GyroX;                // Recibe mensaje de datos de aceleración en el eje X
  int GyroY;                // Recibe mensaje de datos de aceleración en el eje Y
  int GyroZ;                // Recibe mensaje de datos de aceleración en el eje Z
  int E18D80NK;             // Recibe mensaje de lectura del sensor infrarrojo E18-D80NK
  int pinLedColision;       // Recibe mensaje de encender alarma de colisión
  int pressure_bar;         // Recibe mensaje de lectura del sensor de presión SKU237545 en Bares
  int pressure_psi;         // Recibe mensaje de lectura del sensor de presión SKU237545 en PSI
  int pressure_bar1;        // Recibe mensaje de lectura del sensor de presión SKU237545 Interno en Bares
  int pressure_psi1;        // Recibe mensaje de lectura del sensor de presión SKU237545 Interno en PSI
  int ROVDepth;             // Manda mensaje de datos de lectura de profundidad de ROV (m)
  int ROVHDG;               // Manda mensaje de Dirección del ROV (grados)
  int sensorDS18B20;        // Manda mensaje de lectura del sensor de temperatura DS18B20
  int V5;                   // Manda mensaje de datos de voltaje de batería de 5V al maestro.
  int V12;                  // Manda mensaje de datos de voltaje de batería de 12V al maestro.

};

struct SEND_DATA_STRUCTURE  // estructura de mensaje de datos enviados
{
  int upLraw = 0;  //Variables para transportar los datos reales sin procesar de los ESCs
  int upRraw = 0;
  int HLraw = 0;
  int HRraw = 0;
  int CamPitch; //Angle of the camera servo.
  volatile boolean PSB_PAD_LEFTstate;   // Manda lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_PAD_UPstate;     // Manda lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_PAD_RIGHTstate;  // Manda lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_GREENstate;      // Manda lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_REDstate;        // Manda lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_PINKstate;       // Manda lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_BLUEstate;       // Manda lectura del botón Izquierda Izquierda al Esclavo
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
  Serial.begin(115200);      // Comienza la Comunicación en Serie para hablar con el ordenador a 9600 Baudios
  Serial1.begin(115200);    // Comienza la comunicación Serie en el puerto 1, pines 18 y 19, para hablar con el Arduino Esclavo
  Serial1.flush();         // Depura la información del Puerto Serie
  ETin.begin(details(rxdata), &Serial1);    // Comienza la recepción de datos a través de Serial, en los pines 18 y 19
  ETout.begin(details(txdata), &Serial1);   // Comienza el envío de datos a través de Serial, en los pines 18 y 19

  // Pines y ajustes de configuración: GamePad(clock, command, attention, data, Pressures?, Rumble?)
  ps2x.config_gamepad(22, 23, 24, 25, true, true);

  pinMode(led1, OUTPUT);  //se establece el pin del led1 como salida
  pinMode(led2, OUTPUT);  //se establece el pin del led2 como salida
  pinMode(led3, OUTPUT);  //se establece el pin del led3 como salida
  pinMode(led4, OUTPUT);  //se establece el pin del led4 como salida
  pinMode(led5, OUTPUT);  //se establece el pin del led5 como salida
  pinMode(led6, OUTPUT);  //se establece el pin del led6 como salida

  delay(10000); // Detiene el programa para dar tiempo a que se inicie el mando PS2
}

void loop()
{

  ETout.sendData();          // Enviar el mensaje al puerto serie para el Arduino del ROV

  {
    loop_Pantalla();
    loop_Datos();
    loop_SensorE18D80NK();  // Bloque de trabajo del sensor de infrarrojos
    loop_Led();
    loop_Mando_PS2();
  }

  for (int i = 0; i < 5; i++) { // Esta función, cambia el estado de envio a recepción cada 5 segundos
    (ETin.receiveData());    // Recibe el mensaje al puerto serie para el Arduino del ROV

  }
}
