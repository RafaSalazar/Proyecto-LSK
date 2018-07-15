// LSK MOTO DEVICE SLAVE
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 6); // RX, TX
#define pinStop 2
#define pinLeft 3
#define outRedight 4

#define outRed 8
#define outGreen 9
#define outBlue 10

#define pinT 13
 
void setup() {
  pinMode(pinStop,INPUT);
  pinMode(pinLeft,INPUT);
  pinMode(outRedight,INPUT);

  pinMode(outRed,OUTPUT);
  pinMode(outGreen,OUTPUT);
  pinMode(outBlue,OUTPUT);
  
  pinMode(pinT,OUTPUT);
  
  Serial.begin(57600); 
  Serial.println("hello lulos");
  mySerial.begin(38400);
}

String msg = "";
void loop() {

  //Read BT and show data
  if (mySerial.available()) {
    char c = mySerial.read();
    if(c == '\n'){
      Serial.println(msg);
      msg="";
    }else msg=msg+c;
  }

  //Read serial and send data
  if (Serial.available()) {
    char c =  Serial.read();
    mySerial.write(c);  
  }

  //Activate lights
  if(digitalRead(pinStop)){
      digitalWrite(outRed,LOW);
      mySerial.write('S');
      mySerial.write('\n');
      delay(500);
  }else digitalWrite(outRed,HIGH);  
  
  if(digitalRead(pinLeft)){
      digitalWrite(outGreen,LOW);
      mySerial.write('L');
      mySerial.write('\n');   
      delay(500);
  }else digitalWrite(outGreen,HIGH);
  
  if(digitalRead(outRedight)){
      digitalWrite(outBlue,LOW);
      mySerial.write('R');
      mySerial.write('\n'); 
      delay(500);
  }else digitalWrite(outBlue,HIGH);
  
}
