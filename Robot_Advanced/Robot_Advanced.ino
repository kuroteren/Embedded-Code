int Rwheel[] = {5, 6};
int Lwheel[] = {9, 10};

int USEcho = 3;
int USTrig = 4;

long duration, cm;
int speedSet;

void setup() {
  // put your setup code here, to run once:
  pinMode(Rwheel[0], OUTPUT);
  pinMode(Rwheel[1], OUTPUT);
  pinMode(Lwheel[0], OUTPUT);
  pinMode(Lwheel[1], OUTPUT);

  pinMode(USEcho, INPUT);
  pinMode(USTrig, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(USTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(USTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(USTrig, LOW);

  duration = pulseIn(USEcho, HIGH);
  cm = microsecondsToCM(duration);

  Serial.println(cm);

  stopMove();

  if(cm >= 100)
  {
    speedSet = 255;
    forward();
  }
  else if (cm >= 75 && cm < 100)
  {
    speedSet = 175;
    forward();
  }
  else if (cm >= 20 && cm < 75)
  {
    speedSet = 100;
    forward();
  }
  else if (cm > 10)
  {
    speedSet = 60;
    forward();
  }
  else
  {
    stopMove();

    reverse();

    spinLeft();
  }

  delay(1000);
}

void forward()
{
  analogWrite(Rwheel[1], 0);
  analogWrite(Lwheel[1], 0);
  analogWrite(Lwheel[0], speedSet);
  analogWrite(Rwheel[0], speedSet);
}

void reverse()
{
  analogWrite(Rwheel[0], 0);
  analogWrite(Lwheel[0], 0);
  analogWrite(Rwheel[1], 200);
  analogWrite(Lwheel[1], 200);

  delay(750);

  stopMove();
}

void stopMove()
{
  analogWrite(Rwheel[0], 0);
  analogWrite(Lwheel[0], 0);
  analogWrite(Rwheel[1], 0);
  analogWrite(Lwheel[1], 0);
}

void spinLeft()
{
  analogWrite(Rwheel[0], 0);
  analogWrite(Lwheel[1], 0);
  analogWrite(Rwheel[1], 150);
  analogWrite(Lwheel[0], 150);

  delay(500);

  stopMove();
}

long microsecondsToCM(long x)
{
  return (x / 29 / 2);
}
