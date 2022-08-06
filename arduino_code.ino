int lightPin = 2;

// for processPotentiometer()
int percent = 0;
int prevPercent = 0;

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
 
  delay(100);

  processPotentiometer();
}

void convertToState(char chr) {
  Serial.println(chr);
  
  if(chr=='w'){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(lightPin,HIGH);
    delay(100); 
  }
  if(chr=='t'){
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(lightPin,LOW);
    delay(100); 
  }
}

void processPotentiometer() {
  percent = round(analogRead(0) / 1024.00 * 100);
  
  if(percent != prevPercent) {
    Serial.println(percent);
    prevPercent = percent;
  }
  
  delay(100);
}