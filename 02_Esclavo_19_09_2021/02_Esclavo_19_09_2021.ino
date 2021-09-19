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
#include <ESC.h>                // Librería para los ESC
#include <ACS712.h>             // Libreria para el sensor de corriente Amperios

EasyTransfer ETin, ETout;       // Genera los dos objetos de transferencia fácil para Comunicación bidireccional

volatile boolean LEDHdlts1;   // Para el estado de los focos
volatile boolean LEDHdlts;  // Para el estado de los led

const int pinDatosDQ = 28;                       // Pin donde se conecta el bus 1-Wire para los sensores de temperatura DS18B20
OneWire oneWireObjeto(pinDatosDQ);               // Instancia a las clases OneWire y DallasTemperature
DallasTemperature sensorDS18B20(&oneWireObjeto); // Instancia a las clases OneWire y DallasTemperature

Servo CamServo;  // Genera un objeto llamado CamServo
int CamPitch = 90;       // Variable para el ángulo, inicia el servo en 90º

// Se pone toda la identificación de los DHT22 junta

#define DHTPIN 22          // Nro. de pin donde se encuentra conectado el sensor del casco
#define DHTTYPE DHT22      // Modelo de sensor, puede ser DHT11, DHT21 o DHT22
DHT dht(DHTPIN, DHTTYPE);  // Inicializacion del sensor
#define DHT1PIN 24          // Nro. de pin donde se encuentra conectado el sensor del motor derecho
DHT dht1(DHTPIN, DHTTYPE); // Inicializacion del sensor
#define DHT2PIN 26          // Nro. de pin donde se encuentra conectado el sensor del motor izquierdo
DHT dht2(DHTPIN, DHTTYPE); // Inicializacion del sensor

float humedad = 0;
float temperatura = 0;
float humedad1 = 0;
float temperatura1 = 0;
float humedad2 = 0;
float temperatura2 = 0;
uint32_t prevMillis = millis();

unsigned long intervaloMedidas = 1000;  // Hace que solo se lean los valores 1 vez por segundo
unsigned long intervaloMedidas1 = 2500; // Hace que solo se lean los valores 1 vez cada 2 segundos
unsigned long auxMillis = 0; // Indica el valor del intervalo de tiempo
unsigned long auxMillis1 = 0; // Indica el valor del intervalo de tiempo

// Se pone toda la identificación de los ESC

float escDerecha, escIzquierda, escVertical, escVertical1; // se generan los 4 ESC
int cal_int = 0;  // se calibran los ESC

// Valores recibidos del mando PS2 para los motores

int ForwardVal = 0;   // valor leído en palo PS2 derecho arriba/abajo
int YawLeftVal = 0;   // valor leído en palo PS2 derecho derecha/izquierda
int UpVal = 0;        // valor leído en palo PS2 izquierdo arriba/abajo
int RollLeftVal = 0;  // valor leído en palo PS2 izquierdo derecha/izquierda

int upLraw = 0;  // Variables para transportar el valor actual de los datos a los ESC
int upRraw = 0;
int HLraw = 0;
int HRraw = 0;

// Se pone toda la identificación de los LED juntos

const int led1 = 40;  // El Pin del LED chivato de recibir datos del mando es el 40
const int led2 = 42;  // El pin del LED indicador de batería de 12V es el 42.
const int led3 = 44;  // El pin del LED indicador de batería de 5V es el 44.
const int led4 = 46;  // El pin utilizado para el LED de alarma de temperatura es el 36
const int led5 = 48;  // El pin utilizado para el aviso de peligro colisión en el pin 31
const int led6 = 50;  // El pin chivato de la bomba de achique

const int HeadLts = 34;    // El control del rele de los faros está en el pin 34

// Se pone toda la identificación del sistema de refrigeración junta

const int Refrigeracion = 52; // El pin utilizado para encender la bomba de refrigeración es el 52

// Se pone toda la identificación del MPU6050 junta

const int MPU6050_addr = 0x68; // Direction I2C del MPU6050
int16_t AccX, AccY, AccZ, Temp, GyroX, GyroY, GyroZ;

// Se pone toda la parte de lectura del Voltaje de la batería junta con el sensor FZ0430

int sensor_Voltios = A6;
int sensor_voltios1 = A7;

// Se pone toda la parte de la lectura de Amperios junta

ACS712  sensor(ACS712_30A, A0);

float amplitude_current;      //amplitud corriente
float effective_value;       //corriente efectiva


// Se pone toda la parte del sensor de infrarrojos E18D80NK

int pinSensorE18D80NK = 30;   // Se genera el sensor E18D80NK en el pin 30
boolean objectDetect = false; // Marca para mostrar si se ha detectado un objeto

// Se genera un pin de entrada de datos para el sensor de presión SKU237545

int SensorSKU237545_I = 32;  // Sensor de presión Interno conectado al pin 32
int SensorSKU237545_E = 33;  // Sensor de presión Externo conectado al pin 33

// Se pone toda la estructura de recepción de datos junta

struct RECEIVE_DATA_STRUCTURE
{
  int upLraw = 0;   // Variables para transportar los datos sin procesar reales de los ESC
  int upRraw = 0;
  int HLraw = 0;
  int HRraw = 0;
  int CamPitch; //Angle of the camera servo.
  volatile boolean PSB_PAD_LEFTstate;   // Recibe lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_PAD_UPstate;     // Recibe lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_PAD_RIGHTstate;  // Recibe lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_GREENstate;      // Recibe lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_REDstate;        // Recibe lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_PINKstate;       // Recibe lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_BLUEstate;       // Recibe lectura del botón Izquierda Izquierda al Esclavo
  volatile boolean PSB_L1state;         // Recibe lectura del botón Izquierda delante arriba al Esclavo
  volatile boolean PSB_L2state;         // Recibe lectura del botón Izquierda delante abajo al Esclavo
  volatile boolean PSB_L3state;         // Recibe lectura del botón Palo izquierdo abajo al Esclavo
  volatile boolean PSB_R1state;         // Recibe lectura del botón Derecha delante arriba al Esclavo
  volatile boolean PSB_R2state;         // Recibe lectura del botón Derecha delante abajo al Esclavo
  volatile boolean PSB_R3state;         // Recibe lectura del botón Palo derecho abajo al Esclavo
  volatile boolean LEDHdlts;            // Recibe que hacer con los LEDs, encendidos/apagados
  volatile boolean LEDHdlts1;           // Recibe que hacer con los Focos, encendidos/apagados
};

// Se pone toda la identificación del envío de datos junta

struct  SEND_DATA_STRUCTURE
{
  int average;              // Manda mensaje de datos del Amperimetro de 5V
  int average1;              // Manda mensaje de datos del Amperimetro de 12V
  int temperatura;          // Manda mensaje de datos de temperatura interior del ROV al Maestro
  int temperatura1;         // Manda mensaje de datos de temperatura del motor derecho al Maestro
  int temperatura2;         // Manda mensaje de datos de temperatura del motor izquierdo al Maestro
  int humedad;              // Manda mensaje de humedad al Maestro
  int humedad1;             // Manda mensaje de humedad al Maestro del motor derecho
  int humedad2;             // Manda mensaje de humedad al Maestro del motor izquierdo
  int AccX;                 // Manda mensaje de datos de inclinación del eje X al Maestro
  int AccY;                 // Manda mensaje de datos de inclinación del eje Y al Maestro
  int AccZ;                 // Manda mensaje de datos de de inclinación del eje Z al Maestro
  int Temp;                 // Manda mensaje de datos de temperatura del giroscopio al Maestro
  int GyroX;                // Manda mensaje de datos de aceleración en el eje X al Maestro
  int GyroY;                // Manda mensaje de datos de aceleración en el eje Y al Maestro
  int GyroZ;                // Manda mensaje de datos de aceleración en el eje Z al Maestro
  int E18D80NK;             // Manda mensaje de lectura del sensor infrarrojo E18-D80NK
  int pinLedColision;       // Manda mensaje de encender alarma de colisión
  int pressure_bar;         // Manda mensaje de lectura del sensor de presión SKU237545 Interno en Bares
  int pressure_psi;         // Manda mensaje de lectura del sensor de presión SKU237545 Interno en PSI
  int pressure_bar1;        // Manda mensaje de lectura del sensor de presión SKU237545 Interno en Bares
  int pressure_psi1;        // Manda mensaje de lectura del sensor de presión SKU237545 Interno en PSI
  int ROVDepth;             // Manda mensaje de datos de lectura de profundidad de ROV (m)
  int ROVHDG;               // Manda mensaje de Dirección del ROV (grados)
  int sensorDS18B20;        // Manda mensaje de lectura del sensor de temperatura DS18B20
  int V5;                   // Manda mensaje de datos de voltaje de batería de 5V al maestro.
  int V12;                  // Manda mensaje de datos de voltaje de batería de 12V al maestro.
};

RECEIVE_DATA_STRUCTURE rxdata; // Dar un nombre al grupo de datos recibidos
SEND_DATA_STRUCTURE txdata;    // Dar un nombre al grupo de datos enviados

void setup()
{

  // Se pone todo lo referente a la comunicación junta

  Wire.begin ();                           // Comienza la comunicación i2c
  Serial.begin(115200);                       // Comienza la Comunicación Serie para hablar con el ordenador a 9600 baudios
  Serial1.begin(115200);                     // Comienza la Comunicación Serie en el puerto 1, pines 18 y 19, para hablar con el Arduino Maestro
  Serial1.flush();                         // Depura la información del Puerto Serie
  ETin.begin(details(rxdata), & Serial1);  // Comienza la recepción de datos a través de Serial, en los pines 18 y 19
  ETout.begin(details(txdata), & Serial1); // Comienza el envío de datos a través de Serial, en los pines 18 y 19
  sensorDS18B20.begin();                   // Comienza el trabajo del sensor DS18B20

  CamServo.attach(7);

  // Se define el inicio del LED y de los Focos

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);

  pinMode(HeadLts, OUTPUT);
  digitalWrite(HeadLts, LOW);  // Establezca los faros en Off

  // Datos para el Voltimetro

  pinMode(A6, INPUT);   // Pin entrada datos Voltimetro 5V
  pinMode(A7, INPUT);   // Pin entrada datos Voltimetro 12V

  // Datos para el Amperimetro



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
  pinMode(SensorSKU237545_I, INPUT);

  // Se inicia el pin del sensor de presión SKU237545 Externo
  pinMode(SensorSKU237545_E, INPUT);

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

  {
    loop_ACS712_5V();       // Bloque de tranajo del Amperimetro de la bateria de 5V
    loop_ACS712_12V();       // Bloque de tranajo del Amperimetro de la bateria de 5V
    loop_CamServo();        // Bloque de trabajo del servo
    loop_DHT22();           // Bloque de trabajo de los sensores de temperatura y humedad DHT22
    loop_ESC();             // Bloque de trabajo de los ESC de los motores
    loop_MPU6050();         // Bloque de trabajo del Giroscopio
    loop_SensorE18D80NK();  // Bloque de trabajo del sensor de infrarrojos
    loop_Led_Mando_PS2();   // Bloque de trabajo del LED chivato del mando
    loop_Luces();           // Bloque de trabajo de los focos
    loop_SKU237545_I();     // Bloque de trabajo del sensor de presión interno
    loop_SKU237545_E();     // Bloque de trabajo del sensor de presión externo
    loop_DS18B20();         // Bloque de trabajo del sensor de temperatura DS18B20
    loop_V5();              // Bloque de trabajo para medir el voltaje de la batería de 5V
    loop_V12();             // Bloque de trabajo para medir el voltaje de la batería de 12V
  }

  for (int i = 0; i < 5; i++) {// Esta función, cambia el estado de envio a recepción cada 5 segundos
    ETout.sendData();       // Manda el mensaje al puerto serie para el Arduino del ROV
  }

  delay (1000);
}
