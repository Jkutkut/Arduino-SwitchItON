# SwitchItON

*This project is avalive in English and Spanish.*

*Este proyecto está disponible tanto en inglés como en español.*

## English:

This application enables us to control any electric device using a device with internet connection.

**Materials**

- Nodemcu ESP8266 board:
![ESP8266](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/esp8266.png)

- Relay for Arduino (3 inputs: Vcc, Gnd and S):
![Relé](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/relay.png)

- Cable for the electric connections.

- Gaine thermoretractable or isolation for the connections.

- AC to 5V DC transformer (e.g. phone charger, in order to fuel the board).

- Security measures (This project uses +220V on AC).

***Turorial:***
- Install Arduino IDE on your PC.

- [GET ARDUINO READY FOR THE BOARD](https://www.youtube.com/watch?v=p06NNRq5NTU).

- Download the code for the board (SwitchItON_V*x*.ino).

- Change the parametres needed (see comments on the file).

- Upload the code to the board.

- Import the AppInventor 2 application (SwitchItON_V*x*.aia) and custom it.

- Install the app on a AppInventor compatible device.

- Assemble the circuit:
![wiring](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/wiring.png)

---------------------------------------------------------------------------------------------------------------------


## Español:

Esta aplicación domótica nos permite controlar mediante cualquier dispositivo con conexión a internet cualquier aparato eléctrico. 

**Materiales**

- Placa Nodemcu ESP8266:
![ESP8266](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/esp8266.png)

- Relé para arduino (tiene 3 entradas: Vcc, Gnd y S):
![Relé](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/relay.png)

- Cable para hacer las conexiones.
- Plástico termoretráctil o aislante para las conexiones.
- Transformador de corriente alterna a continua 5V (Como un cargador de móvil, para alimentar la placa).
- Medidas de seguridad (Estaremos manejando corriente alterna a 220V).

**Pasos a seguir:**

- Instalar Arduino IDE en el ordenador.

- [PREPARAR ARDUINO PARA LA PLACA](https://www.youtube.com/watch?v=0g7sazWXfEI).

- Descargar el programa para la placa (SwitchItON_V*x*.ino).

- Cambiar los parámetros necesarios (Ver comentarios en el archivo).

- Cargar el programa en la placa.

- Importar en AppInventor 2 la aplicación (SwitchItON_V*x*.aia) y personalizar al gusto.

- Instalar la aplicación en un dispositivo compatible con AppInventor.

- Montar el circuito:

![conexiones](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/wiring.png)

*Nota:* De izquierda a derecha:
 
  -Transformador: alimenta a la placa y al relé. La conexión con la placa se puede hacer mediante USB.

  -Relé: Actúa como interruptor gracias a placa. La conexión Placa-Relé se realiza conectando la salida de la placa digital con la entrada S (de Switch). También se puede alimentar este componente directamente desde la placa pero cuidado porque a veces necesitamos más voltaje del que nos ofrece la placa.
  -Placa: realiza toda la comunicación con el cliente (Nosotros) mediante WIFI y acciona el “interruptor”.

![ejemplo](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/example.png)


Nota:

  -El orden de las entradas del Relé pueden variar. Tener en cuenta que:
    
    -GND = Ground = Tierra = “-”.
    
    -Vcc = Voltaje en continua = Positivo = “+” (Será 5V o 3,3V seguramente).
    
    -S = Switch = Interruptor (Donde se conecta la salida digital de la placa).

  -Realmente se puede conectar cualquier dispositivo que requiera electricidad para funcionar. En el programa vienen definidos 2 elementos a controlar: una luz (Light) y un ventilador (Fan).
  
  -**Cuidado**: En el momento de conectar una de las entradas de corriente a nuestro “Interruptor”, tener cuenta que se corre el peligro de sufrir una descarga severa. Tomar las medidas oportunas.



### Y ahora… a disfrutar de la domótica en casa!
