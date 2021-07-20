#include "LiquidCrystal_I2C.h"

int  A_SIG = 0, B_SIG = 1;

int listPos0 = 0;
int listPos1 = 1;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display




const byte EncoderPinA = 2;
const byte EncoderPinB = 3;
const int debounce = 750;


String drinkList[] = {
"1111                              " ,
"2222                              ", 
"3333                              ", 
"5555                              ",
"6666                              ",
"7777                              ",
"8888                              "
};




void setup() {
  pinMode(EncoderPinA, INPUT_PULLUP);
  pinMode(EncoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), A_FALL, RISING);




  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0); //line 1
  lcd.print("lcd on");
  delay(1000);


  Serial.begin(115200);
}//setup

void A_FALL() {
  detachInterrupt(digitalPinToInterrupt(EncoderPinA));

  B_SIG = digitalRead(EncoderPinB);
  A_SIG = digitalRead(EncoderPinA);

  delay(1000);

  if (B_SIG && A_SIG){
     listPos0++;//moving reverse
  listPos1++;//moving reverse
  }
   

  if (!B_SIG && A_SIG){
    listPos0--;//moving reverse
  listPos1--;//moving reverse
  }
    


  if (listPos0 < 0)
    listPos0 = (sizeof(drinkList) / sizeof(*drinkList)) - 1;

  if (listPos0 > (sizeof(drinkList) / sizeof(*drinkList)) - 1)
    listPos0 = 0;


  if (listPos1 < 0)
    listPos1 = (sizeof(drinkList) / sizeof(*drinkList)) - 1;

  if (listPos1 > (sizeof(drinkList) / sizeof(*drinkList)) - 1)
    listPos1 = 0;

  Serial.println(listPos1);
  attachInterrupt(digitalPinToInterrupt(EncoderPinA), A_FALL, RISING);
}





void loop()
{

  lcd.setCursor(0, 0); //line 1
  lcd.print("*" + drinkList[listPos0]);
  lcd.setCursor(0, 1); //line 2
  lcd.print(drinkList[listPos1]);

}
