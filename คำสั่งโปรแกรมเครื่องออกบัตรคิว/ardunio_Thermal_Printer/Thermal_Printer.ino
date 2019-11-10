#include "Adafruit_Thermal.h" //อ้างอิงไฟล์  Adafruit_Thermal.h, SoftwareSerial.h
#include "SoftwareSerial.h"
#include <SoftwareSerial.h>

SoftwareSerial ArduinoSerial(2, 3); //กำหนดขา Tx, Rx ต่อกับ nodeMCU เพื่อรับค่าจาก nodeMCU  

#define TX_PIN 5  //กำหนดขา  PIN 5 ค่าคงที่ทำหน้าที่รับข้อมูล (Tx) PIN 6 ค่าคงที่ทำหน้าที่ส่งข้อมูล (Rx) ต่อกับ Thermal Printer
#define RX_PIN 6    
                
SoftwareSerial mySerial(RX_PIN, TX_PIN);
Adafruit_Thermal printer(&mySerial);

// รับค่า ลำดับคิว และ แผนกจาก nodeMCU
int i_data; 
int x_data;


void setup() {
  
  mySerial.begin(19200);
  printer.begin();
  pinMode(2,INPUT);   //กำหนดขา 2 ทำหน้าที่ Input
  pinMode(3,OUTPUT);  //กำหนดขา 3 ทำหน้าที่ Output
  Serial.begin(19200);
  ArduinoSerial.begin(19200);  
}

void loop() {
  
  while (ArduinoSerial.available() > 0) {   
    int i_data = ArduinoSerial.parseInt();      
    int x_data = ArduinoSerial.parseInt();  
        
    if (ArduinoSerial.read() > 0) {                   
      Serial.print("Arduino or Thermal Printer"); Serial.print(" : ");   
      Serial.print(i_data); Serial.print(" : ");     
      Serial.println(x_data);                           
      printer.justify('C');                                     
      printer.boldOn();                                       
      printer.setSize('L');              
      printer.print(F("Number = "));                       
      printer.println(i_data); 
                                 
      if (x_data == 1) {                                           
        printer.println("1");                                    
      } else if (x_data == 2) {                                     
        printer.println("2");                                    
      } else if (x_data == 3) {
        printer.println("3");
      } else if (x_data == 4) {
        printer.println("4"); 
      } 
  
     printer.boldOff();
     printer.feed(5);
     printer.sleep();      
     delay(1000L);         
     printer.wake();    
      printer.setDefault(); 
    }
    delay(1000);
 }
}
    
 
