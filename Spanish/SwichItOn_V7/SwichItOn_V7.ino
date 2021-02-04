#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>




/*********   Cambiar esto para controlar la luz y el ventilador   *********/
char ssid[] = "WIFINAME"; // SSID de la WiFi
char password[] = "WIFIPASSW"; // Contraseña de la WiFi
IPAddress ip(192, 168, 1, 80); // Dirección IP del servidor (Esta placa NodeMCU ESP8266)
//Revisa el final del archivo
#define RelayL 14 //Arduino Digital I/O pin number -> Luz
#define RelayF 12 //Arduino Digital I/O pin number -> Ventilador





/*Hardware*/

byte led = 2;
int relayL = 1;
int relayF = 1;

/*Wifi*/

String AnswerStart = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";//Texto antes del mensaje
String Answer = "";


/* Crear una instancia para el servidor */
WiFiServer server(80);     //Especifica el puerto de escucha como un argumento

IPAddress gateway(192,168,1,1);           // gateway de la red
IPAddress subnet(255,255,255,0);          // subnet mask de la red

void setup() {        /*************  SETUP  *************/
  Serial.begin(115200); // Sólo para pruebas
  pinMode(RelayL, OUTPUT);   //Definir la luz y el ventilador como outputs
  pinMode(RelayF, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(RelayL, 1);//Para poder usar los interruptores ya instalados en el lugar con normalidad
  digitalWrite(RelayF, 1);

  digitalWrite(led, 0);

  /* Conectar a la WIFI */
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);       // Fuerza a que se le defina los parámetros asignados
  WiFi.begin(ssid, password);             // conectar al router
  
  WiFi.mode(WIFI_STA);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) { //Si no consigue conectar, reinicia
    Serial.println("Conexión fallida! Reiniciando...");
    delay(2000); //Por defecto era 5000
    ESP.restart();
  }
  
  server.begin();                                                    // Inicia el servidor
  Serial.println(""); //Message for testing (Serial)
  Serial.println("Conectado a "); Serial.println(WiFi.SSID());
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Señal: "); Serial.println(WiFi.RSSI());
  Serial.print("Redes: "); Serial.println(WiFi.scanNetworks());
  Serial.println("Servidor iniciado");
  digitalWrite(RelayL, 1);//Para usar los enchufes de la red local de manera normal
  digitalWrite(RelayF, 1);
}

void loop() {          /*************  Bucle  *************/
/* Servidor */  
  WiFiClient client = server.available();// Comprobar si algún cliente se ha conectado
  if (!client) { //Si no cliente, reinicia
    return;
  }
  Serial.println("Nuevo mensaje de un cliente!");// Espera a que este envie algo
  while(!client.available()){
    delay(1);
  }
  String Message = client.readStringUntil('\r');// Lee la primera línea del mensaje
  Serial.println(Message);
  client.flush();
  digitalWrite(led, 0);//inicia parpadeo del led de control
  /*
  Una vez tenemos el mensaje del cliente, procesamos la orden.
  Para ello, hacemos uso de Message.indexOf("/orden"):
      -Si el mensaje contiene esa orden, tenemos un valor distinto a -1
      -Si no lo encuentra, tendremos -1
  De esta manera, para pedir encender la luz, usamos "Message.indexOf("Message.indexOf("/L%20Set%20ON")!=-1"

  Es posible que te hayas dado cuenta el uso de "%20" en vez de espacios. Esto es necesario para mandar el mensaje mediante ASCII
  http://www.asciitable.com/

  Nota:
  0 = OFF
  1 = ON
  */
  if(Message.indexOf("/Whatsgoingon")!=-1){
    Answer=String(relayL)+String(relayF);//Si "Whatsgoingon" pedido, responde con el valor actual de la luz y el ventilador
  }
  else if (Message.indexOf("/L%20Set%20ON")!=-1){
    relayL = 1;
    Answer="L OFF";//Responde el anterior estado
  }
  else if (Message.indexOf("/F%20Set%20ON")!=-1){
    relayF = 1;
    Answer="F OFF";//Responde el anterior estado
  }
  else if (Message.indexOf("/L%20Set%20OFF")!=-1){
    relayL = 0;
    Answer="L ON";//Responde el anterior estado
  }
  else if (Message.indexOf("/F%20Set%20OFF")!=-1){
    relayF = 0;
    Answer="F ON";//Responde el anterior estado
  }
  else {//Si recibe algo no definido
    Serial.println("Fallo");
    client.stop();
    return;
  }
  delay(40);
  digitalWrite(led, 1);//Finaliza el parpadeo del led de control
  digitalWrite(RelayL, relayL);//Establece el valor del relé (0 o 1)
  digitalWrite(RelayF, relayF);//Establece el valor del relé (0 o 1)
  client.flush();
  client.print(AnswerStart+Answer); //Responde al cliente
  Serial.println("Answer: "+AnswerStart+Answer); //enseña la respuesta en el puerto serie
  //función return-> El cliente se desconectará y el objeto cliente se destruirá
}

/*
Info extra:

Para antiguas ESP8266, los pines de la placa:
D0 = 16;D1 = 5;D2 = 4;D3 = 0;D4 = 2;D5 = 14;D6 = 12;D7 = 13;D8 = 15;D9 = 3;D10 = 1;


Significado de relé de alto y bajo nivel (inglés):
High level trigger refers to the signal trigger end (IN) had a positive voltage and the negative pole
of the power supply, usually with the trigger end of a trigger connected with the positive pole of a 
power supply, when the trigger end has a positive voltage or to trigger voltage, the relay is attracted.
Low level trigger refers to the signal triggering voltage between the end and the negative electrode of 
the power supply is OV, or trigger terminal voltage lower voltage than the positive power supply voltage, 
low to can trigger, make the relay, is usually the cathode of the power supply and the triggering end of 
a trigger mode connection, so that the relay is attracted.*/
