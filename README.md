
Modificado por asesorplaza1 en las diferentes fechas indicadas
Las primeras pruebas y cambios del código, se iniciaron en 2.016, debido a la cantidad de modificaciones.
A partir de ahora 30/01/2020, se ponen las fechas y los cambios en la descripción del proyecto para facilitar la búsqueda de errores en los diferentes cambios del código.

30/01/2020 ya se han comentado todas las líneas de control de la cámara y del LCD
Le añado 2 DHT22 y así estarán los 3 que me hacen falta
He borrado varias líneas de control de la cámara que no se va a utilizar

01/02/2020 Le añado los controles del giroscopio facilitados por Dea de www.cambatronics.com

2/02/2020 No hace falta modificar nada porque ya viene desde el Esclavo solo 1 lectura del sensor X segundo

04/02/2020 Modifico las líneas de lectura de los sensores, porque hasta ahora solo me imprime en Monitor Serie el texto, no los datos

06/02/2020 Se depura un poco el código, y se modifica el encabezado del código

08/02/2020 Se corrige el error de lectura en los sensores, y se corrige la escritura del Monitor Serie

12/02/2020 Para poder añadir cualquier código hay que seguir unas reglas especificas de programación
Se modifica la estructura del código siguiendo esas órdenes de programación, según la información obtenida y guardada en la carpeta 01_UNIR_2_CODIGOS
Se crean varios bloques en el void loop, para el funcionamiento de cada uno de los sensores, eliminando los delay()
Se añade el sensor de distancia infrarrojo E18-D80NK, sin errores

13/02/2020 Se incluye la lectura del sensor de temperatura DS18B20

16/02/2020  Se añade la lectura del sensor de distancia infrarrojo E18-D80NK, sin errores y consigo adaptar un código para leer el sensor de presión SKU237545

08/03/2020 Se conecta un relé en el pin 12 del Arduino Esclavo, para encender los focos de luz externos, no hace falta cambiar el código.

26/03/2020 Se arregla el envío de datos, separando los datos del Monitor Serie, y los datos que hay que enviar al Arduino Maestro, iniciando dos puertos serie con las órdenes

Serial.begin(57600);     // Puerto Serie USB

Serial1.begin(57600);    // Puerto Serie en los pines 18 y 19

ETin.begin(details(rxdata), &Serial1);    // Comienza la recepción de datos a través de Serial, en los pines 18 y 19

ETout.begin(details(txdata), &Serial1);   // Comienza el envío de datos a través de Serial, en los pines 18 y 19

En el Esclavo se incluye una librería específica para el giroscopio MPU6050

28/03/2020 Se incluyen el envío de todas las instrucciones del mando, para tener todos los botones operativos

03/04/2020 Se incluye la parte nueva del Giroscopio MPU6050, que muestra los 3 ejes de inclinación, más la temperatura del Giroscopio y se arreglan y ordenan los Serial.print

11/04/2020 Corrijo el código según las instrucciones de mi amigo Atilano Belinchón

13/04/2020 Corrijo las lecturas y envío de datos del sensor de infrarrojos E18D80NK

18/04/2020 Se cambian algunos " if ", por " else if ", para darle agilidad al código

Entre el día 24/03/2020 y el día 28/04/2020, se hacen varios cambios en el código para mejorarlo y conseguir que el mando funcione, siguiendo las instrucciones de Bigbadbob en las publicaciones del foro http://www.homebuiltrovs.com/rovforum/viewtopic.php?f=18&t=1908 a partir de la página 4

28/04/2020 Se corrige la ortografía de todo el texto que no son órdenes

03/05/2020 Se cambian las asignaciones de los pines, según el código de Github

Las nuevas asignaciones de pines son:

Salida de 3.3V a PIN rojo PS2
Pin 24 a PIN amarillo PS2 + resistencia 1k
Pin 23 a PIN naranja PS2
Pin 25 a PIN marrón PS2 + resistencia 1k
Pin 22 a PIN azul PS2

Se arregla el código para que me salga en el Maestro el estado de los focos, encendidos / apagados.

04/05/2020 Se depura el código según los consejos de Bigbadbob de http://www.homebuiltrov.com

05/05/2020 Se incluye la Macro F, en todos los Serial.print, para reducir el consumo de memoria dinámica según los consejos de Bigbadbob de http://www.homebuiltrov.com , pero me da problemas

06/05/2020 Se depura el código para un mejor funcionamiento, según los consejos de Bigbadbob de http://www.homebuiltrov.com y siguen los problemas con la Macro F

07/05/2020 Se depura el código para un mejor funcionamiento, según los consejos de Bigbadbob de http://www.homebuiltrov.com y siguen los problemas con la Macro F

08/05/2020 Se corrigen los problemas de la Macro F, en todos los Serial.print de texto fijo
No se puede poner la Macro F, a los Serial.print de datos de los sensores y se consigue reducir el consumo de memoria dinámica considerablemente

09/05/2020 Se siguen corrigiendo líneas para la depuración del código, según los consejos de Bigbadbob de http://www.homebuiltrov.com pero siguen los problemas con el mando de la PS2

10/05/2020 Me doy cuenta de un error en la orden de encender los focos y lo corrijo, pero el mando sigue sin funcionar como es debido

11/05/2020 Se modifican varias órdenes del control de los botones, pero el mando sigue sin funcionar correctamente

16/05/2020 Se hacen diversos cambios, según los consejos de Tsanshon de www.foromodelismonaval.es , pero siguen los problemas con el mando.

20/05/2020, Instalo el programa Atom más el complemento Platform IO, para poder depurar los errores del código, y leyendo en la página oficial de Platfom IO, me entero de que ya no dan soporte para la plataforma Atom.

25/05/2020 Sigo leyendo en la página de Platform IO, e instalo el programa Visual Studio Code más el complemento Platform IO, para poder depurar el código.
Me registro en la página oficial de Platform IO, y después de intercambiar algunos mensajes con Maxgerhardt, y dejar la conversación en pausa, como pasa siempre, te dan una bienvenida aceptable, pero no te ayudan lo suficiente, lo dejo por imposible, me aconsejan cambiar de placa y compro unos ESP32, placa más potente que Arduino, pero para poder depurar el código y poder observar el comportamiento del programa hace falta una serie de conexiones y soldar varios pines, cosa que no me convence.

30/05/2020 Consigo depurar el código con Visual Studio Code, pero no consigo nada, después de mucho probar ye instalar todas las bibliotecas necesarias con el nuevo formato.

01/07/2020 Después de una pausa por trabajo, y arto de no progresar nada, desinstalo Visual Studio Code, y vuelvo al Arduino IDE.

02/07/2020 Buscando programas de ROV en Github, encuentro uno que parece interesante el programa del ROV Caribbean, que además de utilizar el mando de la PS2, utiliza también los módulos de Comunicación Serie RS485, a ver que puedo sacar de provecho de este programa.





  La versión original tomada como punto de partida es la siguiente

  ROVPS2Control_Master8.ino
  Hamish Trolove - 30 de marzo de 2016
  www.techmonkeybusiness.com

  Y toma comandos de control de un mando PS2 y transmite los
  Comandos que utilizan la Biblioteca EasyTransfer de Bill Porter en un serial de 9600 baudios
  Enlace (100m de cable).

  Este boceto está diseñado para un Arduino Nano con un solo puerto serie.

  Aunque yo lo estoy usando en un Mega 2560 y funcionaba, hasta que empecé a introducir sensores.

  Para la transmisión del video asesorplaza1 utilizara una Raspberry Pi 3 plus, una cámara USB, y el programa VCL Media Player
  Indicador de luces principales de Pin D4 a LED
  Sensor D5 a LED ROV Batería De bajo voltaje Advertencia
  Pin D6 a LED ROV Advertencia interior de alta temperatura

  Comunicaciones cambiado por Asesorplaza1, el 26/03/2020, para separar los datos que se envían de un Arduino a otro, de los datos del Monitor Serie

  Conexión serie: Parte superior 19 (TX) a ROV 18 (RX)
  Conexión serie: Parte superior 18 (RX) a ROV 19 (TX)
  Conecte el GND en ambos

  La pantalla LCD de 16x2, se cambiara por una pantalla Nextion básica de 5"

  La codificación tira de la biblioteca PSX desarrollada por Bill Porter.
  Vea www.billporter.info para consultar lo último de Bill Porter y descargar las bibliotecas.

  Los controles para el ROV son;
  Stick Derecho - Eje X - Movimiento, Adelante / Atras
  Stick Derecho - Eje Y - Movimiento, Derecha / Izquierda
  Botón R1 movimiento arriba
  Botón R2 movimiento abajo
  Botón Izquierda - Izquierda, interruptor de encendido/apagado de Focos Externos


El software se proporciona “tal cual”, sin ningún tipo de garantía ni expresa ni implícita, incluyendo las garantías comerciales. Solo para uso particular NUNCA comercial. En ningún caso el autor se responsabiliza de ningún tipo de daño derivado del uso del programa.


