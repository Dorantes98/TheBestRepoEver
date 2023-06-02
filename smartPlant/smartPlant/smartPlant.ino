#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_5s; 

float tempF;
float sound;
float light;
float capValue;
int BlueLEDValue = 0;
int RedLEDValue = 0;
int GreenLEDValue = 0;
int switchPin = 7;

volatile bool switchState = 0;
volatile bool switchFlag = 0; 


void setup() {

Serial.begin(9600);

CircuitPlayground.begin();

pinMode(switchPin, 2);
attachInterrupt(digitalPinToInterrupt(switchPin), onOff, CHANGE);

delay_5s.start(5000, AsyncDelay::MILLIS);

}

void loop() {
if (delay_5s.isExpired()) {
sound = CircuitPlayground.mic.soundPressureLevel(50); 
  Serial.print("SPL: ");
  Serial.println(sound);
tempF = CircuitPlayground.temperatureF();
  Serial.print("temp is: ");
  Serial.println(tempF);
light = CircuitPlayground.lightSensor();
  Serial.print("Light Sensor: ");
  Serial.println(light);
capValue = CircuitPlayground.readCap(6);
  Serial.print("Capacitance Value ");
  Serial.println(capValue);
delay_5s.repeat();
}
if(switchFlag){
  delay(5);   //debounce
  switchState = digitalRead(switchPin);
  switchFlag = 0;
}
if(switchState){
    if(sound >= 40){
      Serial.print("SOUND IS TOO LOUD: ");
      Serial.println(sound);
      for(int i = 0; i<10; i++){
        CircuitPlayground.clearPixels();
        delay(10);
        CircuitPlayground.setPixelColor(i, 69, 246, 238);
        CircuitPlayground.playTone(999, 50);
        delay(50);
      }
      delay(1);
    }
}
  if(tempF >= 80){
    Serial.print(" temp is: ");
    Serial.println("Hot Tamale  ");
    flash();
    RedLEDValue = map(tempF, 74, 100, 0, 255);
    for(int i = 0; i<9; i++){
      CircuitPlayground.setPixelColor(i, tempF, 0, 0);
    }
  }

  else if(tempF <= 68){
    Serial.print(" temp is: ");
    Serial.println(" Chilly Willy ");
    BlueLEDValue = map(tempF, 0, 68, 0, 255);
    for(int i = 0; i<9; i++){
      CircuitPlayground.setPixelColor(i, 0, 0, tempF);
    }

  }

  else{
    Serial.print(" temp Is: ");
    Serial.println(" Pleasant ");
    GreenLEDValue = map(tempF, 69, 73, 0, 255);
    for(int i = 0; i<9; i++){
      CircuitPlayground.setPixelColor(i, 0, tempF, 0);
    }
  }
if(capValue < 900){
  CircuitPlayground.setPixelColor(9, 255, 0, 0);
}

else{
  CircuitPlayground.setPixelColor(9, 0, 128, 0);
}

delay(500);

}

void flash()
{
  CircuitPlayground.clearPixels();

  delay(50);

  CircuitPlayground.setPixelColor(0, tempF, 0, 0);
  CircuitPlayground.setPixelColor(1, tempF, 0, 0);
  CircuitPlayground.setPixelColor(2, tempF, 0, 0);
  CircuitPlayground.setPixelColor(3, tempF, 0, 0);
  CircuitPlayground.setPixelColor(4, tempF, 0, 0);
  CircuitPlayground.setPixelColor(5, tempF, 0, 0);
  CircuitPlayground.setPixelColor(6, tempF, 0, 0);
  CircuitPlayground.setPixelColor(7, tempF, 0, 0);
  CircuitPlayground.setPixelColor(8, tempF, 0, 0);

  delay(50);
  
  CircuitPlayground.clearPixels();
}

void onOff()
{
  switchFlag = 1;
}



void cowbell(int awesomeness)
{
  int x = awesomeness;
  return sickBeats;
}