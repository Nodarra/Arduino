// C++ code
//
int even;
int odd;
int matrix[10][10];

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  even = 0;
  odd = 0;
  
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      matrix[i][j] = random(1, 100);
    }
  }
  
  for(int n = 0; n < 10; n++){
    for(int m = 0; m < 10; m++){
      if(matrix[n][m] % 2 == 0){
        even += 1;
        digitalWrite(12, HIGH);
        delay(100);
        digitalWrite(12, LOW);
      }else{
      	odd += 1;
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
      }
    }
  }
  
  Serial.println("Number of even numbers is:");
  Serial.println(even);
  Serial.println("Number of odd numbers is:");
  Serial.println(odd);
}

void loop()
{
/////Soemthing////////
}