#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WebServer.h>
const char* ssid = "Enter SSID here"; 
const char* password = "Enter password here";
 ESP8266WebServer server(80);
 
int firstpin=5; //D1
int secondpin=4; //D2
int thirdpin=0;  //D3
int fourthpin=14;  //D5
int fifthpin=12;  //D6
int sixthpin=13;  //D7  

  

uint8_t peer1[] = {0xC0, 0x49, 0xEF, 0xFA, 0x1B, 0x48};//write the reciever mac adress;

typedef struct message {
int first;
int second;
int third;
int fourth;
int fifth;
int sixth;
};
 
struct message myMessage;


 
void onSent(uint8_t *mac_addr, uint8_t sendStatus) {
 Serial.println("Status:");
 Serial.println(sendStatus);
 
 

 
}
 
void setup() {
 Serial.begin(115200);
 
 
 WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
 Serial.println(WiFi.localIP());
 server.on("/", handle_OnConnect);
 
 server.onNotFound(handle_NotFound);
 server.begin();
 
 // Get Mac Add
 Serial.print("Mac Address: ");
 Serial.print(WiFi.macAddress());
 Serial.println("ESP-Now Sender");
 
 
 // Serial.println("HTTP server started");

 
 // Initializing the ESP-NOW
 if (esp_now_init() != 0) {
   Serial.println("Problem during ESP-NOW init");
   return;
 }
 
 esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
 // Register the peer
 Serial.println("Registering a peer");
 esp_now_add_peer(peer1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
 Serial.println("Registering send callback function");


esp_now_register_send_cb(onSent);


}
 
void loop() {
  myMessage.first = digitalRead(firstpin);
  myMessage.second = digitalRead(secondpin);
  myMessage.third = digitalRead(thirdpin);
  myMessage.fourth = digitalRead(fourthpin);
  myMessage.fifth = digitalRead(fifthpin);
  myMessage.sixth = digitalRead(sixthpin);
 
 
 Serial.println("Send a new message");
 

 esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));

   
  
 
 delay(15000);
 

 
server.handleClient();
 
} 
void handle_OnConnect() {
int firs = digitalRead(firstpin);
int secon = digitalRead(secondpin);
int thir = digitalRead(thirdpin);
int fort = digitalRead(fourthpin);
int fift = digitalRead(fifthpin);
int sixt = digitalRead(sixthpin);


 // Gets the values of the humidity ,
  server.send(200, "text/html", SendHTML( firs, secon, thir, fort, fift, sixt)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}         
String SendHTML(int firs,int secon, int thir, int fort, int fift, int sixt){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>PARKING LOT</h1>\n";
  ptr +="<p>1 MEANS SPACE AVAILABLE";
  ptr +="<p>0 MEANS SPACE FILLED";
  
  ptr +="<p>first: ";
  ptr +=(int)firs;
  ptr +="<p>second: ";
  ptr +=(int)secon;
  ptr +="<p>Third: ";
  ptr +=(int)thir;
  ptr +="<p>forth: ";
  ptr +=(int)fort;
  ptr +="<p>fifth: ";
  ptr +=(int)fift;
  ptr +="<p>sixth: ";
  ptr +=(int)sixt;

  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
