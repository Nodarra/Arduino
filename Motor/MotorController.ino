const int motorIn1 = 7;  //Pin description in void setup//
const int motorIn2 = 6;  
const int enB = 8;

int btn1pin=12;           
int led1pin=22;            
int btn2pin=11;           
int led2pin=23;            
int btn3pin=10;            
int led3pin=24;            
int btn4pin=9;            
int led4pin=25;
int hallsensor = 2;       

int state = 0;            //Motor state 0 = STOP  1 = clockwise  2 = counterclockwise  
int DCmotorspeed = 128;   //Initial motor speed set to 128 for easier demonstration 
volatile byte counter;    //Counts pulses from the sensor
unsigned int rpm;         //RPM variable to display
unsigned long passedtime; //Time passed between two pulses 

void isr()
{
 counter++; //Measures pulses sent by sensor//
 delay(10);
 detachInterrupt(2); //Interrupts are disabled to calculate RPM
 rpm = 60*1000/(millis() - passedtime)*counter;
 passedtime = millis(); //Takes passed time in milliseconds
 counter = 0;
 Serial.print("RPM= ");
 Serial.println(rpm); //Prints out result to monitor
 attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(motorIn1,OUTPUT);     //Motor pin that controll the direction 
  pinMode(motorIn2,OUTPUT);     //Motor pin that controll the direction
  pinMode(btn1pin,INPUT_PULLUP);//Button 1 used for starting the motor
  pinMode(led1pin,OUTPUT);      //LED 1 to indicate motor is running
  pinMode(btn2pin,INPUT_PULLUP);//Button 2 used for changing motor direction 
  pinMode(led2pin,OUTPUT);      //LED 2 used to indicate that direction was changed
  pinMode(btn3pin,INPUT_PULLUP);//Button 3 used to increase the speed of motor
  pinMode(led3pin,OUTPUT);      //LED 3 used to indicate the increase of speed
  pinMode(btn4pin,INPUT_PULLUP);//Button 4 used to decrease the speed of motor
  pinMode(led4pin,OUTPUT);      //LED 4 used to indicate the decrease of speed  
  
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING); //Interrupts are called on rise of input i.e. when the sensor detects something
  pinMode(hallsensor, INPUT); //Sets hallsensor as input
  counter = 0; //Initial counter set to 0
  rpm = 0; //Initial RPM set to 0
  passedtime = 0;//Set digital 2 port mode, the OUTPUT for the output
}

void loop()
{  
  //STARTING THE MOTOR CODE//
  if(digitalRead(btn1pin)==LOW)          //Detecting if Button 1 is pressed
  {   
      delay(10);                         
      if(digitalRead(btn1pin)==LOW)      //Confirm Button 1 is pressed
      {     
        while(digitalRead(btn1pin)==LOW);
        delay(10);                       
        while(digitalRead(btn1pin)==LOW);//Confirm button is released
        for(int i=0;i<4;i++)     
        {
          digitalWrite(led1pin,HIGH); //Activate LED to indicate button is pressed
          delay(100);               
          digitalWrite(led1pin,LOW);  //Turn off LED, OFF
          delay(100);                 
        }
        if(state!=0)                  //Reading the state of the motor 
        {
           state = 0;                 // Motor is at rest
           digitalWrite(led1pin,LOW); //LED 1 is OFF to indicate motor is not active
        }
        else
        {   
           state = 1;                 //Motor is initiated
           digitalWrite(led1pin,HIGH);//LED 1 is turned ON
        }  
      }
   }

  //CHANGING MOTOR DIRECTION CODE//
  if(digitalRead(btn2pin)==LOW)          //Detecting if Button 2 is pressed
  {   
      delay(10);                         
      if(digitalRead(btn2pin)==LOW)      //Confirm Button 2 is pressed
      {     
        while(digitalRead(btn2pin)==LOW);
        delay(10);                       
        while(digitalRead(btn2pin)==LOW);//Confirm button is released
        if(state!=0)                     //Checking the state of the motor
        {
           for(int i=0;i<4;i++)
           {
              digitalWrite(led2pin,HIGH);//LED 2 is ON to indicate button press
              delay(100);                
              digitalWrite(led2pin,LOW); //LED 2 is OFF
              delay(100);                
            }
            if(state==1)                 
            {state = 2;}                 //State changed, motor runs in other direction 
            else if(state==2)            
            {state = 1;}                 //State changed, motor runs in other direction 
         }    
      }
   }

  //INCREASING MOTOR SPEED CODE//
  if(digitalRead(btn3pin)==LOW)          //Detecting if Button 3 is pressed
  {   
      delay(10);                         
      if(digitalRead(btn3pin)==LOW)      //Confirm Button 3 is pressed
      {     
        while(digitalRead(btn3pin)==LOW);
        delay(10);                       
        while(digitalRead(btn3pin)==LOW);//Confirm button is released
        if(state!=0)                     //Checking the state of motor
        {
            for(int i=0;i<4;i++)
            {
               digitalWrite(led3pin,HIGH);//LED3 is ON to indicate button press
               delay(100);                
               digitalWrite(led3pin,LOW); //LED3 is OFF
               delay(100);               
             }
             if(DCmotorspeed<230)         
             {DCmotorspeed += 20;}       //Motor speed is increased by 20
             else
             {DCmotorspeed = 230;}       //Motor speed set to 230, cannot increase it more
         }
      }
   }
   
   if(digitalRead(btn4pin)==LOW)         //Detecting if Button 4 is pressed
   {   
      delay(10);                         
      if(digitalRead(btn4pin)==LOW)      //Confirm button 4 is pressed
      {     
        while(digitalRead(btn4pin)==LOW);/
        delay(10);                       
        while(digitalRead(btn4pin)==LOW);//Confirm button is released
        if(state!=0)
        {
           for(int i=0;i<4;i++)
           {
              digitalWrite(led4pin,HIGH);//LED 4 is ON to indicate button is pushed
              delay(100);                
              digitalWrite(led4pin,LOW); //LED 4 is OFF
              delay(100);               
            }
            if(DCmotorspeed>30)
            {DCmotorspeed -= 20;}        //Motor speed is reduced by 20
            else
            {DCmotorspeed = 20;}         //Motor speed set to 20, minimum value of motor speed(MOTOR STOP)
        }  
      }
   }
   
  switch(state)
  {
    case 0:  clockwise(0);                  //Run motor clockwise withoud speed 
             break;
    case 1:  clockwise(DCmotorspeed);       //Run motor clockwise with speed
             break;
    case 2:  counterclockwise(DCmotorspeed);//Run motor counter clockwise with speed
             break;
    default: clockwise(0);                  //Run motor clockwise without speed
             break;
  }
}

//The function to drive motor clockwise
void clockwise(int Speed)
{
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  analogWrite(enB, Speed); //Setting speed of the motor
}

//The function to drive motor counterclockwise
void counterclockwise(int Speed)
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  analogWrite(enB, Speed); //Setting speed of the motor
}
