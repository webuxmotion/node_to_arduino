#include <ArduinoJson.h>


int lightPin = 2;

// for processPotentiometer()
int percent = 0;
int prevPercent = 0;

int prevLed = 0;

DynamicJsonDocument doc(1024);

String prevDoc;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  sendJson();
  
  if (Serial.available() > 0) {
    char ReaderFromNode; // Store current character
    ReaderFromNode = (char) Serial.read();
    convertToState(ReaderFromNode); // Convert character to state  
  } 
  
  processPotentiometer();

  delay(100);
}

void convertToState(char chr) {
  
  if(chr=='w') {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(lightPin,HIGH);
    doc["led"] = HIGH;
    delay(10);
  }
  if(chr=='t') {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(lightPin,LOW);
    doc["led"] = LOW;
    delay(10);
  }

  delay(10);
}

void processPotentiometer() {
  
  percent = round(analogRead(0) / 1024.00 * 100);
  
  if(percent != prevPercent) {
    prevPercent = percent;
    doc["potentiometr"] = percent;
    doc["led"] = digitalRead(LED_BUILTIN) || digitalRead(lightPin);
    
    delay(10);
  }
  
  delay(10);
}

void sendJson() {
  String newDoc = doc.as<String>();
  
  if (newDoc != prevDoc) {
    Serial.println();
    serializeJson(doc, Serial);
    prevDoc = doc.as<String>();
  }
}
