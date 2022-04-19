
//Constants:
const int ledPin = 3;   //pin 3 has PWM funtion
const int flexPin = A0; //pin A0 to read analog input

//Variables:
int value; //save analog value


void setup(){
  Serial.begin(9600);       //Begin serial communication

}

  float k = 0.1;  // коэффициент фильтрации, 0.0-1.0

  // бегущее среднее
  float expRunningAverage(float newVal) {
  static float filVal = 0;
  filVal += (newVal - filVal) * k;
  return filVal;
  }

void loop(){
  
  value = analogRead(flexPin);         //Read and save analog value from potentiometer
  value = map(value, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  
  value = expRunningAverage(float(value));
  Serial.println(value);               //Print value
  delay(300);                          //Small delay
  
}
