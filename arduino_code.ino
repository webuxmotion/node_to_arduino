int lightPin = 2;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
    char ReaderFromNode; // Store current character
    ReaderFromNode = (char) Serial.read();
    convertToState(ReaderFromNode); // Convert character to state  
  }
 
  delay(1000);
}

void convertToState(char chr) {
  Serial.println(chr);
  
  if(chr=='w'){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(lightPin,HIGH);
    delay(1000); 
  }
  if(chr=='t'){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(lightPin,LOW);
    delay(1000); 
  }
}