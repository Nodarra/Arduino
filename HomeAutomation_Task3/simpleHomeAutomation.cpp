// C++ code
//
//Thinkercad Link: https://www.tinkercad.com/things/jok0M0vRDr4-super-krunk/editel

int photoSensor = 0;
int gasSensor = 0;
int pirSensor = LOW;
int tempSensor = 0;

int gasLimit = 47;
int darkLimit = 500;
int tempLimit = 35;

void setup()
{
  //INPUTS//
  pinMode(A0, INPUT); //Gas//
  pinMode(A1, INPUT); //Light//
  pinMode(A2, INPUT); //Temperature//
  pinMode(2, INPUT);  //PIR Sensor//
  
  //OUTPUTS//
  pinMode(3, OUTPUT); //Alarm&Vibration//
  pinMode(4, OUTPUT); //Alarm//
  pinMode(5, OUTPUT); //Motor//
  pinMode(6, OUTPUT); //Light//
}

void loop()
{
  gasDetect();
  delay(10);
  lightDetect();
  delay(10);
  motionDetect();
  delay(10);
  tempDetect();
  delay(10);
}

void gasDetect(){
  gasSensor = analogRead(A0);
  	
  if(gasSensor > gasLimit){
    digitalWrite(3, HIGH);
  }else{
    digitalWrite(3, LOW);
  }
}

void lightDetect(){
  photoSensor = analogRead(A1);
  
  if(photoSensor < darkLimit){
  	digitalWrite(6, HIGH);
  }else{
    digitalWrite(6, LOW);
  }
}

void motionDetect(){
  pirSensor = digitalRead(2);
  
  if(pirSensor == HIGH){
  	digitalWrite(4, HIGH);
  }else{
    digitalWrite(4, LOW);
  }
}

void tempDetect(){
  tempSensor = analogRead(A2);
  
  if(tempSensor > tempLimit){
    digitalWrite(5, HIGH);
  }else{
    digitalWrite(5, LOW);
  }
}