
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>         
LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей
//Constants:
const int ledPin = 3;   //pin 3 has PWM funtion
const int flexPin = A0; //pin A0 to read analog input

//Variables:
int value; //save analog value


void setup(){
  Serial.begin(9600);       //Begin serial communication
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("Value");
  lcd.setCursor(7, 0);
}

  float k = 0.1;  // коэффициент фильтрации, 0.0-1.0


  // бегущее среднее
  float expRunningAverage(float newVal) {
  static float filVal = 0;
  filVal += (newVal - filVal) * k;
  return filVal;
  }
void fillBar0(byte start_pos, byte row, byte bar_length, byte fill_percent) {
  byte infill = round((float)bar_length * fill_percent / 100);
  lcd.setCursor(start_pos, row);
  if (infill == 0) lcd.write(16);
  else lcd.write(255);
  for (int n = 1; n < bar_length - 1; n++) {
    if (n < infill) lcd.write(255);
    if (n >= infill) lcd.write(16);
  }
  if (infill == bar_length) lcd.write(255);
  else lcd.write(16);
}
void loop(){
  
  value = analogRead(flexPin);         //Read and save analog value from potentiometer
  value = map(value, 600, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  int perc = map(value, 0, 300, 0, 100);
  value = expRunningAverage(float(value));
  Serial.println(value);//Print value
  lcd.setCursor(7, 0);
  lcd.print(value);
  fillBar0(0,1,10,perc);
  delay(300);                          //Small delay
  
}
