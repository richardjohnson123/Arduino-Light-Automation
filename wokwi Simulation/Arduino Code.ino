#include<Servo.h>

Servo servo;
const int led = 12;
const int ldr = A0;
const int potpin = A1;  // analog pin used to connect the potentiometer
int intensity = 1;    // variable to read the value from the analog pin
int count;

// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  servo.attach(9);
  servo.write(0);
}

void loop() {

  if (digitalRead((5)) == LOW) {

    intensity = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
    intensity = map(intensity, 0, 1023, 0, 100);
  }

  if (digitalRead((5)) == HIGH) {

    int analogValue = analogRead(A0);
    float voltage = analogValue / 1024. * 5;
    float resistance = 2000 * voltage / (1 - voltage / 5);
    float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

    Serial.println(resistance);

    if (count >= 2) {

      //Error: Something has gone wrong
      digitalWrite(led, HIGH);
    }

    else {

      digitalWrite(led, LOW);
    }

    if (lux > intensity) {

      Serial.println("Light!");

      if (count <= 1) {

        count = 0;
      }
    }

    else {

      //Serial.println("Dark!");

      if (count < 2) {

        delay(2000);
        servo.write(28);
        delay(4000);
        servo.write(0);
        count++;
      }
    }

    //Serial.print("Lux: ");
    //Serial.print(lux);
    //Serial.println("          ");

    delay(100);
  }

  Serial.print("Intensity: ");
  Serial.println(intensity);
  delay(100);
}
