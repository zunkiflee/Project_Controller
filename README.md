# Project_Controller
ปริญญานิพนธ์ เครื่องระบบออกบัตรคิว กรณีศึกษาโรงพยาบาลสะเดา

#ในส่วนไฟล์ทั้งหมดเป็นส่วนของ Controller อุปกรณ์ที่ใช้บอร์ด Arduino, nodeMCU version 2, Thermal Printer และ Raspberry pi 3(Server)

#คำสั่งโปรแกรมเครื่องออกบัตรคิว แบ่ง 2 ส่วน ส่วนแรก Arduino เชื่อมต่อกับ Thermal Printer ทำหน้าที่ปริ้นใบแสดงผลลำดับคิวและแผนกและเชื่อมต่อกับ nodeMCU 
 ส่วนที่สอง nodeMCU version 2 ต่อกับ Switch ปุ่มกดแต่ละแผนกและบอร์ด nodeMCU เชื่อมต่อบอร์ด Arduino เมื่อทำการกดปุ่มแต่ละแผนก ในส่วนบอร์ด nodeMCU
 ทำกระบวนการเช็คลำดับคิวแต่ละแผนที่กดเข้ามา ซึ่งเช็คใน Database จาก Server
