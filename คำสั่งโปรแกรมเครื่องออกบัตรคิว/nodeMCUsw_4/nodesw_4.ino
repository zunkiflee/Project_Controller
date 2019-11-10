#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define SERVER_PORT 80;

const char* ssid = "Raspberry";
const char* password = "coepi156";

IPAddress server(192,168,1,100);
 
SoftwareSerial NodeSerial(D3, D2); // RX | TX port ส่งข้อมูลไปยัง nodeMCU

String c ;
String data_q ;
String data_a ; 
String qstr ; 
int qint; // ตัวแปรแปลงเป็น Int
int sum2; //

int qa_data;
int qb_data;
int qc_data;
int qd_data;
int i_data; // ตัวแปร x_data สำหรับเก็บค่าลำดับคิว(แผนก)

// ตัวแปร A_data-D_data สำหรับแทน Switch ปุ่มกดมี 4 แผนก
int A_data = 1;
int B_data = 2;
int C_data = 3;
int D_data = 4;

// ตัวแปร x_data ไว้รอค่าจากตัวแปร A_data-D_data เมื่อมีการกดปุ่ม (แผนก)
int x_data;

// Function สำหรับตรวจสอบลำดับคิว
int senddp();

// Function ทำการส่งค่าไปบันทึก Database
void send_qdp(int x_data,int i_data);

WiFiClient client;

void setup() {
     
     // กำหนดขา D1, D5, D6, D7 ทำหน้าที่ Input เชื่อมต่อกับปุ่มกด   
     pinMode(D1,INPUT_PULLUP); //Button 1 แผนกที่1
     pinMode(D5,INPUT_PULLUP); //Button 2 แผนกที่2
     pinMode(D6,INPUT_PULLUP); //Button 3 แผนกที่3
     pinMode(D7,INPUT_PULLUP); //Button 4 แผนกที่4

     pinMode(D3,INPUT); // กำหนดขา D3 ทำหน้าที่ Input 
     pinMode(D2,OUTPUT); // กำหนดขา D2 ทำหน้าที่ Output 
     
     Serial.begin(19200);
     
     NodeSerial.begin(19200); 
     
     Serial.begin(19200);
     delay(10); 
     
     WiFi.begin(ssid,password);             ////////////////////////////////////
     while(WiFi.status() != WL_CONNECTED){  //                                //
     delay(500);                            //                                //
     Serial.println(".");                   //                                //
     Serial.println("Connected to ");       //          เชื่อมต่อเครือข่ายไร้สาย    //
     Serial.println(ssid);                  //                                //
     }                                      //                                //
     Serial.println("IP Address");          //                                //
     Serial.println(WiFi.localIP());        //                                //
     delay(100);                           ////////////////////////////////////
     
     
}
     
void loop() { 
  
  if(!digitalRead(D1)) {

    /* ตรวจสอบสถานะการกดปุ่มให้ทำงานโดยมีค่าคือ 1 ทำการส่งค่า 1 ไปยังฟังก์ชัน int sum = senddp(); ตรวจสอบค่าลำดับคิว 
       ซึ่งส่งค่าลำดับคิวกลับมา จากนั้นส่งค่าแผนกและลำดับคิวไปยังบอร์ดอาดุยโน่ที่เชื่อมต่อเครื่องพิมพ์ใบเสร็จแบบเทอร์มอลทำการออก
       บัตรคิวส่งค่าแผนกและลำดับคิวไปยังฟังก์ชัน send_qdp(i_data,x_data) เพื่อทำการบันทึกลงในฐานข้อมูล*/
  
    Serial.print("\n");
    x_data = A_data; // ให้ x_data มีค่า 1 เพราะ A_data เก็บค่า 1 
    Serial.println(x_data);Serial.print("\t"); // แสดงค่าแผนก 1 
    Serial.print("\n");
        
    int sum = senddp(); // ฟังชั่น ส่งค่าแผนก 1 ไปยังฐานข้อมูลเพื่อเช็คค่าคิวล่าสุด
        
    x_data = A_data; 
    Serial.print("\n");
    Serial.print("Sum = "); 
    Serial.print(sum);
    qa_data = sum;
    i_data = qa_data;
    Serial.print("\n");
    Serial.println(x_data);Serial.println(i_data); Serial.print("\t");
    Serial.print("\n");
        
    NodeSerial.print(i_data); NodeSerial.print(" "); // ส่งค่าแผนก1ไปยังอาดูโน่
    NodeSerial.print(x_data); NodeSerial.print("\n"); // ส่งค่าคิวล่าสุดไปยังอาดูโน่

    send_qdp(i_data, x_data); // นำค่าคิวและค่าแผนกที่เป็น Int ไปเก็บใน database
        
    delay(100);
        
}

  if(!digitalRead(D5)) {
    Serial.print("\n");
    x_data = B_data;
    Serial.println(x_data); Serial.print("\t");
    Serial.print("\n");
        
    int sum = senddp();
        
    x_data=B_data;
    Serial.print("\n");
    Serial.print("Sum = ");
    Serial.print(sum);
    qb_data = sum;
    i_data = qb_data;
        
    Serial.print("\n\n");
    Serial.println(x_data); Serial.println(i_data); Serial.print("\t");
    Serial.print("\n");
        
    NodeSerial.print(i_data); NodeSerial.print(" ");
    NodeSerial.print(x_data); NodeSerial.print("\n");

    send_qdp(i_data, x_data); // นำค่าคิวและค่าแผนกที่เป็น Int ไปเก็บใน database
         
    delay(100);
}

  if(!digitalRead(D6)) {

    Serial.print("\n");   
    x_data = C_data;
    Serial.println(x_data); Serial.print("\t");
    Serial.print("\n");
        
    int sum = senddp();
        
    x_data = C_data;
    Serial.print("\n");
    Serial.print("Sum = ");
    Serial.print(sum);
    qc_data = sum;
    i_data = qc_data;
    Serial.print("\n");
    Serial.println(x_data); Serial.println(i_data); Serial.print("\t");
    Serial.print("\n");
        
    NodeSerial.print(i_data); NodeSerial.print(" ");
    NodeSerial.print(x_data); NodeSerial.print("\n");

    send_qdp(i_data, x_data); // นำค่าคิวและค่าแผนกที่เป็น Int ไปเก็บใน database
         
    delay(100);
        
}

  if(!digitalRead(D7)) {
    Serial.print("\n");
    x_data = D_data;
    Serial.println(x_data); Serial.print("\t");
    Serial.print("\n");
        
    int sum = senddp();
        
    x_data = D_data;
    Serial.print("\n");
    Serial.print("Sum = ");
    Serial.print(sum);
    qd_data = sum;
    i_data = qd_data;
    Serial.print("\n");
    Serial.println(x_data); Serial.println(i_data); Serial.print("\t");
    Serial.print("\n");
        
    NodeSerial.print(i_data); NodeSerial.print(" ");
    NodeSerial.print(x_data); NodeSerial.print("\n");
   
    send_qdp(i_data, x_data); // นำค่าคิวและค่าแผนกที่เป็น Int ไปเก็บใน database
        
    delay(100);
   
   }
   
 }

int senddp() {

  String  str = "GET /qservice/qselect.php?dp=";
          str += x_data;
          str += " HTTP/1.0";
                
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println(str);
    Serial.println(str);
    client.println();
    delay(1000);
           
    char g ='0'; 
    
    while(client.available() > 0) {
      c = client.readStringUntil('\r');
     
      // ทำการดักค่าว่างจากเซิร์ฟเวอร์ที่ Response เพื่อนำค่าชนิด char ส่งจากจากเซิร์ฟเวอร์นำไปใช้โดยค่า c เท่ากับค่าว่าง 
      if (c == " ") {
        g = '1';
      }
      
       if((g == '1'))Serial.print(c); 
        data_q  = c;
        data_a = data_q ; // นำ a ไปแปลงเป็น Int หลังจากเงื่อนไขติดต่อกับ Server
      }
      
    Serial.print(data_q);
    Serial.print("\n");
    Serial.print("---------------------------"); 
    Serial.print("\n");
    client.stop(); 
  } 
     
   Serial.print(data_a);
   qstr = data_a ; // a เก็บค่าคิวที่เป็นชนิด char ส่วน qst เก็บค่าคิวที่เป็นขนิดสตริงเพื่อนำไปแปลง
   qint = qstr.toInt(); // แปลงค่า qstr ที่เก็บค่าคิวเป็นชนิดสตริงแปลงเป็น Int
   Serial.print("\n");
   Serial.print("int = ");
   Serial.print(qint);
   Serial.print("\n");
   Serial.print("---------------------------"); 
     
   sum_2 = qint; //sum เก็บค่าคิวที่แปลงเป็น Int เพื่อที่จะส่งค่ากลับไปยังฟังชัน void loop
   return sum_2; 
    
}
 
void send_qdp(int i_data, int x_data) {

  /* ส่งค่า i_data(คิว), int x_data(แผนก) ไปยังเว็บเซิร์ฟเวอรเพื่อทำการบันทึกลงฐานข้อมูล */  

  String str = "GET /qservice/qadd.php?qa=";
         str += i_data;
         str += "&dp=";  
         str += x_data;
         str += " HTTP/1.0";
         
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println(str);
    Serial.println(str);
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
   delay(200);
}
