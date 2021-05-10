const byte ROW_LENGTH = 8;
const byte COLUMN_LENGTH = 8;
const byte ROW_PINS[ROW_LENGTH] = {13, 12, 11, 10, 9, 8, 7, 6};
const byte COLUMN_PINS[COLUMN_LENGTH] = {5, 4, 3, 2, A0, A1, A2, A3};
const unsigned int INDEX[8] = {
	1 << 0,
	1 << 1,
	1 << 2,
	1 << 3,
	1 << 4,
	1 << 5,
	1 << 6,
	1 << 7
};

///Defining Matrices///
int matrixA[8][8];
int matrixB[8][8];
int matrixC[8][8];

void setup(){
  
  ///Setting up Serial monitor///
  Serial.begin(9600);
  ///Calling functions///
  setMatrixA();
  setMatrixB();
  checkMatrix();
  
	for (byte i = 0; i < ROW_LENGTH; i++){
		pinMode(ROW_PINS[i], OUTPUT);
		digitalWrite(ROW_PINS[i], LOW);
	}
	for (byte i = 0; i < COLUMN_LENGTH; i++){
		pinMode(COLUMN_PINS[i], OUTPUT);
		digitalWrite(COLUMN_PINS[i], HIGH);
	}
}

void loop(){
	setSmile();
}

void set(byte rowValue, byte columnValue, bool enabled){
	for (byte i = 0; i < ROW_LENGTH; i++){
		if ((rowValue & INDEX[i]) > 0){
			digitalWrite(ROW_PINS[i], ((enabled) ? HIGH : LOW));
		}
	}
	for (byte i = 0; i < COLUMN_LENGTH; i++){
		if ((columnValue & INDEX[i]) > 0){
 			digitalWrite(COLUMN_PINS[i], ((enabled) ? LOW : HIGH));
		}
	}
	delayMicroseconds(50);
}

void set(byte rowValue, byte columnValue){
	set(rowValue, columnValue, true);
	set(rowValue, columnValue, false);
}

void setSmile(){
  ///Loops traverse the elements in the array///
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(matrixC[i][j] == 1){///Turning on LEDs that are marked with 1///
      	set(INDEX[i], INDEX[j]);
      }
    }
  }
}

///Takes inputs for Matrix A ///
void setMatrixA(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      Serial.println("Enter integer in matrix A: ");///Indicator that user should enter an integer///
      while(Serial.available() == 0){} ///Waits for user input///
      matrixA[i][j] = Serial.parseInt(); ///Parses user input as int into the array///
      Serial.println(matrixA[i][j]);	
    }
  }
}

///Takes inputs for Matrix B///
void setMatrixB(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      Serial.println("Enter integer in matrix B: ");///Indicator that user should enter an integer///
      while(Serial.available() == 0){} ///Waits for user input///
      matrixB[i][j] = Serial.parseInt(); ///Parses user input as int into the array///
      Serial.println(matrixB[i][j]);		
    }
  }
}


///Checks the division between elements of both arrays///
void checkMatrix(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      ///Check if element of A divided by element of B gives a whole number///
      ///If true mark with 1 if false mark with 0///
      if(matrixA[i][j] % matrixB[i][j] == 0){ 
      	matrixC[i][j] = 1;
      }else{
        matrixC[i][j] = 0;
      }
    }
  }
}
