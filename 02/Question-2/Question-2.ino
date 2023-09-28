#include <Servo.h>
#include <Keypad.h>

Servo myservo;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int trigPin = 10;
const int echoPin = 11;

String input = "";
String password = "159D";

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myservo.attach(13); // PWN pin connected to servomotor
}

void open() {
  myservo.write(180);
}

void close() {
  myservo.write(0);
}

void poll_password() {
  char key = customKeypad.getKey();
  if (key) {
    input += key;
    Serial.println(input);
    if (input == "*") {
      input = "";
    }
    if (input == password) {
      open_door();
      input = "";
    }
  }
}

void open_door() {
  open();
  delay(1000);
}

void close_door() {
  close();
  delay(1000);
}

long duration;
double distance;

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.0;

  // Serial.println(distance);

  if (distance < 10.0) {
    poll_password();
  } else {
    close_door();
  }
}
