#include <Keypad.h>

#define GREEN 11
#define YELLOW 12
#define RED 13

const byte ROWS = 4;
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int i = 0;
char hour[4];
bool dawn = false;

void regular_schedule() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  delay(1000);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(1000);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, HIGH);
  delay(1000);
}

void dawn_schedule() {
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  delay(1000);
  digitalWrite(RED, HIGH);
  delay(1000);
}

void print_hour() {
  Serial.print("Hora Actual: ");
  Serial.print(hour[0]);
  Serial.print(hour[1]);
  Serial.print(":");
  Serial.print(hour[2]);
  Serial.print(hour[3]);
  Serial.println("");
}

void setup() {
  Serial.begin(9600);
  
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
}

int iteration = 0;
bool polling_hour = false;
int time = 0;

void poll_hour() {
  polling_hour = true;
  char customKey = customKeypad.getKey();
  if (customKey) {
    hour[i] = customKey;
    i++;
    if (i == 4) {
      print_hour();
      dawn = (hour[0] == '0' && hour[1] <= '5');
      i = 0;
      polling_hour = false;
      time = 0;
      iteration = 0;
      Serial.println("Ya no puedes cambiar la hora");
    }
  }
}

void loop() {
  if (polling_hour || iteration == 5) {
    if (iteration == 5 && !polling_hour) {
      Serial.println("Puedes cambiar la hora ahora");
    }
    poll_hour();
    if (time == 50000) {
      Serial.println("Te demoraste mucho...");
      polling_hour = false;
      time = 0;
      iteration = 0;
    }
    time++;
  } else {
    if (dawn) {
      dawn_schedule();
    } else {
      regular_schedule();
    }
  }
  iteration++;
}