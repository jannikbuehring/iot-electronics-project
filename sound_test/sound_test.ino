int sensor = 0;
const int soundsensor = A0;
const int digital = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(soundsensor,INPUT);
  pinMode(digital, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //sensor = analogRead(soundsensor);
  sensor = digitalRead(digital);
  //Serial.println(sensor);
  if (sensor == 1){
    Serial.println("clap!");
    delay(100);
  }
}
