// LEDs
const int RED = 8;
const int YEL = 9;
const int GRN = 10;
const int BLU = 11;

// Length of sequence
int seqlen;

// Bool if sequence was entered successfully by player
bool success;

void setup() {
  // put your setup code here, to run once:
  // Buttons
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);


  pinMode(RED, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(BLU, OUTPUT);

  // Random seed start
  randomSeed(analogRead(1));
  // Start with 1 LED
  seqlen = 1;

  success = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  int sequence[seqlen];
  int player[seqlen];

  // Simon says:
  for(int x = 0; x < seqlen; x++)
  {
    int v = rand() % 4;

    sequence[x] = v;

    if(v == 0)
    {
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
    }
    if(v == 1)
    {
      digitalWrite(YEL, HIGH);
      delay(500);
      digitalWrite(YEL, LOW);
    }
    if(v == 2)
    {
      digitalWrite(GRN, HIGH);
      delay(500);
      digitalWrite(GRN, LOW);
    }
    if(v == 3)
    {
      digitalWrite(BLU, HIGH);
      delay(500);
      digitalWrite(BLU, LOW);
    }
    delay(1000);
  }

  // Safety delay
  delay(500);

  // Player's sequence position
  int y = 0;

  // Player input:
  do{
    int rd = digitalRead(2);
    int yl = digitalRead(3);
    int gn = digitalRead(4);
    int bl = digitalRead(5);

    if(!rd)
    {
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
      player[y] =  0;
    }
    if(!yl)
    {
      digitalWrite(YEL, HIGH);
      delay(500);
      digitalWrite(YEL, LOW);
      player[y] =  1;
    }
    if(!gn)
    {
      digitalWrite(GRN, HIGH);
      delay(500);
      digitalWrite(GRN, LOW);
      player[y] =  2;
    }
    if(!bl)
    {
      digitalWrite(BLU, HIGH);
      delay(500);
      digitalWrite(BLU, LOW);
      player[y] =  3;
    }

    // As long as a button was pressed
    // Move to next in sequence
    if(!rd || !yl || !gn || !bl)
    {
      y++;
    }
    /*
     * I could check for error here
     * and end the sequence immediately
     * but I already recorded my video
     * using current code
     */
  }while(y < seqlen);

  // Check sequences for victory
  for(int z = 0; z < seqlen; z++)
  {
    if(sequence[z] != player[z])
    {
      success = false;
      break;
    }
  }

  // Display either win or loss
  if(success)
  {
    win();
    seqlen++;
  }
  else
  {
    error();
  }
}

// Error sequence
void error() {
  digitalWrite(RED, HIGH);
  digitalWrite(YEL, HIGH);
  digitalWrite(GRN, HIGH);
  digitalWrite(BLU, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);
  delay(1000);
  digitalWrite(YEL, LOW);
  delay(1000);
  digitalWrite(GRN, LOW);
  delay(1000);
  digitalWrite(BLU, LOW);

  // Restart
  delay(5000);
  setup();
}

// Victory!!!!
void win() {
  int c = 0;
  do {
    digitalWrite(RED, HIGH);
    digitalWrite(YEL, HIGH);
    digitalWrite(GRN, HIGH);
    digitalWrite(BLU, HIGH);
    delay(1000);
    digitalWrite(RED, LOW);
    digitalWrite(YEL, LOW);
    digitalWrite(GRN, LOW);
    digitalWrite(BLU, LOW);
    delay(1000);
    c++;
  } while(c <= 2);
  // Delay 4 seconds to let player
  // tell the difference
  delay(4000);
}
