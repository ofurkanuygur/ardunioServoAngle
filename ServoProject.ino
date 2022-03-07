#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

int pinCounter = 0;
int maxCounter = 3;
int keyPresses[3] = {0, 0, 0};
int angle = 0;
int firstStep = 1;
Servo servo;
int servoPin = A4;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {4, 3, 2, A5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5}; //connect to the column pinouts of the keypad

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  firstStepSet();
  servo.attach(servoPin);

}

void loop() {


  char key = keypad.getKey();

  if (key) {
    if (key == 0x23 || key == 0x2A)
    {
      lcd.clear();
      reset();
    }
    else
    {
      angle += firstStep * (key - 0x30);
      firstStep /= 10;
      if (pinCounter == maxCounter - 1)
      {
        ServoSendAngle(angle);
      }
      else
      {
        pinCounter++;
      }
    }
  }
}

void ServoSendAngle(int angle)
{
  if (angle > 180)
  {
    lcd.print((String)angle + "Buyuktur180");
    angle = 180;
  }
  else
  {
    lcd.print((String)angle + "derece");
    servo.write(angle);
  }
}
void firstStepSet()
{
  firstStep = 1;
  for (int i = 0; i < maxCounter - 1; i++)
    firstStep *= 10;

}
void reset()
{
  firstStepSet();
  angle = 0;
  pinCounter = 0;
}
