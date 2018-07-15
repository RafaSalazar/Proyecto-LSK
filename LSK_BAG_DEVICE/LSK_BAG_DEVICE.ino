// LSK BAG DEVICE MASTER
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define signalRigth 2
#define signalLeft  4
#define signalStop  7
#define rigthRed    3
#define rigthBlue   5
#define leftRed     6
#define leftBlue    9
#define ledPin      13

bool stateR = false;
bool stateL = false;
bool stateS = false;

int cont = 0;
int limit = 50;
int interval = 10;
int value = 200;
void setup() {
  pinMode(signalRigth, OUTPUT);
  pinMode(signalLeft, OUTPUT);
  pinMode(signalStop, OUTPUT);
  pinMode(rigthRed, OUTPUT);
  pinMode(rigthBlue, OUTPUT);
  pinMode(leftRed, OUTPUT);
  pinMode(leftBlue, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(signalRigth, LOW);
  digitalWrite(signalLeft, LOW);
  digitalWrite(signalStop, LOW);
  digitalWrite(rigthRed, LOW);
  digitalWrite(rigthBlue, LOW);
  digitalWrite(leftRed, LOW);
  digitalWrite(leftBlue, LOW);
  digitalWrite(ledPin, LOW);
  
  Serial.begin(57600); 
  Serial.println("hello lulos");
  mySerial.begin(38400);
}

String msg = "";
void loop() {

  if (mySerial.available()) {
    char c = mySerial.read();
    if(c == '\n'){
      Serial.println(msg);
      if(msg == "R"){
        stateR = true;
        stateL = false;
        stateS = false;
        cont = 0;
        Serial.println("derecha");
      }else if(msg == "L"){
        stateR = false;
        stateL = true;
        stateS = false;
        cont = 0;
        Serial.println("izquierda");
      }else if(msg == "S"){
        stateR = false;
        stateL = false;
        stateS = true;
        cont = 0;
        Serial.println("stop");
      }
      msg="";
    }else msg=msg+c;
  }
  if (Serial.available()) {
    char c =  Serial.read(); 
    mySerial.write(c);  
  }

  if(stateR){
      digitalWrite(signalRigth,HIGH);
      analogWrite(rigthBlue,value);
      delay(interval);
      cont++;
      Serial.print("Derecha");
      Serial.println(cont);
  }else{
      digitalWrite(signalRigth,LOW);
      analogWrite(rigthBlue,0);
  }

  if(stateL){
      digitalWrite(signalLeft,HIGH);
      analogWrite(leftBlue,value);
      delay(interval);
      cont++;
      Serial.print("Izquierda");
      Serial.println(cont);
  }else{
      digitalWrite(signalLeft,LOW);
      analogWrite(leftBlue,0);
  }
  
  if(stateS){
      digitalWrite(signalStop,HIGH);
      analogWrite(rigthRed,value);
      analogWrite(leftRed,value);
      delay(interval);
      cont++;
      Serial.print("Stop");
      Serial.println(cont);
  }else{
      digitalWrite(signalStop,LOW);
      analogWrite(rigthRed,0);
      analogWrite(leftRed,0);
  }

  if(cont > limit){
    stateR = false;
    stateL = false;
    stateS = false;
    cont = 0;
    }
  
  
}
