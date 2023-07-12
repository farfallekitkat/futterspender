#define taster1 32
#define taster2 33
#define taster3 27

int counter = 0;

void setup() {
  pinMode(taster1, INPUT);
  pinMode(taster2, INPUT);
  pinMode(taster3, INPUT);

  Serial.begin(9600);
}

void loop() {
  int zustand1 = digitalRead(taster1);
  int zustand2 = digitalRead(taster2);
  int zustand3 = digitalRead(taster3);

  if (zustand1 == LOW)
  {
    Serial.println("taster1 gedruekt");
    delay(250);
  }
  if (zustand2 == LOW)
  {
    Serial.println("taster2 gedruekt");
    delay(250);
  }
  if (zustand3 == LOW)
  {
    Serial.println("taster3 gedruekt");
    delay(250);
  }
  delay(50);
}
