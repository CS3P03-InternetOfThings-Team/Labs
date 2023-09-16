void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  int mappedValue = map(sensorValue, 0, 1023, 0, 15);

  Serial.println(mappedValue);

}