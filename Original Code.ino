
#include<Servo.h>

Servo servo;
int count;

const int led = 13;
const int ldr = A0;
const int resetButton = 9;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  servo.attach(8);
  servo.write(0);
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  pinMode(resetButton, INPUT_PULLUP);
  //digitalWrite(led, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  int ldrStatus = analogRead(ldr);
  bool reset = digitalRead(resetButton);
  Serial.println(ldrStatus);

  if(reset == false){

    while(digitalRead(resetButton) == false){

      count = 0;
    }
  }

  if(count >= 2){

    digitalWrite(led, HIGH);
  }

  else{

    digitalWrite(led, LOW);
  }

  if(ldrStatus < 35){
    //digitalWrite(servoPin, HIGH);

    if(count < 2){

      delay(10000);
      servo.write(28);
      delay(2000);
      servo.write(0);
      count++;
    }

    Serial.println("Light OFF");
  }

  else{

    Serial.println("Light ON");

    if(count <= 1){

      count = 0;
    }
  }
}
