/*
 * This is the Automated Planter Box
 * The LCD will be on all the time, but the brightness will be controlled by a pot
 * The Moisture sensor will read values consistenly
 * 
*/
#include <LiquidCrystal.h>
#include <FastLED.h>
#include <math.h>
#define AV_VAL 10
#define NUM_LEDS 60
#define DATA_PIN 10
#define MOIST_VAL 400                                           //this is the value to alert the system to fill up (AIR = 571; WATER = 302)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN
CRGB leds[NUM_LEDS];    //DONT CHANGE
void ledF();
int ledS = 10;
int ledState =  HIGH;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
float moist = A5;
float moisture_level;
int pump = 9;
int water_jugg = 8;
int water_state = LOW;    //when testing the make shift jugg sensor, this is the variable i change if it is HIGH when dis-connected
int alert = 11;         //alerts user when water jugg levels are low

void setup(){
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  Serial.begin(115200);
  lcd.begin(16, 2);
  pinMode(ledS, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(water_jugg, INPUT);   //make sure to add a resistor (220 ohm) when wiring between positive lead and pin
    for(int i = 0; i<NUM_LEDS; i++){    //sets the LED strip on at the start of the code
    leds[i].setRGB(0,120,120);
    FastLED.show();
  }
}


void loop(){
  ledF();
  moisture_level = avr(analogRead(moist));
  //Serial.println(moisture_level);
  lcd.setCursor(0,0);
  lcd.print("Moisture Levels: ");
  lcd.setCursor(0,1);
  lcd.print(moisture_level,0);
  while(moisture_level >= MOIST_VAL){          //i.e. if the plant needs water
    lcd.clear();
    do{
      Serial.println(digitalRead(water_jugg));
      tone(alert,250,500);         //Time using milliseconds --> (millis()/30000)%2
      noTone(alert);
      lcd.setCursor(0,0);
      lcd.print("WATER JUGG EMPTY!!!");
    }while(digitalRead(water_jugg) == water_state);   //if the water level is LOW
    digitalWrite(pump, HIGH);
    moisture_level = avr(analogRead(moist)); 
  }
}


float avr(int readA){
float sum = 0;
float average;
    for(int i = 0; i< AV_VAL; i++){
    sum += float(readA);
  }
    average = sum / AV_VAL;
return average;
}


void ledF(){
long OnTime = (5.76 * pow(10,7));           // milliseconds of on-time (16 hours = 5.76 x 10^7)
long OffTime = (2.88 * pow(10,7));          // milliseconds of off-time (8 hours = 2.88 x 10^7)

unsigned long currentMillis = millis();
  if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime)){
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    // Updates the actual LED
          //digitalWrite(ledS, ledState);  
    for(int i = 0; i<NUM_LEDS; i++){
      leds[i].setRGB(0,120,120);
      FastLED.show();
    }
  }else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime)){
    ledState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    // Updates the actual LED
          //digitalWrite(ledS, ledState);    
      for(int i = NUM_LEDS; i>0; i--){
        leds[i] = CRGB::Black;
        FastLED.show();
      }
  delay(2000);
  }
}
