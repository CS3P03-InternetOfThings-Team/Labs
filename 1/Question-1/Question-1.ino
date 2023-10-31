#define GREEN 11
#define YELLOW 12
#define RED 13

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
}

void loop() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  delay(10000);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(3000);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, HIGH);
  delay(5000);
}
