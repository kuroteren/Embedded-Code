int Rwheel[] = {4, 5};
int Lwheel[] = {7, 8};
int POWER = 6;

int Rencoder = 2;
int Lencoder = 3;

volatile int Rcount = 0;
volatile int Lcount = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Rwheel[0], OUTPUT);
  pinMode(Rwheel[1], OUTPUT);
  pinMode(Lwheel[0], OUTPUT);
  pinMode(Lwheel[1], OUTPUT);
  pinMode(POWER, OUTPUT);

  pinMode(Rencoder, INPUT_PULLUP);
  pinMode(Lencoder, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(Rencoder), countRight, HIGH);
  attachInterrupt(digitalPinToInterrupt(Lencoder), countLeft, HIGH);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(POWER, HIGH);

  /*
   * Forward
   */
  forward();

  delay(10000);

  Serial.print("Right wheel: ");
   Serial.print(Rcount);
   Serial.print("      /        ");
   Serial.print("Left wheel: ");
   Serial.println(Lcount);

  /*
   * Reverse
   */
  reverse();

  delay(10000);

  Serial.print("Right wheel: ");
   Serial.print(Rcount);
   Serial.print("      /        ");
   Serial.print("Left wheel: ");
   Serial.println(Lcount);

  /*
   * Speed Control
   */
   speedControl();

   /*
    * Stop
    */
   digitalWrite(POWER, LOW);

   delay(10000);

   Serial.print("Right wheel: ");
   Serial.print(Rcount);
   Serial.print("      /        ");
   Serial.print("Left wheel: ");
   Serial.println(Lcount);

   /*
    * Spin left/right
    */
   spinLeft();

   delay(10000);

   Serial.print("Right wheel: ");
   Serial.print(Rcount);
   Serial.print("      /        ");
   Serial.print("Left wheel: ");
   Serial.println(Lcount);

   spinRight();

   delay(10000);

   Serial.print("Right wheel: ");
   Serial.print(Rcount);
   Serial.print("      /        ");
   Serial.print("Left wheel: ");
   Serial.println(Lcount);

   digitalWrite(POWER, LOW);

   /*
    * Turn left/right
    */
   turnRight();

   delay(10000);

   turnLeft();

   delay(10000);

   digitalWrite(POWER, LOW);

   delay(3000);

   Serial.print("Right wheel: ");
   Serial.print(Rcount);
   Serial.print("      /        ");
   Serial.print("Left wheel: ");
   Serial.println(Lcount);
}

void forward()
{
  digitalWrite(Rwheel[1], LOW);
  digitalWrite(Lwheel[1], LOW);
  digitalWrite(Lwheel[0], HIGH);
  digitalWrite(Rwheel[0], HIGH);
}

void reverse()
{
  digitalWrite(Rwheel[0], LOW);
  digitalWrite(Lwheel[0], LOW);
  digitalWrite(Rwheel[1], HIGH);
  digitalWrite(Lwheel[1], HIGH);
}

void speedControl()
{
  analogWrite(POWER, 200);
   delay(1000);
   analogWrite(POWER, 150);
   delay(1000);
   analogWrite(POWER, 100);
   delay(1000);
   analogWrite(POWER, 50);
   delay(1000);
}

void spinLeft()
{
  digitalWrite(POWER, LOW);
  
  digitalWrite(Rwheel[0], LOW);
  digitalWrite(Rwheel[1], HIGH);
  digitalWrite(Lwheel[0], HIGH);
  digitalWrite(Lwheel[1], LOW);

  digitalWrite(POWER, HIGH);
}

void spinRight()
{
  digitalWrite(POWER, LOW);

  digitalWrite(Rwheel[0], HIGH);
  digitalWrite(Rwheel[1], LOW);
  digitalWrite(Lwheel[0], LOW);
  digitalWrite(Lwheel[1], HIGH);
  
  digitalWrite(POWER, HIGH);
}

void turnRight()
{
  digitalWrite(POWER, LOW);
  
  digitalWrite(Rwheel[0], LOW);
  digitalWrite(Rwheel[1], LOW);
  digitalWrite(Lwheel[0], HIGH);
  digitalWrite(Lwheel[1], LOW);
  
  digitalWrite(POWER, HIGH);
}

void turnLeft()
{
  digitalWrite(POWER, LOW);

  digitalWrite(Rwheel[0], HIGH);
  digitalWrite(Rwheel[1], LOW);
  digitalWrite(Lwheel[0], LOW);
  digitalWrite(Lwheel[1], LOW);
   
  digitalWrite(POWER, HIGH);
}

void countRight()
{
  Rcount++;
}

void countLeft()
{
  Lcount++;
}
