#include <PCD8544.h>
PCD8544 lcd;

int LED=12;
float volt0=0;
float volt1=0;
float volt2=0;
float volt3=0;
int volt0Pin = A0;
int volt1Pin = A1;
int volt2Pin = A2;
int volt3Pin = A3;
int switch_pin = 8;

void setup() {
  lcd.begin(84, 48);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(switch_pin, INPUT);   

}
void loop() {
    lcd.clear();
    volt0 = analogRead(volt0Pin)*48/1023 - 24;
   

 
  lcd.setCursor(0, 0);
  lcd.print("V1: ");
  lcd.print(volt0);
  lcd.print(" V");
  lcd.setCursor(0,1);
  lcd.print("V2: ");
  lcd.print(volt1);
  lcd.print(" V");  
  lcd.setCursor(0, 2);
  lcd.print("V3: ");
  lcd.print(volt2);
  lcd.print(" V"); 
  lcd.setCursor(0,3);   
  lcd.print("V4: ");
  lcd.print(volt3);
  lcd.print(" V");

  if(digitalRead(switch_pin) == HIGH){  
    Serial.println(volt0);
    Serial.println(volt1);
    Serial.println(volt2);
    Serial.println(volt3);
  }
  if (volt0 < -20 || volt0 > 20 || volt1 < -20 || volt1 > 20 || volt2 < -20 || volt2 > 20 || volt3 < -20 || volt3 > 20){
    digitalWrite(LED, HIGH);        
  }else {
    digitalWrite(LED, LOW);
  }

  
  delay(2000);
 }
