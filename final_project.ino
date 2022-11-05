// Include Libraries
#include "Arduino.h"
#include "BTHC05.h"
#include "LiquidCrystal_PCF8574.h"
#include "Adafruit_NeoPixel.h"
#include "Button.h"

//refrance: circuito.io

// Pin Definitions
#define BTHC05_PIN_TXD  11
#define BTHC05_PIN_RXD  10
#define LEDRGB_1_PIN_DIN  2
#define PUSHBUTTON_1_PIN_2  3
#define PUSHBUTTON_2_PIN_2  4
#define PUSHBUTTON_3_PIN_2  5
#define PUSHBUTTON_4_PIN_2  6
#define PUSHBUTTON_5_PIN_2  7
#define PUSHBUTTON_6_PIN_2  8
#define PUSHBUTTON_7_PIN_2  9
#define PUSHBUTTON_8_PIN_2  12
#define PUSHBUTTON_9_PIN_2  13



// Global variables and defines
// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints. 
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
#define LedRGB_1_NUMOFLEDS 9
// object initialization
BTHC05 bthc05(BTHC05_PIN_RXD,BTHC05_PIN_TXD);
LiquidCrystal_PCF8574 lcdI2C;
Adafruit_NeoPixel LedRGB_1(LEDRGB_1_PIN_DIN);
Button pushButton_1(PUSHBUTTON_1_PIN_2);
Button pushButton_2(PUSHBUTTON_2_PIN_2);
Button pushButton_3(PUSHBUTTON_3_PIN_2);
Button pushButton_4(PUSHBUTTON_4_PIN_2);
Button pushButton_5(PUSHBUTTON_5_PIN_2);
Button pushButton_6(PUSHBUTTON_6_PIN_2);
Button pushButton_7(PUSHBUTTON_7_PIN_2);
Button pushButton_8(PUSHBUTTON_8_PIN_2);
Button pushButton_9(PUSHBUTTON_9_PIN_2);

//vars for tic-tac-toe game score
int player1Score = 0; 
int player2Score = 0; 
int result = 0;
int gameRound = 0; 

//vars for tic-tac-toe game logic
int turn = 1;
bool won = false; 
bool pushButton_1Val = false;
bool pushButton_2Val = false; 
bool pushButton_3Val = false; 
bool pushButton_4Val = false; 
bool pushButton_5Val = false; 
bool pushButton_6Val = false;
bool pushButton_7Val = false;  
bool pushButton_8Val = false;  
bool pushButton_9Val = false;  
  


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    bthc05.begin(9600);
    //This example uses HC-05 Bluetooth to communicate with an Android device.
    //Download bluetooth terminal from google play store, https://play.google.com/store/apps/details?id=Qwerty.BluetoothTerminal&hl=en
    //Pair and connect to 'HC-05', the default password for connection is '1234'.
    //You should see this message from your arduino on your android device
    bthc05.println("Bluetooth On....");
    // initialize the lcd
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 
    LedRGB_1.begin(); // This initializes the NeoPixel library.
    LedRGB_1.show(); // Initialize all leds to 'off'
    pushButton_1.init();
    pushButton_2.init();
    pushButton_3.init();
    pushButton_4.init();
    pushButton_5.init();
    pushButton_6.init();
    pushButton_7.init();
    pushButton_8.init();
    pushButton_9.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // HC - 05 Bluetooth Serial Module - Test Code
    String bthc05Str = "Testing bthc05... this will contain player score";
    //Receive String from bluetooth device
    if (bthc05.available())
    {
    //Read a complete line from bluetooth terminal
    bthc05Str = bthc05.readStringUntil('\n');
    // Print raw data to serial monitor
    Serial.print("BT Raw Data: ");
    Serial.println(bthc05Str);
    }
    //Send sensor data to Bluetooth device  
    bthc05.println("PUT YOUR SENSOR DATA HERE");
    }
    else if(menuOption == '2') {
    // LCD 16x2 I2C - Test Code
    // The LCD Screen will display the text of your choice.
    lcdI2C.clear();                          // Clear LCD screen.
    lcdI2C.print(" Welcome ");                   // Print print String to LCD on first line
    lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
    lcdI2C.print(" Tic-tac-toe ");                   // Print print String to LCD on second line
    delay(1000);

    }
    else if(menuOption == '3') {
    // LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) #1 - Test Code
    for(int i=0 ; i <= LedRGB_1_NUMOFLEDS ; i++){
    for (int k = 0 ; k <= 255 ; k++) {
    // set leds Color to RGB values, from 0,0,0 up to 255,255,255
    LedRGB_1.setPixelColor(i, LedRGB_1.Color(255-k,k,100)); // turn on green color on led #i.
    if (i > 0)
    LedRGB_1.setPixelColor(i-1, LedRGB_1.Color(0,0,0)); // turn off last led
    LedRGB_1.show(); //update led color to the hardware.
    delay(1);
    }
    }

    }
    else if(menuOption == '4') {
    // Mini Pushbutton Switch #1 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_1.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_1Val = pushButton_1.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_1Val);

    }
    else if(menuOption == '5') {
    // Mini Pushbutton Switch #2 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_2.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_2Val = pushButton_2.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_2Val);

    }
    else if(menuOption == '6') {
    // Mini Pushbutton Switch #3 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_3.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_3Val = pushButton_3.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_3Val);

    }
    else if(menuOption == '7') {
    // Mini Pushbutton Switch #4 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_4.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_4Val = pushButton_4.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_4Val);

    }
    else if(menuOption == '8') {
    // Mini Pushbutton Switch #5 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_5.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_5Val = pushButton_5.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_5Val);

    }
    else if(menuOption == '9') {
    // Mini Pushbutton Switch #6 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_6.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_6Val = pushButton_6.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_6Val);

    }
    else if(menuOption == '10') {
    // Mini Pushbutton Switch #7 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_7.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_7Val = pushButton_7.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_7Val);

    }
    else if(menuOption == '11') {
    // Mini Pushbutton Switch #8 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_8.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_8Val = pushButton_8.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_8Val);

    }
    else if(menuOption == '12') {
    // Mini Pushbutton Switch #9 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_9.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_9Val = pushButton_9.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_9Val);

    }

    else if(menuOption == '13'){
      //game logic
      Serial.print("game begin");
      result = rungame();
       
      //update lcd based on result here
      
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}


int rungame(){

  //make sure LEDs are turned off at the begining of the game 
  for(int i=0 ; i <= LedRGB_1_NUMOFLEDS ; i++){
    LedRGB_1.setPixelColor(i, LedRGB_1.Color(0,0,0)); //off
    LedRGB_1.show(); //update led color to the hardware.
  }
  won = false; 
  turn = 1; 
  
  while(turn < 10 && won = false){//there exists an unused matrix/LED of someone won
     
    if (player == 1){
      //oponents turn
      //wait for bluetooth signal to increase turn.
    }
    if (player == 2){ //RED PLAYER
      //this players turn
      if(pushButton_1Val == false){// 1st button has not been pressed
        pushButton_1Val = pushButton_1.read(); 
        if(pushButton_1Val == true){// button pressed
          LedRGB_1.setPixelColor(1, LedRGB_1.Color(255,0,0));
          diagonal[1]++; 
          collumn[1]++;
          row[1]++;
          turn++;
          player = 1; 
        }
      }

      if(pushButton_2Val == false){// 2nd button has not been pressed
        pushButton_2Val = pushButton_2.read(); 
        if(pushButton_2Val == true){// button pressed
          LedRGB_1.setPixelColor(2, LedRGB_1.Color(255,0,0));
          collumn[2]++;
          row[1]++;
          turn++;
          player = 1; 
        }
      }

      if(pushButton_3Val == false){// 3rd button has not been pressed
        pushButton_3Val = pushButton_3.read(); 
        if(pushButton_3Val == true){// button pressed
          LedRGB_1.setPixelColor(3, LedRGB_1.Color(255,0,0));
          diagonal[2]++; 
          collumn[3]++;
          row[1]++;
          turn = 1;
        }
      }

      if(pushButton_4Val == false){// 4th button has not been pressed
        pushButton_4Val = pushButton_4.read(); 
        if(pushButton_4Val == true){// button pressed
          LedRGB_1.setPixelColor(4, LedRGB_1.Color(255,0,0));
          collumn[1]++;
          row[2]++;
          turn++;
          player = 1; 
        }
      }

      if(pushButton_5Val == false){// 5th button has not been pressed
        pushButton_5Val = pushButton_5.read(); 
        if(pushButton_5Val == true){// button pressed
          LedRGB_1.setPixelColor(5, LedRGB_1.Color(255,0,0));
          diagonal[1]++; 
          diagonal[2]++;
          collumn[2]++;
          row[2]++;
          turn++;
          player = 1; 
        }
      }

      if(pushButton_6Val == false){// 6th button has not been pressed
        pushButton_6Val = pushButton_6.read(); 
        if(pushButton_6Val == true){// button pressed
          LedRGB_1.setPixelColor(6, LedRGB_1.Color(255,0,0));
          collumn[3]++;
          row[2]++;
          turn++;
          player = 1; 
        }
      }

      if(pushButton_7Val == false){// 7th button has not been pressed
        pushButton_7Val = pushButton_7.read(); 
        if(pushButton_7Val == true){// button pressed
          LedRGB_1.setPixelColor(7, LedRGB_1.Color(255,0,0)); 
          diagonal[2]++;
          collumn[1]++;
          row[3]++;
          turn++;
          player = 1; 
        }
      }

      if(pushButton_8Val == false){// 8th button has not been pressed
        pushButton_8Val = pushButton_8.read(); 
        if(pushButton_8Val == true){// button pressed
          LedRGB_1.setPixelColor(8, LedRGB_1.Color(255,0,0)); 
          collumm[2]++;
          row[3]++;
          turn++;
          player = 1; 
        }
      }

      if(pushButton_9Val == false){// 9th button has not been pressed
        pushButton_9Val = pushButton_9.read(); 
        if(pushButton_9Val == true){// button pressed
          LedRGB_1.setPixelColor(9, LedRGB_1.Color(255,0,0)); 
          diagonal[1]++;
          collumn[3]++;
          row[3]++;
          turn++;
          player = 1; 
        }
      }

        for(int i = 1; i < 4; i++){ //check for winning collumn or row
          if(collumn[i] == 3){
            won = true; 
            player1Score++; 
          }
          if(row[i] == 3){
            won = true; 
            player1Score++; 
          }
        }
        if(diagonal[1] == 3){
          won = true; 
          player1Score++; 
        }
        if(diagonal[2] == 3){
          won = true; 
          player1Score++; 
        }
        
        //send diagonal, collumn, row, turn and player information to other player through bluetooth. 
        //also need to send pushButton_nVal state.
        //also need to send if last play was winning and update score.

        if(won == true){// if the won flag has been set on your turn you have won
          return 2;
        }
    }
    if(won == true){// if the won flag has been set on oponent turn you have lost
      return 1;
    }
  }
  
}


//DEBUG
// Menu function for selecting the components to be tested
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) HC - 05 Bluetooth Serial Module"));
    Serial.println(F("(2) LCD 16x2 I2C"));
    Serial.println(F("(3) LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) #1"));
    Serial.println(F("(4) Mini Pushbutton Switch #1"));
    Serial.println(F("(5) Mini Pushbutton Switch #2"));
    Serial.println(F("(6) Mini Pushbutton Switch #3"));
    Serial.println(F("(7) Mini Pushbutton Switch #4"));
    Serial.println(F("(8) Mini Pushbutton Switch #5"));
    Serial.println(F("(9) Mini Pushbutton Switch #6"));
    Serial.println(F("(10) Mini Pushbutton Switch #7"));
    Serial.println(F("(11) Mini Pushbutton Switch #8"));
    Serial.println(F("(12) Mini Pushbutton Switch #9"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing HC - 05 Bluetooth Serial Module"));
        else if(c == '2') 
          Serial.println(F("Now Testing LCD 16x2 I2C"));
        else if(c == '3') 
          Serial.println(F("Now Testing LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) #1"));
        else if(c == '4') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #1"));
        else if(c == '5') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #2"));
        else if(c == '6') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #3"));
        else if(c == '7') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #4"));
        else if(c == '8') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #5"));
        else if(c == '9') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #6"));
        else if(c == '10') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #7"));
        else if(c == '11') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #8"));
        else if(c == '12') 
          Serial.println(F("Now Testing Mini Pushbutton Switch #9"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
