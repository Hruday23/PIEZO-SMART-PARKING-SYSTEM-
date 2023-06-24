#include <LiquidCrystal_I2C.h>

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
typedef struct message {
  int first;
  int second;
  int third;
  int forth;
  int fifth;
  int sixth;
};
 
struct message myMessage;
//uint8_t is unsigned integer of 8bit. 
void onDataReceiver(const uint8_t * mac, const uint8_t *incomingData, int len) {
  //Serial.println("Message received.");

 memcpy(&myMessage, incomingData, sizeof(myMessage));
 lcd.clear();

/*Serial.print("slot1=" +String(myMessage.first)); //1=empty 0=filled.
 Serial.print("slot2=" +String(myMessage.second));
  Serial.print("slot3=" +String(myMessage.third)); //1=empty 0=filled.
 Serial.print("slot4=" +String(myMessage.forth));
  Serial.print("slot5=" +String(myMessage.fifth)); //1=empty 0=filled.
 Serial.print("slot6=" +String(myMessage.sixth));*/
 


 //if 1is empty and 2 is filed print 1
 // if both are filled print no slots are emnptty
 //if both are empty print 1, 2    
 /*if(myMessage.first==0 && myMessage.second==0)
        Serial.println("No empty slots");
 else if(myMessage.first==1 && myMessage.second==1)
        Serial.println("slot 1 and slot 2 are empty");
 else if(myMessage.first==1 && myMessage.second==0)
        Serial.println("slot 1 is empty");
 else if(myMessage.first==0 && myMessage.second==1)
        Serial.println("slot 2 is empty");*/
    int n=10;
    lcd.print("slot:");
        for(int i=1;i<n;i++)
        {
           
          if(i==1)
          {
            if(myMessage.first==0)
            {
              
              lcd.print(" ");
            }
            else 
           // Serial.print("1,");
            lcd.print("1");
          }
          else if(i==2)
          {
            if(myMessage.second==0)
            {
              //Serial.print(" ,");
              lcd.print(" ");
            }
            else 
            //Serial.print("2,");
            lcd.print("2");
          }
          else if (i==3)
          {
            if(myMessage.third==0)
            {
              //Serial.print(" ,");
              lcd.print(" ");
            }
            else 
            //Serial.print("3,");
            lcd.print("3");
          }
          else if(i==4)
          {
            if(myMessage.forth==0)
            {
              //Serial.print(" ,");
              lcd.print(" ");
            }
            else 
            //Serial.print("4,");
            lcd.print("4");
          } 
          else if(i==5)
          {
            if(myMessage.fifth==0)
            {
              //Serial.print(" ,");
              lcd.print(" ");
            }
            else 
             //Serial.print("5,");
             lcd.print("5");
          }   
          else if(i==6)
          {
            if(myMessage.sixth==0)
            {
             // Serial.print(" ,");
              lcd.print(" ");
            }
            else
           // Serial.print("6,");
            lcd.print("6");
          }                          
        }
 
}
 
void setup() {
 //Serial.begin(115200);
  lcd.begin();
  lcd.backlight();

 WiFi.mode(WIFI_STA);//wifi-sta = wifi station.
 //Serial.print("Mac Address: ");
 //Serial.print(WiFi.macAddress());
 //Serial.println("ESP32 ESP-Now Broadcast");
 if (esp_now_init() != 0) {
   //Serial.println("Problem during ESP-NOW init");
   return;
 }
 esp_now_register_recv_cb(onDataReceiver);//to register recieving call back function.
}

 

 
void loop() {
 
  
}