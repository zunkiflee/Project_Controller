#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define SERVER_PORT 80;

const char* ssid = "Raspberry";
const char* password = "coepi156";

int SW_A = 1;

IPAddress server(192,168,1,100);
WiFiClient client;


void setup() {
     Serial.begin(19200);
     
     pinMode(D1,INPUT_PULLUP);

     WiFi.begin(ssid,password); //เชื่อมต่อ WiFi

     while(WiFi.status() != WL_CONNECTED) {
     delay(100);
     Serial.println(".");
     Serial.println("Connected to ");
     Serial.println(ssid);
     }

     Serial.println("IP Address");
     Serial.println(WiFi.localIP());
     delay(100);
}

void loop() {
   
     if(!digitalRead(D1)) {
      Serial.println("\n");
                 
      String str = "GET /qservice/qdpselect.php?dp=";
      str += SW_A;
      str += " HTTP/1.0";
         
      if (client.connect(server, 80)) {
        Serial.println("connected");
        client.println(st);
        Serial.println(st);
        client.println();
        delay(500);
   
      while(client.available()) {
        char c = client.read();
        Serial.print(c);
      }
        
      Serial.print("\n");
      Serial.print("---------------------------"); 
      Serial.print("\n");
      client.stop();
     
      }
        delay(500);
     }        
}
