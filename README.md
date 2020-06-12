Ninguno de los programas, funciona aun como es debido

Los dos primeros programas

01 Programa Maestro

02 Programa Esclavo

Son para utilizar con el IDE Arduino

El programa llamado
04 VSC PIO projects

Es para utilizar con el programa Visual Studio Code más el complemento Platform-IO

En este repositorio, voy a publicar las modificaciones hechas a los programas para controlar un ROV, comenzó los programas con el IDE de Arduino, y con dos placas Arduino Mega 2560, pero en vista del tamaño y la complicación de los códigos, ahora estoy usando Visual Studio Code, con Platfor IO, y posiblemente tengamos que cambiar de placas por dos ESP32, dados los problemas que se me plantean con la depuración de los códigos.
Como bien pone en el título del repositorio, estos programas irán evolucionando y cambiando, según valla progresando en la depuración de los códigos como de los dos programas.
Los programas ahora mismo, compilan con el IDE Arduino, pero no operan todo lo bien que tienen problemas, por eso él puso en el título de los programas, "no funcionan aún", espero poder resolver todos los problemas en breve.
Os mantendré informados de los cambios, un saludo a todo el mundo.

La versión original tomada como punto de partida es la siguiente
ROVPS2Control_Slavev8.ino
Hamish Trolove - 30 de marzo de 2016
www.techmonkeybusiness.com
Este boceto toma los comandos que se le envían desde la unidad Maestra con el controlador PS2 conectado y lo convierte en comandos de motor, Servo comandos, controles de luz, etc. Los datos se envían desde el Arduino (maestro) al ROV (esclavo) utilizando la biblioteca EasyTransfer de Bill Porter a través de un enlace en serie de 9600 baudios (anclaje de 100 m). La biblioteca MS5803_14 es de Luke Miller http://github.com/millerlp
Ver también como se desarrolla el proyecto original con los siguientes códigos:
HoryzonTrigger.ino, ROVPS2Control_Masterv0.ino,
ROVDoNothing.ino, ROVSubBv0.ino, DigitalCompassv2.ino,
PTLoggerv4.ino y TMP36_Temperature_Sensor.ino.
En la página www.techmonkeybusiness.com


Modificado por asesorplaza1 en las diferentes fechas indicadas
Las primeras pruebas y cambios del código, se iniciaron en 2.016, debido a la cantidad de modificaciones
A partir de ahora 30/01/2020, se ponen las fechas y los cambios en la descripción del proyecto
Para facilitar la búsqueda de errores en los diferentes cambios del código

30/01/2020 ya se han comentado todas las líneas de control de la cámara y del LCD
Le añado 2 DHT22 y así estarán los 3 que me hacen falta
He borrado varias líneas de control de la cámara que no se va a utilizar

01/02/2020 le añado los controles del giroscopio facilitados por Dea de www.cambatronics.com

02/02/2020 le añado la orden para leer solo 1 vez X segundo el DHT22, truco de José Luis de
www.cambatronics.com y se borran las líneas correspondientes al control de la cámara de video, no utilizadas por asesorplaza1, en esta modificación del proyecto original

04/02/2020 modifico las líneas de lectura de los sensores, porque hasta ahora solo me imprime en Monitor Serie el texto, no los datos

06/02/2020 se depura un poco el código, y se modifica el encabezado del código

08/02/2020 se corrige el error de lectura en los sensores, y se corrige la escritura del Monitor Serie

12/02/2020 para poder añadir cualquier código hay que seguir unas reglas especificas de programación
Se modifica la estructura del código siguiendo esas órdenes de programación, según la información obtenida y guardada
En la carpeta 01_UNIR_2_CODIGOS
Se crean varios bloques en el void loop, para el funcionamiento de cada uno de los sensores, eliminando los delay()

13/02/2020 se incluye el sensor de temperatura DS18B20, ayudado por DEA de www.cambatronics.com

16/02/2020  Se añade el sensor de distancia infrarrojo E18-D80NK, sin errores y consigo adaptar un código para leer el sensor de presión SKU237545

08/03/2020 se conecta un relé en el pin 12 del Arduino Esclavo, para encender los focos de luz externos, no hace falta cambiar el código

26/03/2020 Se incluye la librería MPU6050, para controlar el giroscopio
Se arregla el envió de datos, separando los datos del Monitor Serie, y los datos que hay que enviar al Arduino Maestro, iniciando dos puertos serie con las ordenes

Serial.begin(57600);     // Puerto Serie USB

Serial1.begin(57600);    // Puerto Serie en los pines 18 y 19

ETin.begin(details(rxdata), &Serial1);    // Comienza la recepción de datos a través de Serial, en los pines 18 y 19

ETout.begin(details(txdata), &Serial1);   // Comienza el envío de datos a través de Serial, en los pines 18 y 19

28/03/2020 Se incluyen el envió de todas las instrucciones del mando, para tener todos los botones operativos (no funciona)

03/04/2020 Se incluye la parte nueva del Giroscopio MPU6050, que muestra los 3 ejes de inclinación, más la temperatura del Giroscopio.
También se incluye el segundo sensor de presión

05/04/2020 se cambia el código del sensor infrarrojo E18D80NK, por uno mejor

11/04/2020 Corrijo el código según las instrucciones de mi amigo Atilano Belinchón

13/04/2020 Corrijo las lecturas y envió de datos del sensor de infrarrojos E18D80NK

15/04/2020 Se incluye el servo de dirección para accionarlo con los botones R1 y R2 del mando según información obtenida de la página

https://arduparatodos.blogspot.com/2017/02/controlar-servomotor-con-arduino-varios.html

18/04/2020 Se cambian algunos " if ", por " else if ", para darle agilidad al código, siguiendo las instrucciones de DEA de www.cambatronics.com

Entre el día 24/03/2020 y el día 28/04/2020, se hacen varios cambios en el código para mejorarlo y conseguir que el mando funcione, Siguiendo las instrucciones de Bigbadbob en las publicaciones del foro

http://www.homebuiltrovs.com/rovforum/viewtopic.php?f=18&t=1908

A partir de la página 4

28/04/2020 Se corrige la ortografía de todo el texto que no son órdenes

03/05/2020 Se cambian las asignaciones de los pines, según el código de Github

Las nuevas asignaciones de pines son:

Salida de 3.3V a PIN rojo PS2
Pin 24 a PIN amarillo PS2 + resistencia 1k
Pin 23 a PIN naranja PS2
Pin 25 a PIN marrón PS2 + resistencia 1k
Pin 22 a PIN azul PS2

Se arregla el código para que me salga en el Maestro el estado de los focos, encendidos / apagados

04/05/2020 Se depura el código según los consejos de Bigbadbob de http://www.homebuiltrov.com

05/05/2020 Se incluye la Macro F, en todos los Serial.print, para reducir el consumo de memoria dinámica
Según los consejos de Bigbadbob de  https://www.homebuiltrov.com , pero me da problemas

06/05/2020 Se depura el código para un mejor funcionamiento, según los consejos de Bigbadbob de http://www.homebuiltrov.com y siguen los problemas con la Macro F

07/05/2020 Se depura el código para un mejor funcionamiento, según los consejos de Bigbadbob de http://www.homebuiltrov.com y siguen los problemas con la Macro F

08/05/2020 Se corrigen los problemas de la Macro F, en todos los Serial.print de texto fijo
No se puede poner la Macro F, a los Serial.print de datos de los sensores
Y se consigue reducir el consumo de memoria dinámica considerablemente

09/05/2020 Se siguen corrigiendo líneas para la depuración del código, según los consejos de Bigbadbob de http://www.homebuiltrov.com . Pero siguen los problemas con el mando de la PS2

10/05/2020 Me doy cuenta de un error en la orden de encender los focos y lo corrijo. Pero el mando sigue sin funcionar como es debido

11/05/2020 Se modifican varias órdenes del control de los botones, pero el mando sigue sin funcionar correctamente

16/05/2020 Se hacen diversos cambios, según los consejos de Tsanshon de www.foromodelismonaval.es

02/06/2020, Haciendo caso a Tsanshon, instalo el programa Atom más el complemento Platform-IO, para depurar los programas

06/06/2020, Me registro en el foro Platfor-IO, en busca de soluciones, y me dicen que ya no se da soporte para Atom, por lo que tengo que desinstalar este programa, e instalar Visual Estudio Code, con el complemento Platform-IO

11/06/2020, Después de conseguir que los programas funcionen en VSC + PIO, resulta que no puedo continuar el trabajo, porque no se han actualizado los componentes de VSC + PIO, para Arduino, la mayoría de la gente que utiliza estos programas, también utilizan otras placas, que son las ESP32, con muchas más posibilidades que Arduino, ya he comprado unas placas de esas, y estoy esperando a que me lleguen, son más baratas que las placas Arduino.











Los datos enviados desde el maestro son configuraciones sin formato para el control ESC.

Este boceto está diseñado para un Arduino Nano con un solo puerto serie.
Yo lo estoy usando en un Mega 2560, y funciona

Las asignaciones de pin son;
D13 = pin LED ROJO.
D12 = Control de faros
D11 = Pasador de puente
D8 = ESC Vertical Izquierda
D7 = ESC Vertical Derecha
D6 = ESC Horizontal Izquierda
D5 = ESC Horizontal Derecha
D4 = Servo de paso de cámara (anulado en el código de asesorplaza1)
D3 = Disparador de video (anulado en el código de asesorplaza1)
D2 = Disparador de foto  (anulado en el código de asesorplaza1)
Para la transmisión del video asesorplaza1 utilizara una Raspberry Pi 3 plus, una cámara USB, y el programa VCL Media Player

A7 = Conexión del divisor de voltaje
A6 = Pin de salida del sensor de temperatura TMP36 (se cambia este sensor por obsoleto, se usan los sensores DHT22)

Pines GND del bus i2c en los sensores MS5803-14BA y BMP180 a pines Nano GND Pines Vcc en los sensores MS5803-14BA y BMP180 a pines Nano 3.3V pines
SDA en los sensores MS5803-14BA y BMP180 a pines Nano A4 pines SCL en MS5803-14BA y BMP180 sensores para pin Nano A5
Se cambian estos sensores por obsoletos, se usan los sensores DHT22 y el giroscopio MPU6050

5V = Suministro al sensor de temperatura TMP36. (Se cambia este sensor por obsoleto, se usan los sensores DHT22)

Conexión serial de comunicaciones: modificado por Asesorplaza1, el 26/03/2020, para separar los datos mandados entre Arduinos, de los datos a mandar al Monitor serie
Conexión serial: 

Pin 19 Arduino de Control (TX) a Pin 18 Arduino ROV (RX) 
Pin 18 Arduino de Control (RX) a Pin 19 Arduino ROV (TX)
Conecte el GND en ambos

Tenga en cuenta que los ESC ya se habrán programado en este punto del proyecto.

Los datos de voltaje interno, rumbo, profundidad y temperatura interna se envían a través del enlace serie de regreso al maestro
Para su visualización en una pantalla LCD de 16x2.
La pantalla LCD de 16x2, se cambiara por una pantalla Nextion básica de 5"

El encabezado es de una brújula digital HMC5883L (dirección i2c 0x1E)
Y la profundidad de un sensor de alta presión MS5803-14BA (dirección i2c 0x76)
(Se cambia este sensor por obsoleto, se usa el giroscopio MPU 6050)

