/// this code is to send/receive multiple float variables to/from Simulink

typedef union{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

// Create the variables you want to receive
FLOATUNION_t myValue1;
FLOATUNION_t myValue2;
FLOATUNION_t myValue3;

// Create the variables to send
FLOATUNION_t send1;
FLOATUNION_t send2;
FLOATUNION_t send3;

void setup() {
  // initialize serial, use the same boudrate in the Simulink Config block
  Serial.begin(115200);

}
void loop(){

  // Get the floats from serial
  getFloat();
  send1.number = myValue1.number;
  send2.number = myValue2.number;
  send3.number = myValue3.number;
  
  // Print header: Important to avoid sync errors!
  Serial.write('A'); 
  // Print float data
  for (int i=0; i<4; i++){
    Serial.write(send1.bytes[i]); 
  }
  for (int i=0; i<4; i++){
    Serial.write(send2.bytes[i]); 
  }
  for (int i=0; i<4; i++){
    Serial.write(send3.bytes[i]); 
  }
  // Print terminator
  Serial.print('\n');
 // Use the same delay in the Serial Receive block
  delay(50);
}


void getFloat(){
    while (Serial.available()>13){
      int cont = 0;
      FLOATUNION_t f;
      char header;
      header = (char)Serial.read();
      if (header =='x'){
        while (cont < 4 ){
          myValue1.bytes[cont] = Serial.read() ;
          cont = cont +1;
        }
        cont = 0;
        while (cont < 4 ){
          myValue2.bytes[cont] = Serial.read() ;
          cont = cont +1;
        }
        cont = 0;
        while (cont < 4 ){
          myValue3.bytes[cont] = Serial.read() ;
          cont = cont +1;
        }
        char terminator = (char)Serial.read();
      }
    }
}
