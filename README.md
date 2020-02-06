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

*Note:* From left to right:
 
 -Transformer: fuels the board and the relay. The conection to the board can be made through USB.
 
 -Relay: Acts as a switch controled by the board. The board-relay's connection is achieved joing the output of the board with the S input (Switch). There is an option to fed this component directly from the board, but keep in mind that sometimes the relay requires more voltage than the board can provide.
 
 -Board: processes and executes the communication with the client (us) using WIFI and triggers the "switch". 


![eg](https://github.com/Jkutkut/SwitchItON/blob/master/imgs/example.png)


Notes:
  
  -The order on the relay's inputs may vary. Keep in mind:
    
    -GND = Ground = "-"
    
    -VCC = AC Voltage = Positive = "+" (Normally: 5V, 3.3V)
    
    -S = Switch

  -Most electric devices can be connected this way. In this example, a light and a fan are available to control.
  
  -**Warning**: on the assembly proccess, there's the risk to suffer a severe electric shock. Take the precautions necessary.  
  
### Enjoy the DIY domotic!
