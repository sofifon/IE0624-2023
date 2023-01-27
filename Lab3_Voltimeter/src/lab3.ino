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
int v;
int switch_pin = 8;
int ac_switch = 9;



void setup() {
  lcd.begin(84, 48);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(switch_pin, INPUT);
  pinMode(ac_switch, INPUT);   

}

// lectura del valor maximo de la onda
uint16_t get_max() {
  uint16_t max_v = 0;
  for(uint8_t i = 0; i < 100; i++) {
    uint16_t r = analogRead(volt3Pin);
    if(max_v < r) max_v = r;
    delayMicroseconds(200);
  }
  return max_v;
}


void loop() {
    lcd.clear();
    volt0 = map(analogRead(volt0Pin), 0, 956, -24, 24);
    volt1 = map(analogRead(volt1Pin), 0, 956, -24, 24);
    volt2 = map(analogRead(volt2Pin), 0, 956, -24, 24);

    if(digitalRead(ac_switch) == LOW){
      volt3 = map(analogRead(volt3Pin), 0, 956, -24, 24);
    }
    if (digitalRead(ac_switch)== HIGH){
      char buf[10];
      uint32_t v = get_max();
     
      volt3 = map(v, 0, 475, 0, 24);
      // calculo de RMS
      volt3 /= sqrt(2);
    }
    
   

 
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

  
  delay(1000);
 }
