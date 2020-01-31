#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>




/*********   Change this to control Light and Fan   *********/
char ssid[] = "WIFINAME"; // SSID of WiFi
char password[] = "WIFIPASSW"; // Password of WiFi
IPAddress ip(192, 168, 1, 80; // IP address of the server (this NodeMCU ESP8266)
//check the bottom of the file
#define RelayL 14 //Arduino Digital I/O pin number->Light
#define RelayF 12 //Arduino Digital I/O pin number->Fan





/*Hardware*/

byte led = 2;
int relayL = 1;
int relayF = 1;

/*Wifi*/

String AnswerStart = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";//Text before answer
String Answer = "";


/* Create an instance of the server */
WiFiServer server(80);     //Specify the port to listen on as an argument

IPAddress gateway(192,168,1,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

void setup() {        /*************  SETUP  *************/
  Serial.begin(115200); // only for debug
  pinMode(RelayL, OUTPUT);   //Set relay and blue light as outputs
  pinMode(RelayF, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(RelayL, 1);//To use normal swich
  digitalWrite(RelayF, 1);

  digitalWrite(led, 0);

  /* Connect to WiFi network */
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, password);             // connects to the WiFi router
  
  WiFi.mode(WIFI_STA);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) { //If not connected yet, reboot
    Serial.println("Connection Failed! Rebooting...");
    delay(2000); //Default was 5000
    ESP.restart();
  }
  
  server.begin();                                                    // Start the server
  Serial.println(""); //Message for testing (Serial)
  Serial.println("Connected to "); Serial.println(WiFi.SSID());
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
  Serial.println("Server started");
  digitalWrite(RelayL, 1);//To use normal swich
  digitalWrite(RelayF, 1);
}

void loop() {          /*************  LOOP  *************/
/* Server */  
  WiFiClient client = server.available();// Check if a client has connected
  if (!client) { //If not client, restart loop
    return;
  }
  Serial.println("New message from client");// Wait until the client sends some data
  while(!client.available()){
    delay(1);
  }
  String Message = client.readStringUntil('\r');// Read the first line of the request
  Serial.println(Message);
  client.flush();
  digitalWrite(led, 0);//start light blink
  /*
  Now that we have the message from the client, we need to do what the client wants us to do.
  To check the message we use Message.indexOf("/order"): 
      -If the message has that order, Message.indexOf("/order") is diferent than -1
      -If not found, Message.indexOf("/order") = -1
  This way, to set the light On with the order "L Set ON", we use "Message.indexOf("/L%20Set%20ON")!=-1"
  
  You may have noticed that we wrote some "%20" instead of " ". This is mandatory in order to send a message with ASCII
  http://www.asciitable.com/
  
  Note:
  0 = OFF
  1 = ON
  */
  if(Message.indexOf("/Whatsgoingon")!=-1){+
    Answer=String(relayL)+String(relayF);//if "Whatsgoingon" asked, answer with the state of the light and fan
  }
  else if (Message.indexOf("/L%20Set%20ON")!=-1){
    relayL = 1;
    Answer="L OFF";//respond the old state
  }
  else if (Message.indexOf("/F%20Set%20ON")!=-1){
    relayF = 1;
    Answer="F OFF";//respond the old state
  }
  else if (Message.indexOf("/L%20Set%20OFF")!=-1){
    relayL = 0;
    Answer="L ON";//respond the old state
  }
  else if (Message.indexOf("/F%20Set%20OFF")!=-1){
    relayF = 0;
    Answer="F ON";//respond the old state
  }
  else {//Recibed something not defined
    Serial.println("FAIL");
    client.stop();
    return;
  }
  delay(40);
  digitalWrite(led, 1);//end light blink
  digitalWrite(RelayL, relayL);//set the relay to the value (0 or 1)
  digitalWrite(RelayF, relayF);//set the relay to the value (0 or 1)
  client.flush();
  client.print(AnswerStart+Answer); //Send the response to the client
  Serial.println("Answer: "+AnswerStart+Answer); //show response in serial
  //function returns-> The client will be disconnected and 'client' object is detroyed
}

/*
Extra info:

For old ESP8266, the pins in real board:
D0 = 16;D1 = 5;D2 = 4;D3 = 0;D4 = 2;D5 = 14;D6 = 12;D7 = 13;D8 = 15;D9 = 3;D10 = 1;

Relay:
High level and low level of meaning:
High level trigger refers to the signal trigger end (IN) had a positive voltage and the negative pole
of the power supply, usually with the trigger end of a trigger connected with the positive pole of a 
power supply, when the trigger end has a positive voltage or to trigger voltage, the relay is attracted.
Low level trigger refers to the signal triggering voltage between the end and the negative electrode of 
the power supply is OV, or trigger terminal voltage lower voltage than the positive power supply voltage, 
low to can trigger, make the relay, is usually the cathode of the power supply and the triggering end of 
a trigger mode connection, so that the relay is attracted.*/

