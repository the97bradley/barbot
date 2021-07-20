//TODO: Add to documentation
//TODO: figure out how to program over wifi
//https://techtutorialsx.com/2016/10/22/esp8266-webserver-getting-query-parameters/
//https://www.youtube.com/watch?v=dDktrUOnqq4
//https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html
//https://techtutorialsx.com/2017/03/26/esp8266-webserver-accessing-the-body-of-a-http-request/








#include "LiquidCrystal_I2C.h"
#include "drinks.h"



#include <stdio.h>
#include <MemoryFree.h>
#include <EEPROM.h>
#include <stdlib.h>

const int MILLISEC_PER_OZ = 900;




const char *drinksJson =
  "Here, on the other hand, I've gone crazy \
and really let the literal span several lines, \
without bothering with quoting each line's \
content. This works, but you can't indent.";

//vars related to encoder rotation tracking - unnecessary with no screen
int  A_SIG = 0, B_SIG = 1;
int listPos0 = 0;
int listPos1 = 1;
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
const byte EncoderPinA = 2;
const byte EncoderPinB = 3;
const byte ButtonPin=19;
String drinkList[] = { //array of all the drinks used for the display

"Amaretto Sour                                  ",
"Kentucky Mule                                  ",
"Old Fashioned                                   ",
"Bourbon Sour                                  ",
"Margarita                                  ",
"Blue Margarita                                  ",
"Tequila Sunrise                                  ",
"Siesta                                  ",
"Mexican Mule                                  ",
"Orange Paloma                                  ",
"Mojito                                  ",
"Daquiri                                  ",
"Vodka Gimlet                                  ",
"Cosmo                                  ",
"Moscow Mule                                  ",
"Double Strike                                  ",
"Vodka Cran                                  ",
"Lemon Drop Martini                                  ",
"Kamikaze                                  ",
"Screwdriver                                  ",
"Blue Monday                                  ",
"Cranberry Kiss                                  ",
"Gin Gimlet                                  ",
"Tom Collins                                  ",
"Southside                                  ",
"Bluebird                                  ",
"Mudslide                                  ",
"White Russian                                  ",
"Irish Cactus                                  ",
"Espresso Martini                                  ",
"Sugar Cookie Martini                                  ",
"Girl Scout Cookie                                  ",
"Mind Eraser                                  ",
"Toasted Almond                                  ",
"Italian Sunset                                  ",
"Blue Hawaiian                                  ",
"Sex on the Beach                                  ",
"Jungle Bird                                  "
};

//offset of pin connection to the pump number
const int pinOffset = 21;







void setup()
{

  //Setup related to encoder/ screen
  pinMode(EncoderPinA, INPUT_PULLUP);
  pinMode(EncoderPinB, INPUT_PULLUP);
    pinMode(ButtonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(EncoderPinA), A_FALL, RISING);

  //set all pump pins to output and write them to high since the relay is low true
  //I put my pumps on pins 22->46 specifically so I could do this
  for (int i = 22; i < 47; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);


  }

  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0); //line 1
  lcd.print("lcd on");
  delay(1000);


  Serial.begin(115200);

}




//interupt func for the encoder - unnecessary without it
void A_FALL() {
  detachInterrupt(digitalPinToInterrupt(EncoderPinA));

  B_SIG = digitalRead(EncoderPinB);
  A_SIG = digitalRead(EncoderPinA);

  delay(1000);

  if (B_SIG && A_SIG) {
    listPos0++;//moving reverse
    listPos1++;//moving reverse
  }


  if (!B_SIG && A_SIG) {
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

//RGB display code is run in the loop -
void loop() {



  lcd.setCursor(0, 0); //line 1
  lcd.print("*" + drinkList[listPos0]);
  lcd.setCursor(0, 1); //line 2
  lcd.print(drinkList[listPos1]);

    if (digitalRead(ButtonPin)==0){
      drinkSwitcher(drinkList[listPos0]);
      delay(1000);
  
    }

}


// API code is run in the serialEvent function
//for testing change all "Serial3" to "Serial"
void serialEvent() { //change for testing serialEvent3
  String inString = Serial.readString();  //change for testing


  //
  //  //for testing purposes (e.g. "test 1") will test pump number 1 or just "test" will cycle all the pumps for 1 second
    if (inString.indexOf ("test") != -1) {
  
  
  
  
  
  
      //check if we are testing a single pump or all of them
      if (inString.indexOf (" ")!=-1){
                int pumpNum = (inString.substring(inString.indexOf(" "))).toInt();
 
         Serial.println("Testing pump " + String(pumpNum));
  
  
      digitalWrite(pumpNum + pinOffset, LOW);
      delay(MILLISEC_PER_OZ);
      digitalWrite(pumpNum + pinOffset, HIGH);
   
      }
      else {
  
      Serial.println("running test");
  
      for (int i = 22; i < 47; i++) {
        digitalWrite(i, LOW);
        Serial.println("testing pump " + String(i - 21));
        delay(1000);
        digitalWrite(i, HIGH);
        delay(500);
  
      }
    }
    }
  else{
  drinkSwitcher(inString);

  inString = "";

}
}


void runPump(int pump, double oz) {
  if (oz >1){
digitalWrite(pump + pinOffset, LOW);
  delay(MILLISEC_PER_OZ);
  digitalWrite(pump + pinOffset, HIGH);
    delay(1000);
    runPump(pump, oz-1);
  }else{
    
digitalWrite(pump + pinOffset, LOW);
  delay(MILLISEC_PER_OZ*oz);
  digitalWrite(pump + pinOffset, HIGH);
  }

}


void makeDrink(drink d) {
  Serial.println("Making " + String(d.name));
  for (int i = 1; i < 25; i++) {
    if (d.mixersArray[i] > 0) {
      runPump(i , d.mixersArray[i]);
      delay(1000);
    }

  }

}




//switch on the standard drink names and modify the reference to the current drink to be the specified drink
void drinkSwitcher(String inputValue) {

Serial.println("input into drink switcher: " + inputValue);

  //  char * inputValue = in.c_str();


  drink currentDrink ;

  if (inputValue.indexOf( "Amaretto Sour") != -1) {
    currentDrink.name = "Amaretto Sour";
    currentDrink.extras = "egg white, 2 dashes Angostura bitters";
    currentDrink.mixersArray[BOURBON_PUMP] = 0.5;
    currentDrink.mixersArray[GIN_PUMP] = 1;
    currentDrink.mixersArray[LEMON_PUMP] = 1;
  }


  else if (inputValue.indexOf( "Kentucky Mule") != -1) {
    currentDrink.name = "Kentucky Mule";
    currentDrink.extras = "";
    currentDrink.mixersArray[BOURBON_PUMP] = 2;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
    currentDrink.mixersArray[GINGER_BEER_PUMP] = 4;
  }

  else if (inputValue.indexOf( "Old Fashioned ") != -1) {
    currentDrink.name = "Old Fashioned ";
    currentDrink.extras = "2 dash Angostura bitters and Orange peel";
    currentDrink.mixersArray[BOURBON_PUMP] = 2;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.1666;
  }

  else if (inputValue.indexOf( "Bourbon Sour") != -1) {
    currentDrink.name = "Bourbon Sour";
    currentDrink.extras = "egg white";
    currentDrink.mixersArray[BOURBON_PUMP] = 2;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.1666;
    currentDrink.mixersArray[LEMON_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Margarita") != -1) {
    currentDrink.name = "Margarita";
    currentDrink.extras = "";
    currentDrink.mixersArray[TEQUILA_PUMP] = 2;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Blue Margarita") != -1) {
    currentDrink.name = "Blue Margarita";
    currentDrink.extras = "";
    currentDrink.mixersArray[TEQUILA_PUMP] = 2;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 1;
    currentDrink.mixersArray[BLUE_CURACAO_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Tequila Sunrise") != -1) {
    currentDrink.name = "Tequila Sunrise";
    currentDrink.extras = "";
    currentDrink.mixersArray[TEQUILA_PUMP] = 1.5;
    currentDrink.mixersArray[ORANGE_PUMP] = 6;
    currentDrink.mixersArray[GRENADINE_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Siesta") != -1) {
    currentDrink.name = "Siesta";
    currentDrink.extras = "";
    currentDrink.mixersArray[TEQUILA_PUMP] = 1;
    currentDrink.mixersArray[ORANGE_PUMP] = 0.5;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.5;
    currentDrink.mixersArray[CAMPARI_PUMP] = 0.5;
  }

  else if (inputValue.indexOf( "Mexican Mule") != -1) {
    currentDrink.name = "Mexican Mule";
    currentDrink.extras = "";
    currentDrink.mixersArray[TEQUILA_PUMP] = 2;
    currentDrink.mixersArray[GINGER_BEER_PUMP] = 4;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
  }

  else if (inputValue.indexOf( "Orange Paloma") != -1) {
    currentDrink.name = "Orange Paloma";
    currentDrink.extras = "";
    currentDrink.mixersArray[TEQUILA_PUMP] = 1.5;
    currentDrink.mixersArray[ORANGE_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
  }

  else if (inputValue.indexOf( "Mojito") != -1) {
    currentDrink.name = "Mojito";
    currentDrink.extras = "mint leaves";
    currentDrink.mixersArray[RUM_PUMP] = 2;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.5;
    currentDrink.mixersArray[LIME_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Daquiri") != -1) {
    currentDrink.name = "Daquiri";
    currentDrink.extras = "";
    currentDrink.mixersArray[RUM_PUMP] = 2;
    currentDrink.mixersArray[SIMPLE_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Vodka Gimlet") != -1) {
    currentDrink.name = "Vodka Gimlet";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 2;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.75;
    currentDrink.mixersArray[LIME_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Cosmo") != -1) {
    currentDrink.name = "Cosmo";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1.5;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
    currentDrink.mixersArray[CRANBERRY_PUMP] = 0.25;
  }

  else if (inputValue.indexOf( "Moscow Mule") != -1) {
    currentDrink.name = "Moscow Mule";
    currentDrink.extras = "";
    currentDrink.mixersArray[GINGER_BEER_PUMP] = 5;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
  }

  else if (inputValue.indexOf( "Double Strike") != -1) {
    currentDrink.name = "Double Strike";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1.5;
    currentDrink.mixersArray[BLUE_CURACAO_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 0.375;
    currentDrink.mixersArray[CRANBERRY_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Vodka Cran") != -1) {
    currentDrink.name = "Vodka Cran";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1;
    currentDrink.mixersArray[ORANGE_PUMP] = 0.2;
    currentDrink.mixersArray[LIME_PUMP] = 0.2;
    currentDrink.mixersArray[CRANBERRY_PUMP] = 4.5;
  }

  else if (inputValue.indexOf( "Lemon Drop Martini") != -1) {
    currentDrink.name = "Lemon Drop Martini";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 0.5;
    currentDrink.mixersArray[LEMON_PUMP] = 0.75;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.25;
  }

  else if (inputValue.indexOf( "Kamikaze") != -1) {
    currentDrink.name = "Kamikaze";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 0.75;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 0.75;
    currentDrink.mixersArray[LIME_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Screwdriver") != -1) {
    currentDrink.name = "Screwdriver";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1.5;
    currentDrink.mixersArray[ORANGE_PUMP] = 4;
  }

  else if (inputValue.indexOf( "Blue Monday") != -1) {
    currentDrink.name = "Blue Monday";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1.5;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 0.5;
    currentDrink.mixersArray[BLUE_CURACAO_PUMP] = 0.25;
  }

  else if (inputValue.indexOf( "Cranberry Kiss") != -1) {
    currentDrink.name = "Cranberry Kiss";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1;
    currentDrink.mixersArray[AMARETTO_PUMP] = 0.5;
    currentDrink.mixersArray[ORANGE_PUMP] = 0.1875;
    currentDrink.mixersArray[CRANBERRY_PUMP] = 2;
  }

  else if (inputValue.indexOf( "Gin Gimlet") != -1) {
    currentDrink.name = "Gin Gimlet";
    currentDrink.extras = "";
    currentDrink.mixersArray[GIN_PUMP] = 2;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.75;
    currentDrink.mixersArray[LIME_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Tom Collins") != -1) {
    currentDrink.name = "Tom Collins";
    currentDrink.extras = "maraschino cherry";
    currentDrink.mixersArray[GIN_PUMP] = 2;
    currentDrink.mixersArray[LEMON_PUMP] = 1;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.5;
    currentDrink.mixersArray[SELTZER_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Southside") != -1) {
    currentDrink.name = "Southside";
    currentDrink.extras = "mint leaves";
    currentDrink.mixersArray[GIN_PUMP] = 2;
    currentDrink.mixersArray[LEMON_PUMP] = 1;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.5;
  }

  else if (inputValue.indexOf( "Bluebird") != -1) {
    currentDrink.name = "Bluebird";
    currentDrink.extras = "2 dashes bitters";
    currentDrink.mixersArray[GIN_PUMP] = 2;
    currentDrink.mixersArray[TRIPLE_SEC_PUMP] = 1;
    currentDrink.mixersArray[BLUE_CURACAO_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Mudslide") != -1) {
    currentDrink.name = "Mudslide";
    currentDrink.extras = "1.5 oz cream";
    currentDrink.mixersArray[VODKA_PUMP] = 1;
    currentDrink.mixersArray[KAHLUA_PUMP] = 1;
    currentDrink.mixersArray[BAILEYS_PUMP] = 1.5;
  }

  else if (inputValue.indexOf( "White Russian") != -1) {
    currentDrink.name = "White Russian";
    currentDrink.extras = "1 oz cream";
    currentDrink.mixersArray[VODKA_PUMP] = 2;
    currentDrink.mixersArray[KAHLUA_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Irish Cactus") != -1) {
    currentDrink.name = "Irish Cactus";
    currentDrink.extras = "";
    currentDrink.mixersArray[BAILEYS_PUMP] = 2;
    currentDrink.mixersArray[TEQUILA_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Espresso Martini") != -1) {
    currentDrink.name = "Espresso Martini";
    currentDrink.extras = "1 oz coffee";
    currentDrink.mixersArray[VODKA_PUMP] = 2;
    currentDrink.mixersArray[KAHLUA_PUMP] = 0.75;
  }

  else if (inputValue.indexOf( "Sugar Cookie Martini") != -1) {
    currentDrink.name = "Sugar Cookie Martini";
    currentDrink.extras = "";
    currentDrink.mixersArray[TEQUILA_PUMP] = 1.5;
    currentDrink.mixersArray[AMARETTO_PUMP] = 1;
    currentDrink.mixersArray[BAILEYS_PUMP] = 1.5;
  }


  else if (inputValue.indexOf( "Mind Eraser") != -1) {
    currentDrink.name = "Mind Eraser";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 1.5;
    currentDrink.mixersArray[KAHLUA_PUMP] = 1.5;
    currentDrink.mixersArray[SELTZER_PUMP] = 1.5;
  }

  else if (inputValue.indexOf( "Toasted Almond") != -1) {
    currentDrink.name = "Toasted Almond";
    currentDrink.extras = "2 oz cream";
    currentDrink.mixersArray[KAHLUA_PUMP] = 1;
    currentDrink.mixersArray[AMARETTO_PUMP] = 1;
  }

  else if (inputValue.indexOf( "Italian Sunset") != -1) {
    currentDrink.name = "Italian Sunset";
    currentDrink.extras = "";
    currentDrink.mixersArray[AMARETTO_PUMP] = 2;
    currentDrink.mixersArray[ORANGE_PUMP] = 3;
    currentDrink.mixersArray[SELTZER_PUMP] = 3;
    currentDrink.mixersArray[GRENADINE_PUMP] = 0.1;
  }

  else if (inputValue.indexOf( "Blue Hawaiian") != -1) {
    currentDrink.name = "Blue Hawaiian";
    currentDrink.extras = "";
    currentDrink.mixersArray[PINEAPPLE_PUMP] = 3;
    currentDrink.mixersArray[VODKA_PUMP] = 0.75;
    currentDrink.mixersArray[RUM_PUMP] = 0.75;
    currentDrink.mixersArray[BLUE_CURACAO_PUMP] = 0.5;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
    currentDrink.mixersArray[LEMON_PUMP] = 0.5;
  }

  else if (inputValue.indexOf( "Sex on the Beach") != -1) {
    currentDrink.name = "Sex on the Beach";
    currentDrink.extras = "";
    currentDrink.mixersArray[VODKA_PUMP] = 2;
    currentDrink.mixersArray[PEACH_SCHNAPPS_PUMP] = 1;
    currentDrink.mixersArray[ORANGE_PUMP] = 2;
    currentDrink.mixersArray[CRANBERRY_PUMP] = 2;
  }

  else if (inputValue.indexOf( "Jungle Bird") != -1) {
    currentDrink.name = "Jungle Bird";
    currentDrink.extras = "";
    currentDrink.mixersArray[RUM_PUMP] = 1.5;
    currentDrink.mixersArray[CAMPARI_PUMP] = 0.75;
    currentDrink.mixersArray[PINEAPPLE_PUMP] = 1.5;
    currentDrink.mixersArray[LIME_PUMP] = 0.5;
    currentDrink.mixersArray[SIMPLE_PUMP] = 0.5;
  }else{
      Serial.println("Not in drink list: "+inputValue);
      return;

  }

  makeDrink(currentDrink);
}




//
//  size_t drinkArrSz   = sizeof(drinkArr) / sizeof(drinkArr[0]);
//
//  Serial.println ("array size  " + String(drinkArrSz));
//
//
//

//for(int i=0; i< DRINK_ARR_SZ; i++){
//  if (strcmp(drinksArr[i].name,  nameCharArr) ==0){
//    makeDrink(drinksArr[i]);
//    return;
//  }
//}
//Serial.println("Unknown input: " + inputValue);
//
//}
