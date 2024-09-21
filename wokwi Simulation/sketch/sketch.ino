#include<Servo.h>

Servo servo;
int led = 12;
int ldr = A0;
int potpin = A1;  // analog pin used to connect the potentiometer
int intensity;    // variable to read the value from the analog pin
int count;

// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  servo.attach(9);
  servo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:

  int analogValue = analogRead(A0);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  intensity = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  intensity = map(intensity, 0, 1023, 0, 100);

  Serial.print("Intensity: ");
  Serial.println(intensity);
  if(count >= 2){

    digitalWrite(led, HIGH);
  }

  else{

    digitalWrite(led, LOW);
  }

  if (lux > intensity) {

    Serial.println("Light!");

    if(count <= 1){

      count = 0;
    }
  } 
  
  else {

    Serial.println("Dark!");

    if(count < 2){

      delay(2000);
      servo.write(28);
      delay(4000);
      servo.write(0);
      count++;
    }
  }

  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.println("          ");

  delay(100);
}
