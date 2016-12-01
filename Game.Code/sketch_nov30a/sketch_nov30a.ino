int game = 0;
//--------------------//
bool g1 = false;
bool g2 = false;
bool g3 = false;
bool g4 = false;
int attempts;
//--------------------//
int correctCount = 0;
const String Code[3] = {"666*420", "#3825968", "8675309*"};
const int switches[3][3] = {{LOW, LOW, HIGH},{LOW, HIGH, LOW}, {LOW, LOW, LOW}};
const String combo[3] = {"uuddlrlr", "uuddllrr", "ulrlludr"}; //note combo must be 8 digits
const int note[3] = {440, 587, 261};
//--------------------//
int comboCount = 0;
//--------------------//
int ledgreenpin = 6;
int ledpinjoy = 7;
int ledpinpot = 8;
int buttonledpin = 9;
//--------------------//
int analogpinjoy1 = A0;
int analogpinjoy2 = A1;
int analogpinjoy3 = A2;
//--------------------//
int analogpinpot3 = A5;
//--------------------//
int amberswitch = 2;
int redswitch = 3;
int greenswitch = 4;
//--------------------//
int buttonpin = 5;
//--------------------//
int buzzmain = 10;
int buzzsecondary = 11;
//--------------------//
int randNum;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //--------------------//
  pinMode(amberswitch, INPUT);
  pinMode(redswitch, INPUT);
  pinMode(greenswitch, INPUT);
  //--------------------//
  pinMode(analogpinjoy1, INPUT);
  pinMode(analogpinjoy2, INPUT);
  pinMode(analogpinjoy3, INPUT);
  //--------------------//
  pinMode(analogpinpot3, INPUT);
  //--------------------//
  pinMode(ledgreenpin, OUTPUT);
  pinMode(ledpinjoy, OUTPUT);
  pinMode(ledpinpot, OUTPUT);
  pinMode(buttonledpin, OUTPUT);
  //--------------------//
  pinMode(buttonpin, INPUT_PULLUP);
  //--------------------//
  digitalWrite(ledgreenpin, HIGH);
  digitalWrite(ledpinjoy, LOW);
  digitalWrite(ledpinpot, LOW);
  digitalWrite(buttonledpin, LOW);
  
 
  randomSeed(analogRead(A3));
  randNum = random() %3;
  while(!Serial.available())
  {
     
  }
  attempts = Serial.read();
  attempts -= 48;
  
  if (attempts > 9)
  attempts = 10;

  if (attempts <=0)
  attempts = 1;
  
  Serial.println(attempts);
}

void loop() {

while(attempts <= 0)
{
  lose();
  delay(600);
}

  String input;
  while (Serial.available())
  {
    input = Serial.readString();
    if (game == 0)
      screen(input);

  }

  if (digitalRead(buttonpin) == LOW)
  {
    updateleds();
    game++;
    game = game % 4;
    delay(200);
  }
  if (game == 1)
  {
    joy();
  }
  if (game == 2)
  {
    pot();
  }
  if (game == 3)
  {
    switcher();
  }
  if(g1 && g2 && g3 && g4)
  {
    win();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void updateleds()
{
  if (game == 0)
  {
    digitalWrite(ledgreenpin, LOW);
    digitalWrite(ledpinjoy, HIGH);
    digitalWrite(ledpinpot, LOW);
    digitalWrite(buttonledpin, LOW);

  }
  if (game == 1)
  {
    digitalWrite(ledgreenpin, LOW);
    digitalWrite(ledpinjoy, LOW);
    digitalWrite(ledpinpot, HIGH);
    digitalWrite(buttonledpin, LOW);
  }
  if (game == 2)
  {
    digitalWrite(ledgreenpin, LOW);
    digitalWrite(ledpinjoy, LOW);
    digitalWrite(ledpinpot, LOW);
    digitalWrite(buttonledpin, HIGH);
  }
  if (game == 3)
  {
    digitalWrite(ledgreenpin, HIGH);
    digitalWrite(ledpinjoy, LOW);
    digitalWrite(ledpinpot, LOW);
    digitalWrite(buttonledpin, LOW);
  }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void screen(String& input)
{
  if (input == Code[randNum])
  {
    winSound();
    input = "";
    g1 = true;
  }
  else if (input == "")
  {
    noTone(1);
  }
  else
  {
    loseSound();
    input = "";
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void switcher()
{
  if (g4 == false)
  {
    if (digitalRead(amberswitch) == switches[randNum][0] && digitalRead(redswitch) == switches[randNum][1] && digitalRead(greenswitch) == switches[randNum][2])
    {
      winSound();
      g4 = true;
    }
  }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pot()
{
  if (g3 == false)
  {
    tone(11, note[randNum], 14);
    delay(14);
    int temp = analogRead(A5);
    tone(10, temp, 14);
    delay(14);

    if (temp < note[randNum]+5 && temp > note[randNum] - 5)
    {
      correctCount++;
    }
    else
    {
      correctCount = 0;
    }

    if (correctCount >= 50)
    {
      winSound();
      g3 = true;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void joy()
{
  if (g2 == false)
  {
    int tempX = analogRead(analogpinjoy1);
    int tempY = analogRead(analogpinjoy2);
    char direct;

    int x = map(tempX, 0, 1024, 0, 10);
    int y = map(tempY, 0, 1024, 0, 10);

    if (x == 0 && y == 5)
    {
      direct = 'd';
      tone(10, 300, 200);
    }
    else if (x == 5 && y == 0)
    {
      direct = 'l';
      tone(10, 440, 200);
    }
    else if (x == 9 && y == 5)
    {
      direct = 'u';
      tone(10, 660, 200);
    }
    else if (x == 5 && y == 9)
    {
      direct = 'r';
      tone(10, 520, 200);
    }

    Serial.println(direct);
    if (direct == combo[randNum][comboCount])
    {
      comboCount++;
    }
    else if (comboCount == 8)
    {
      winSound();
      g2 = true;
      comboCount = 0;
    }
    else
    {
      if (direct == 'u' || direct == 'd' || direct == 'l' || direct == 'r')
      {
        comboCount = 0;
        loseSound();
      }
    }
    delay(200);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loseSound()
{
  tone(10, 208, 140);
  delay(50);
  tone(10, 196, 140);
  delay(50);
  tone(10, 185, 140);
  delay(50);
  tone(10, 175, 280);
attempts--;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void winSound()
{
  tone(10, 585, 150);
  delay(50);
  tone(10, 740, 150);
  delay(50);
  tone(10, 880, 150);
  delay(50);
  tone(10, 1175, 150);
  delay(50);
}

///////////////////////////////////////////////////////////////////////////////////////////
void win()
{
  tone(10, 392, 100);
  delay(300);
  tone(10, 392, 100);
  delay(100);
  tone(10, 587, 400);
  delay(400);
  tone(10, 494, 200);
  delay(200);
  
  tone(10, 698, 200);
  delay(200);
  tone(10, 587, 200);
  delay(200);
  tone(10, 880, 200);
  delay(200);
  tone(10, 698, 200);
  delay(200);
  
  tone(10, 1046, 600);
  delay(600);
}
////////////////////////////////////////////////////////////////////
void lose()
{
  tone(10, 523, 200);
  delay(200);
  tone(10, 294, 200);
  delay(300);
  tone(10, 262, 100);
  delay(100);
  tone(10, 392, 600);
  delay(600);
  for (int i = 622; i > 261; i=i -20)
  {
    tone(10, i, 14);
    delay(14);
    tone(11, i-50, 14);
    delay(14);
  }
}


