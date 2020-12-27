/*

Programa Esclavo, este es el que va dentro del vehículo
Por favor lea el archivo LÉAME

Slave Program that is the one that is on the surface and controls the movements of the ROV
Please read the README or Readme English file

*/

// Se ponen todas las librerías juntas

#include <Servo.h>              // librería para gestionar los servos y los ESC
#include <EasyTransfer.h>       // librería Easy Transfer de Bill Porter
#include <Adafruit_Sensor.h>    // librería para gestionar el sensor de temperatura DHT22
#include <DHT.h>                // librería para el sensor DHT 22
#include <OneWire.h>            // librería para el sensor de temperatura DS18B20
#include <DallasTemperature.h>  // Librería para el sensor de temperatura DS18B20
#include <MPU6050.h>            // librería i2c para el Giroscopio ***
#include <PS2X_lib.h>           // Librería para el mando PS2
#include <ESC.h>                // Librería para los ESC

PS2X ps2x;                      // Genera un objeto llamado ps2x
EasyTransfer ETin, ETout;       // Genera los dos objetos de transferencia fácil para Comunicación bidireccional

volatile boolean LEDHdlts;   // Para el estado de los focos
volatile boolean LEDHdlts1;  // Para el estado de los led

const int pinDatosDQ = 28;                       // Pin donde se conecta el bus 1-Wire para los sensores de temperatura
OneWire oneWireObjeto(pinDatosDQ);               // Instancia a las clases OneWire y DallasTemperature
DallasTemperature sensorDS18B20(&oneWireObjeto); // Instancia a las clases OneWire y DallasTemperature

// Se pone toda la identificación de los DHT22 junta

DHT dht(22, DHT22);    // Seleccionamos el pin y tipo de sensor del casco
DHT dht1(24, DHT22);   // Seleccionamos el pin y tipo de sensor del motor derecho
DHT dht2(26, DHT22);   // Seleccionamos el pin y tipo de sensor del motor izquierdo

// Se pone toda la identificación de los ESC y los Servos junta

Servo Servo1;   // Genera objeto Servo1 ESC motor Derecho
Servo Servo2;   // Genera objeto Servo2 ESC motor Izquierdo
Servo Servo3;   // Genera objeto Servo3 ESC motor Inmersion 1
Servo Servo4;   // Genera objeto Servo4 ESC motor Inmersion 2
Servo CamServo;  // Genera un objeto llamado CamServo
int CamPitch = 90;       // Variable para el ángulo, inicia el servo en 90º

int ForwardVal = 0;   // valor leído en palo PS2 derecho arriba/abajo
int YawLeftVal = 0;   // valor leído en palo PS2 derecho derecha/izquierda
int UpVal = 0;        // valor leído en palo PS2 izquierdo arriba/abajo
int RollLeftVal = 0;  // valor leído en palo PS2 izquierdo derecha/izquierda

int upLraw = 0;  // Variables para transportar el valor actual de los datos a los ESC
int upRraw = 0;
int HLraw = 0;
int HRraw = 0;

// Se pone toda la identificación de los LED juntos

const int led1 = 14;  // El pin del LED indicador de batería es 14.
const int led2 = 38;  // El Pin utilizado como chivato de recibir datos del mando
const int led3 = 36;  // El pin utilizado para el LED de alarma de temperatura es el 36
const int led4 = 31;  // El pin utilizado para el aviso de peligro colisión en el pin 31
const int led5 = 40;  // El pin chivato del mando es el 5

const int HeadLts = 34;    // El control de los faros está en el pin 34

// Se pone toda la identificación del sistema de refrigeración junta

const int Refrigeracion = 34; // El pin utilizado para encender la bomba de refrigeración es el 34


// Se pone toda la identificación del MPU6050 junta

const int MPU6050_addr = 0x68; // Direction I2C del MPU6050
int16_t AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ;

// Se pone toda la parte de lectura de la batería junta

int pin_voltaje_5V = A7; // pin analógico utilizado para leer el voltaje de la batería
float voltaje_entrada;  // variable para leer el voltaje del pin analógico
float voltaje_final;
float r1 = 100000; // El valor de la resistencia 1, es de 1M
float r2 = 10000; // El valor de la resistencia 2, es de 100K
// Donde r1 = 1M ohmios y r2 = 100K ohmios para un voltaje máximo de 55 V.

// Se pone toda la parte del sensor E18D80NK

int pinSensorE18D80NK = 30;   // Se genera el sensor E18D80NK en el pin 30
boolean objectDetect = false; // Marca para mostrar si se ha detectado un objeto

// Se generan todos los botones del mando

boolean PSB_PAD_UPstate = false;     // Genera el botón Izquierda arriba al Esclavo
boolean PSB_PAD_DOWNstate = false;   // Genera el botón Izquierda abajo al Esclavo
boolean PSB_PAD_LEFTstate = false;   // El botón Izquierda izquierdo ya esta usado para encender los focos
boolean PSB_PAD_RIGHTstate = false;  // Genera el botón Izquierda derecho al Esclavo
boolean PSB_BLUEstate = false;       // Genera el botón Cruz azul al Esclavo
boolean PSB_GREENstate = false;      // Genera el botón Triangulo verde al Esclavo
boolean PSB_PINKstate = false;       // Genera el botón Cuadrado rosa al Esclavo
boolean PSB_REDstate = false;        // Genera el botón Circulo rojo al Esclavo
boolean PSB_L1state = false;         // Genera el botón Izquierda delante arriba al Esclavo
boolean PSB_L2state = false;         // Genera el botón Izquierda delante abajo al Esclavo
boolean PSB_L3state = false;         // Genera el botón Palo izquierdo abajo al Esclavo
boolean PSB_R1state = false;         // Genera el botón Derecha delante arriba al Esclavo
boolean PSB_R2state = false;         // Genera el botón Derecha delante abajo al Esclavo
boolean PSB_R3state = false;         // Genera el botón Palo derecho abajo al Esclavo

// Se genera un pin de entrada de datos para el sensor de presión SKU237545

int SensorSKU237545_I = 32;  // Sensor de presión Interno
int SensorSKU237545_E = 33;  // Sensor de presión Externo

// Se pone toda la estructura de recepción de datos junta

struct RECEIVE_DATA_STRUCTURE
{
  int upLraw = 0;   // Variables para transportar los datos sin procesar reales de los ESC
  int upRraw = 0;
  int HLraw = 0;
  int HRraw = 0;
  volatile boolean PSB_PAD_UPstate;     // Recibe lectura del botón Izquierda arriba del Maestro
  volatile boolean PSB_PAD_DOWNstate;   // Recibe lectura del botón Izquierda abajo del Maestro
  volatile boolean PSB_PAD_RIGHTstate;  // Recibe lectura del botón Izquierda derecha del Maestro
  volatile boolean PSB_PAD_LEFTstate;   // Recibe lectura del botón Izquierda Izquierda del Maestro
  volatile boolean PSB_BLUEstate;       // Recibe lectura del botón Cruz azul del Maestro
  volatile boolean PSB_GREENstate;      // Recibe lectura del botón Triangulo verde del Maestro
  volatile boolean PSB_PINKstate;       // Recibe lectura del botón Cuadrado rosa del Maestro
  volatile boolean PSB_REDstate;        // Recibe lectura del botón Circulo rojo del Maestro
  volatile boolean PSB_L1state;         // Recibe lectura del botón Delante izquierda arriba del Maestro
  volatile boolean PSB_L2state;         // Recibe lectura del botón Delante izquierda abajo del Maestro
  volatile boolean PSB_L3state;         // Recibe lectura de presión Palo izquierda del Maestro
  volatile boolean PSB_R1state;         // Recibe lectura del botón Delante derecha arriba del Maestro
  volatile boolean PSB_R2state;         // Recibe lectura del botón Delante derecha abajo del Maestro
  volatile boolean PSB_R3state;         // Recibe lectura de presión Palo izquierdo del Maestro
  volatile boolean LEDHdlts;            // Luces LED encendidas / apagadas
};

// Se pone toda la identificación del envío de datos junta

struct  SEND_DATA_STRUCTURE
{
  int BattVolt_5;             // Manda mensaje de datos de voltaje de batería al maestro.
  int t;                    // Manda mensaje de datos de temperatura interior del ROV al Maestro
  int t1;                   // Manda mensaje de datos de temperatura del motor derecho al Maestro
  int t2;                   // Manda mensaje de datos de temperatura del motor izquierdo al Maestro
  int ROVDepth;             // Manda mensaje de datos de lectura de profundidad de ROV (m)
  int ROVHDG;               // Manda mensaje de Dirección del ROV (grados)
  int h;                    // Manda mensaje de humedad al Maestro
  int h1;                   // Manda mensaje de humedad al Maestro del motor derecho
  int h2;                   // Manda mensaje de humedad al Maestro del motor izquierdo
  int AccX;                 // Manda mensaje de datos de inclinación del eje X al Maestro
  int AccY;                 // Manda mensaje de datos de inclinación del eje Y al Maestro
  int AccZ;                 // Manda mensaje de datos de de inclinación del eje Z al Maestro
  int Temp;                 // Manda mensaje de datos de temperatura del giroscopio al Maestro
  int GyroX;                // Manda mensaje de datos de aceleración en el eje X al Maestro
  int GyroY;                // Manda mensaje de datos de aceleración en el eje Y al Maestro
  int GyroZ;                // Manda mensaje de datos de aceleración en el eje Z al Maestro
  int E18D80NK;             // Manda mensaje de lectura del sensor infrarrojo E18-D80NK
  int pinLedColision;       // Manda mensaje de encender alarma de colisión
  int sensorDS18B20;        // Manda mensaje de lectura del sensor de temperatura DS18B20
  int pressure_bar;         // Manda mensaje de lectura del sensor de presión SKU237545 Interno en Bares
  int pressure_psi;         // Manda mensaje de lectura del sensor de presión SKU237545 Interno en PSI
  int pressure_bar1;        // Manda mensaje de lectura del sensor de presión SKU237545 Interno en Bares
  int pressure_psi1;        // Manda mensaje de lectura del sensor de presión SKU237545 Interno en PSI
};

RECEIVE_DATA_STRUCTURE rxdata; // Dar un nombre al grupo de datos recibidos
SEND_DATA_STRUCTURE txdata;    // Dar un nombre al grupo de datos enviados

unsigned long intervaloMedidas = 1000;  // Hace que solo se lean los valores 1 vez por segundo
unsigned long intervaloMedidas1 = 2000; // Hace que solo se lean los valores 1 vez cada 2 segundos
unsigned long auxMillis = 0; // Indica el valor del intervalo de tiempo

void setup()
{

  // Se pone todo lo referente a la comunicación junta

  Wire.begin ();                           // Comienza la comunicación i2c
  Serial.begin(9600);                       // Comienza la Comunicación Serie para hablar con el ordenador a 9600 baudios
  Serial1.begin(9600);                     // Comienza la Comunicación Serie en el puerto 1, pines 18 y 19, para hablar con el Arduino Maestro
  Serial1.flush();                         // Depura la información del Puerto Serie
  ETin.begin(details(rxdata), & Serial1);  // Comienza la recepción de datos a través de Serial, en los pines 18 y 19
  ETout.begin(details(txdata), & Serial1); // Comienza el envío de datos a través de Serial, en los pines 18 y 19
  sensorDS18B20.begin();                   // Comienza el trabajo del sensor DS18B20

  // Se define el inicio del LED y de los Focos

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);


  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);


  pinMode(HeadLts, OUTPUT);
  digitalWrite(HeadLts, LOW);  // Establezca los faros en Off


  // Se inician los ESC y se define en que pin actúa cada uno
  Servo1.attach(3);
  Servo2.attach(4);
  Servo3.attach(5);
  Servo4.attach(6);
  CamServo.attach(7); // Adjunte el servo de dirección al pin 4

  // Se inician y se manda a imprimir la prueba de funcionamiento de los sensores DHT22
  dht.begin();  // Inicia el trabajo del sensor DHT22 del casco
  Serial.println (F(" \n Probando sensor DHT22 casco!"));
  dht1.begin(); // Inicia el trabajo del sensor DHT22 del motor derecho
  Serial.println (F(" \n Probando sensor DHT22 motor DR!"));
  dht2.begin(); // Inicia el trabajo del sensor DHT22 del motor izquierdo
  Serial.println (F(" \n Probando sensor DHT22 motor IZ!"));

  // Se inician los pines del sensor
  pinMode(pinSensorE18D80NK, INPUT_PULLUP); // Definir pin como sensor de entrada

  // Se inicia el pin del sensor de presión SKU237545 Interno
  pinMode (SensorSKU237545_I, INPUT);

  // Se inicia el pin del sensor de presión SKU237545 Externo
  pinMode (SensorSKU237545_E, INPUT);

  // Se inicia el pin A7 como entrada de datos del voltaje de la bateria
  pinMode(pin_voltaje_5V, INPUT);

  // Proceso para iniciar el giroscopio MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

delay (1000);
}

void loop ()
{

  ETin.receiveData();     // Recibe el mensaje del Arduino Maestro

  for (int i = 0; i < 5; i++) {// Esta función, cambia el estado de envio a recepción cada 5 segundos

    ETout.sendData();       // Manda el mensaje al puerto serie para el Arduino del ROV
    {
      loop_MandoPS2();        // Bloque de tabajo del mando PS2
      loop_ESC();             // Bloque de trabajo de los ESC de los motores
      loop_CamServo();  // Bloque de trabajo del servo
      loop_Luces();           // Bloque de trabajo de los focos
      loop_Voltaje_5V();         // Bloque de trabajo para medir el voltaje de la batería
      loop_DHT22();           // Bloque de trabajo de los sensores de temperatura y humedad DHT22
      loop_MPU6050();         // Bloque de trabajo del Giroscopio
      loop_SensorE18D80NK();  // Bloque de trabajo del sensor de infrarrojos
      loop_DS18B20();         // Bloque de trabajo del sensor de temperatura DS18B20
      loop_SKU237545_I();     // Bloque de trabajo del sensor de presión interno
      loop_SKU237545_E();     // Bloque de trabajo del sensor de presión externo
    }
  }
}
void loop_MandoPS2() { // Bloque de trabajo del mando PS2

  PSB_PAD_UPstate = (rxdata.PSB_PAD_UPstate);         // Recibe lectura del botón Izquierda arriba al Esclavo
  PSB_PAD_DOWNstate = (rxdata.PSB_PAD_DOWNstate);     // Recibe lectura del botón Izquierda abajo al Esclavo
  PSB_PAD_LEFTstate = (rxdata.PSB_PAD_LEFTstate);     // Recibe lectura del botón Izquierda Izquierda al Esclavo
  PSB_PAD_RIGHTstate = (rxdata.PSB_PAD_RIGHTstate);   // Recibe lectura del botón Izquierda derecho al Esclavo
  PSB_BLUEstate = (rxdata.PSB_BLUEstate);             // Recibe lectura del botón Cruz azul al Esclavo
  PSB_GREENstate = (rxdata.PSB_GREENstate);           // Recibe lectura del botón Triangulo verde al Esclavo
  PSB_PINKstate = (rxdata.PSB_PINKstate);             // Recibe lectura del botón Cuadrado rosa al Esclavo
  PSB_REDstate = (rxdata.PSB_REDstate);               // Recibe lectura del botón Circulo rojo al Esclavo
  PSB_L1state = (rxdata.PSB_L1state);                 // Recibe lectura del botón Izquierda delante arriba al Esclavo
  PSB_L2state = (rxdata.PSB_L2state);                 // Recibe lectura del botón Izquierda delante abajo al Esclavo
  PSB_L3state = (rxdata.PSB_L3state);                 // Recibe lectura del botón Palo izquierdo abajo al Esclavo
  PSB_R1state = (rxdata.PSB_R1state);                 // Recibe lectura del botón Derecha delante arriba al Esclavo
  PSB_R2state = (rxdata.PSB_R2state);                 // Recibe lectura del botón Derecha delante abajo al Esclavo
  PSB_R3state = (rxdata.PSB_R3state);                 // Recibe lectura del botón Palo derecho abajo al Esclavo

  if (rxdata.PSB_PAD_UPstate)  // Si presionamos el botón izquierda arriba
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_PAD_DOWNstate)  // Si presionamos el botón izquierda abajo
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_PAD_RIGHTstate) // Si presionamos el botón izquierda derecha
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  // if (rxdata.PSB_PAD_LEFTstate) // Lee el valor del botón Izquierda Izquierda al Esclavo
  // que ya se hace en el void loop_luces

  if (rxdata.PSB_GREENstate) // Si presionamos triangulo verde
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_REDstate) // Si presionamos el círculo rojo
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_BLUEstate) // Si presionamos el cruz azul
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_PINKstate) // Si presionamos el cuadrado rosa
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_L1state) // Si presionamos el botón L1
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_L2state) // Si presionamos el botón L2
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  /*  if (rxdata.PSB_R1state) // Si presionamos el botón R1
    // que ya se hace con el void ServoInmersion
    {
      ServoInmersion = !ServoInmersion + 1;
      grnLEDHdlts = !grnLEDHdlts;                      // Cambia el estado del LED ON / OF
    }

    if (rxdata.PSB_R2state) // Si presionamos el botón R2
    {
      ServoInmersion = !ServoInmersion - 1;
      grnLEDHdlts = !grnLEDHdlts;                      // Cambia el estado del LED ON / OF
    }
  */

  if (rxdata.PSB_L3state) // Si presionamos el joystick izquierdo hacia abajo
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

  if (rxdata.PSB_R3state) // Si presionamos el joystick derecho hacia abajo
  {
    LEDHdlts1 = !LEDHdlts1;                      // Cambia el estado del LED ON / OF
  }

}

void loop_ESC() { // Bloque de trabajo de los ESC de los motores

  ForwardVal = ps2x.Analog(PSS_RY);
  YawLeftVal = ps2x.Analog(PSS_RX);
  UpVal = ps2x.Analog(PSS_LY);
  RollLeftVal = ps2x.Analog(PSS_LX);

  upLraw = (128 - UpVal) + (128 - RollLeftVal) / 2; // esto será hasta un valor de 192
  upRraw = (128 - UpVal) - (128 - RollLeftVal) / 2; // esto será hasta un valor de 192
  HLraw = (128 - ForwardVal) + (128 - YawLeftVal); // esto será hasta un valor de 256
  HRraw = (128 - ForwardVal) - (128 - YawLeftVal); // esto será hasta un valor de 256

  // Scala los valores para que sean adecuados para los ESC y los servos
  upLraw = map(upLraw, -193, 193, 0, 179);
  upRraw = map(upRraw, -193, 198, 0, 179);
  HLraw = map(HLraw, -256, 256, 0, 179);
  HRraw = map(HRraw, -256, 256, 0, 179);

  // escribe el valor 0 en los servos

  Servo1.write(upLraw);
  Servo2.write(upRraw);
  Servo3.write(HLraw);
  Servo4.write(HRraw);

}

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

void loop_Luces() {// Bloque de trabajo de los focos

  digitalWrite(HeadLts, rxdata.LEDHdlts);
  // Enciende los faros en función del estado del boton
  if (rxdata.LEDHdlts > 0)
  {
    digitalWrite(HeadLts, LOW);
    Serial.print (F(" \n Focos apagados "));
  }
  else
  {
    (rxdata.LEDHdlts < 0);
    digitalWrite(HeadLts, HIGH);
    Serial.print (F(" \n Focos encendidos "));
  }
}

void loop_Voltaje_5V() {// Bloque de trabajo de medición de voltaje de la batería

  if ( millis() - auxMillis > intervaloMedidas1) // Indica el valor de intervalo entre toma de datos del sensor
  {
    voltaje_entrada = (analogRead(pin_voltaje_5V) * 5.00) / 1024; // Lee el voltaje de entrada de la batería a través del divisor de voltaje.
    voltaje_final = voltaje_entrada / (r2 / (r1 + r2));
    txdata.BattVolt_5 = voltaje_final;  // Enviar de vuelta el voltaje de la batería a bordo.
    auxMillis = millis();
    Serial.print (F(" \n Voltaje línea 5 V = "));
    Serial.print(voltaje_final);
  }

  else if (voltaje_final > 5)
  {
    // Si el voltaje final es menor que 5 Voltios
    // Enciende el LED de advertencia
    digitalWrite(led1, HIGH);
    // Escribe el texto
    Serial.print (F(" \n VOLTAJE BAJO !"));
  }
}

void loop_DHT22() {// Bloque de trabajo de los sensores DHT22

  if ( millis() - auxMillis > intervaloMedidas) // Indica el valor de intervalo entre toma de datos del sensor
  {
    float h = dht.readHumidity();
    // Lectura de Humedad desde el sensor DHT22 del interior del ROV
    float t = dht.readTemperature();
    // Lectura de Temperatura desde el sensor DHT22 del interior del ROV
    float h1 = dht1.readHumidity();
    // Lectura de Humedad desde el sensor DHT22 del motor derecho
    float t1 = dht1.readTemperature();
    // Lectura de Temperatura desde el sensor DHT22 del motor derecho
    float h2 = dht2.readHumidity();
    // Lectura de Humedad desde el sensor DHT22 del motor izquierdo
    float t2 = dht2.readTemperature();
    // Lectura de Temperatura desde el sensor DHT22 del motor izquierdo

    // Comprueba si hay fallo en todas las lecturas y sale rápido y prueba otra vez
    if (isnan(h) || isnan(t)) {
      Serial.print (F(" \n Fallo de lectura desde el sensor DHT del Casco!"));
      //      return;
    }
    else if (isnan(h1) || isnan(t1))
    {
      Serial.print (F(" \n Fallo de lectura desde el sensor DHT del motor DR!"));
      //      return;
    }
    else if (isnan(h2) || isnan(t2))
    {
      Serial.print (F(" \n Fallo de lectura desde el sensor DHT del motor IZ!"));
      //      return;
    }
    else if (( millis() - auxMillis) > intervaloMedidas)
    {
      txdata.t = t;   // Envía al Maestro la temperatura leída en el casco
      txdata.h = h;   // Envía al Maestro la humedad leída en el casco
      txdata.t1 = t1; // Envía al Maestro la temperatura leída en el motor derecho
      txdata.h1 = h1; // Envía al Maestro la humedad leída en el motor derecho
      txdata.t2 = t2; // Envía al Maestro la temperatura leída en el motor izquierdo
      txdata.h2 = h2; // Envía al Maestro la humedad leída en el motor izquierdo
      auxMillis = millis();
    }
    else if (t > 40 || t1 > 40 || t2 > 40)
    {
      // Si la temperatura de cualquiera de los sensores DHT22 es demasiado alta (más de 40 grados C)
      // Enciende el LED de advertencia
      digitalWrite(led3, HIGH);
      // Enciende la bomba de refrigeración
      digitalWrite(Refrigeracion, HIGH);
      // Escribe el texto
      Serial.print (F(" \n TEMPERATURA ELEVADA !"));
    }

    Serial.print (F(" \n Temperatura en el casco = "));
    Serial.print (t);
    Serial.print (F(" *C "));
    Serial.print (F(" \n Temperatura en el motor DR = "));
    Serial.print (t1);
    Serial.print (F(" *C1 "));
    Serial.print (F(" \n Temperatura en el motor IZ = "));
    Serial.print (t2);
    Serial.print (F(" *C2 "));
    Serial.print (F(" \n Humedad en el Casco = "));
    Serial.print (h);
    Serial.print (F(" %\t"));
    Serial.print (F(" \n Humedad en el motor DR = "));
    Serial.print (h1);
    Serial.print (F(" %\t"));
    Serial.print (F(" \n Humedad en el motor IZ = "));
    Serial.print (h2);
    Serial.print (F(" %\t"));
  }
}

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

void loop_SensorE18D80NK() {// Bloque de trabajo del sensor infrarrojo

  int E18D80NK = digitalRead(pinSensorE18D80NK); // leer el Sensor

  if (E18D80NK > 0) {
    Serial.println (F(" \n Todo despejado"));
    digitalWrite(led4, LOW); // encender el LED de peligro
  }
  else {
    Serial.println (F(" \n Peligro Objeto detectado"));
    digitalWrite(led4, HIGH); // Apagar el LED de peligro
  }
  txdata.E18D80NK = E18D80NK;
}

void loop_DS18B20() {  // Bloque de trabajo del sensor de temperatura DS18B20

  sensorDS18B20.requestTemperatures();
  Serial.print (F("\n Temperatura sensor DS18B20 = "));
  Serial.print (sensorDS18B20.getTempCByIndex(0));
  Serial.print (F(" ºC"));
  txdata.sensorDS18B20 = sensorDS18B20.getTempCByIndex(0);
}

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
