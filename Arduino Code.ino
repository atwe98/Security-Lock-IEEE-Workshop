#include <Servo.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

Servo myservo;                //servo objectg creation

const int rs = 12, en = 14, d4 = 5, d5 = 4, d6 = 3, d7 = 2;   //selecting LCD pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                    //lcd object creation

//setting keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', 'x'},       //Mapping keypad keys
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {13, 10, 9, 8};       //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 1, 0};         //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );     //keypad object creation

const char k[] = {'0', '0', '0', '0'};      //Passcode
char p[4];                //Empty array to store pressed button values
int button_counter=0;                //variable to store number of pressed buttons

void setup() {
  
  lcd.begin(16, 2);                         //Setting up LCD
  lcd.setCursor(0, 0);
  lcd.print("Enter Passcode: ");
  lcd.setCursor(0, 1);

  myservo.attach(11);             //selecting servo to pin 11
  myservo.write(0);              // tell servo to go to position 0 deg
}
void loop() {
  bool wrong;         //boolean to check if passcode is correct
  char key = keypad.getKey();
  delay(5);
  if (key) {

    if (key == 'C') {
      button_counter = 0;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      myservo.write(0);
    }
    else {
      lcd.print('*');
      p[button_counter] = key;
      button_counter++;
    }
  }

  if (button_counter == 4) {
    wrong = false;
    for (int i = 0; i < 4; i++)
      if (p[i] != k[i])
        wrong = true;
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    if (wrong) {
      lcd.print("Invalid Passcode");
    }
    else {
      lcd.print("Access Granted");
      myservo.write(90);              // tell servo to go to position 90 deg
    }
    button_counter = 0;
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    myservo.write(0);
  }
}
