#include <SimpleButton.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
//=====================================DISPLAY SET-UP FUNCTION=================================//
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
//======================BUTTONS SETUP FUNCTION==============================================//
using namespace simplebutton;
Button* UP = NULL;
Button* DOWN = NULL;
Button* ACCEPT = NULL;
Button* RIGHT = NULL;
Button* LEFT = NULL;


////////////////////////////////        SETTINGS             /////////////////////////////////

int LDE = D8;
int up = D3;
int down = D4;
int accpt = RX;
int rght = D6;
int lft = D7;

////////////////////////////////////////////////////////////////////////////////////////////////////

//=========================================PAGE SETUP FUNCTIONs=========================================//
enum pageType {MAIN_MENU,SINGLESHOT_SETTING,SINGLEBULB_SETTING,TIMELAPSEM_SETTING,TIMELAPSEBULB_SETTING,CUSTOMTL_SETTING, SUB_MENU1, SUB_MENU2, SUB_MENU3,SUB_MENU4};
enum pageType currPage = MAIN_MENU;
//=================================================MAIN-SETUP=========================================//
void setup() {
  pinMode(LDE, OUTPUT);
  UP = new ButtonPullup(up);
  DOWN = new ButtonPullup(down);
  ACCEPT = new ButtonPullup(accpt);
  RIGHT = new ButtonPullup(rght);
  LEFT = new ButtonPullup(lft);
//-------------------------------------DISPLAY SETUP-----------------------------------------------//
  Wire.begin();
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.display();
//  Serial.begin(9600);
}
//==============================================MAIN-LOOP========================================//
void loop() {
  switch (currPage) {
    case MAIN_MENU:                page_MainMenu(); break;
    case SINGLESHOT_SETTING:       page_SINGLESHOT_SETTING(); break;
    case SINGLEBULB_SETTING:       page_SINGLEBULB_SETTING(); break;
    case TIMELAPSEM_SETTING:       page_TIMELAPSEM_SETTING(); break;
    case TIMELAPSEBULB_SETTING:    page_TIMELAPSEBULB_SETTING(); break;
    case CUSTOMTL_SETTING:         page_CUSTOMTL_SETTING(); break;
    case SUB_MENU1:                page_SUB_MENU1(); break;
    case SUB_MENU2:                page_SUB_MENU2(); break;
    case SUB_MENU3:                page_SUB_MENU3(); break;
    case SUB_MENU4:                page_SUB_MENU4(); break;
  }
}
//=====================================================MAIN MENU =================================//
void page_MainMenu(void) {
  boolean updateDisplay = true;
  uint32_t loopStartMs;
  uint8_t sub_pos = 1;
  boolean isUpButtonPressed = false;
  boolean wasUpButtonPressed = false;
  boolean isDownButtonPressed = false;
  boolean wasDownButtonPressed = false;
  boolean isAcceptButtonPressed = false;
  boolean wasAcceptButtonPressed = false;
  boolean isLeftButtonPressed = false; 
  boolean wasLeftButtonPressed = false; 
  boolean isRightButtonPressed = false; 
  boolean wasRightButtonPressed = false; 

  while (currPage == MAIN_MENU) {
    loopStartMs = millis();
    if (updateDisplay) {
      display.clearDisplay();
      display.setCursor(0, 5);
      if (sub_pos == 1) { display.println("|>> SINGLE SHOT"); } else { display.println("      SINGLE SHOT"); }
      display.setCursor(0, 15);
      if (sub_pos == 2) { display.println("|>> SINGLE/BULB"); } else { display.println("      SINGLE/BULB"); }
      display.setCursor(0, 25);
      if (sub_pos == 3) { display.println("|>> TIMELAPSE(M)"); } else { display.println("      TIMELAPSE(M)"); }
      display.setCursor(0, 35);
      if (sub_pos == 4) { display.println("|>> TIMELAPSE(BULB)"); } else { display.println("      TIMELAPSE(BULB)"); }
      display.setCursor(0, 45);
      if (sub_pos == 5) { display.println("|>> CUSTOM/TL"); } else { display.println("      CUSTOM/TL"); }
      display.display();
      updateDisplay = false;
    }
    UP->update();
    isUpButtonPressed = UP->clicked();
    DOWN->update();
    isDownButtonPressed = DOWN->clicked();
    ACCEPT->update();
    isAcceptButtonPressed = ACCEPT->clicked();
    LEFT->update();
    isLeftButtonPressed = LEFT->clicked();
    RIGHT->update();
    isRightButtonPressed = RIGHT->clicked();
    
//---------------------------------------------------UP BUTTON HANDLING----------------------------------------//
        if (isUpButtonPressed && !wasUpButtonPressed) {
          sub_pos--;
          if(sub_pos < 1) {
            sub_pos = 5;
          }
          updateDisplay = true;
        }
//--------------------------------------------------DOWN BUTTON HANDING-----------------------------------------//
        if (isDownButtonPressed && !wasDownButtonPressed) {
          sub_pos++;
          if(sub_pos > 5){
            sub_pos = 1;
          }
          updateDisplay = true;
        }
//------------------------------------------------ACCEPT BUTTON HANDLING------------------------------------------//
        if (isAcceptButtonPressed && !wasAcceptButtonPressed) {
                switch (sub_pos) {
        case 1:
          currPage = SINGLESHOT_SETTING;
          break;
        case 2:
          currPage = SINGLEBULB_SETTING;
          break;
        case 3:
          currPage = TIMELAPSEM_SETTING;
          break;
        case 4:
          currPage = TIMELAPSEBULB_SETTING;
          break;
        case 5:
          currPage = CUSTOMTL_SETTING;
          break;
      }
      updateDisplay = true;
        }
//--------------------------------------------------Left Button Handling-----------------------------------------------//
    if (isLeftButtonPressed && !wasLeftButtonPressed) {

    }
//-----------------------------------------------------Right button handling--------------------------------------------//
    if (isRightButtonPressed && !wasRightButtonPressed) {
      
    }
//==========================================================================================================================//

    wasLeftButtonPressed = isLeftButtonPressed;
    wasRightButtonPressed = isRightButtonPressed;
    wasUpButtonPressed = isUpButtonPressed;
    wasDownButtonPressed = isDownButtonPressed;
    wasAcceptButtonPressed = isAcceptButtonPressed;
    delay(10);
  }
}
//=========================================================page_SINGLESHOT_SETTING===================================================================//
void page_SINGLESHOT_SETTING() {
  boolean updateDisplay = true;
  uint32_t loopStartMs;
  uint8_t sub_pos = 2;
  boolean isUpButtonPressed = false;
  boolean wasUpButtonPressed = false;
  boolean isDownButtonPressed = false;
  boolean wasDownButtonPressed = false;
  boolean isAcceptButtonPressed = false;
  boolean wasAcceptButtonPressed = false;
  boolean isLeftButtonPressed = false; 
  boolean wasLeftButtonPressed = false; 
  boolean isRightButtonPressed = false; 
  boolean wasRightButtonPressed = false; 
  unsigned long delayTime = 1000;

  while (currPage == SINGLESHOT_SETTING) {
    loopStartMs = millis();
    if (updateDisplay) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("     SINGLE SHOT    ");
      display.setCursor(0, 20);
      if (sub_pos == 1) { display.println("> BACK"); } else { display.println("  BACK"); }
      display.setCursor(0, 30);
      if (sub_pos == 2) { 
        display.print("> TIMER:");
        display.print(delayTime);
        display.print(" ms"); 
        } else { 
          display.print("  TIMER:"); display.print(delayTime);display.print(" ms");
          }
      display.setCursor(0, 50);
      if (sub_pos == 3) { display.println("> SAVE SETTING"); } else { display.println("  SAVE SETTING"); }
      
      display.display();
      updateDisplay = false;
    }
    UP->update();
    isUpButtonPressed = UP->clicked();
    DOWN->update();
    isDownButtonPressed = DOWN->clicked();
    ACCEPT->update();
    isAcceptButtonPressed = ACCEPT->clicked();
    LEFT->update();
    isLeftButtonPressed = LEFT->clicked();
    RIGHT->update();
    isRightButtonPressed = RIGHT->clicked();

//---------------- Handle UP button to increase delay-------------------//
    if (isUpButtonPressed && !wasUpButtonPressed) {
                sub_pos--;
          if(sub_pos < 1) {
            sub_pos = 3;
          }
          updateDisplay = true;
    }

//--------------------- DOWN button to decrease delay (minimum 100ms)----------------------//
    if (isDownButtonPressed && !wasDownButtonPressed) {
                sub_pos++;
          if(sub_pos > 3){
            sub_pos = 1;
          }
          updateDisplay = true;
    }
//--------------------------------Accept Button handling-------------------------------------//
    if (isAcceptButtonPressed && !wasAcceptButtonPressed) {
      switch (sub_pos) {
        case 1:
          currPage = MAIN_MENU;
          break;
        case 2:
          delay(delayTime);
          digitalWrite(LDE, HIGH);
          delay(100); 
          digitalWrite(LDE, LOW);
          display.print("DONE..!!");
          break;
        case 3:
          currPage = TIMELAPSEM_SETTING;
          break;
      }

   }
 //----------------------------------------Left Button Handling-------------------------------//
    if (isLeftButtonPressed && !wasLeftButtonPressed) {
       if (delayTime >= 2000 && sub_pos == 2) { 
        delayTime -= 1000;    
        updateDisplay = true;
      }
    }
//-------------------------------------Right button handling------------------------------------//
    if (isRightButtonPressed && !wasRightButtonPressed) {
     if(sub_pos == 2){
      delayTime += 1000; 
      updateDisplay = true;
     }    
    }
//-------------------------------------------------------------------------------------------------// 
    
    wasLeftButtonPressed = isLeftButtonPressed;
    wasRightButtonPressed = isRightButtonPressed;
    wasUpButtonPressed = isUpButtonPressed;
    wasDownButtonPressed = isDownButtonPressed;
    wasAcceptButtonPressed = isAcceptButtonPressed;
    delay(10);
  }
}

//=============================================================================================================================//
void page_SINGLEBULB_SETTING() {

}
//==============================================================================================================================//
void page_TIMELAPSEM_SETTING() {
  boolean updateDisplay = true;
  uint32_t loopStartMs;
  uint8_t sub_pos = 2;
  boolean isUpButtonPressed = false;
  boolean wasUpButtonPressed = false;
  boolean isDownButtonPressed = false;
  boolean wasDownButtonPressed = false;
  boolean isAcceptButtonPressed = false;
  boolean wasAcceptButtonPressed = false;
  boolean isLeftButtonPressed = false; 
  boolean wasLeftButtonPressed = false; 
  boolean isRightButtonPressed = false; 
  boolean wasRightButtonPressed = false; 
  unsigned long delayTime = 1000;
  unsigned long shot = 5;
  

  while (currPage == TIMELAPSEM_SETTING) {
    loopStartMs = millis();
    if (updateDisplay) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("     TIMELAPSE(M)    ");
      display.setCursor(0, 15);
      if (sub_pos == 1) { display.println("> BACK"); } else { display.println("  BACK"); }
      display.setCursor(0, 25);
      if (sub_pos == 2) { 
        display.print("> INTERVAL:");
        display.print(delayTime);
        display.print(" ms"); 
        } else { 
          display.print("  INTERVAL:"); display.print(delayTime);display.print(" ms");
          }
        display.setCursor(0, 35);
      if (sub_pos == 3) { 
        display.print("> SHOT:");
        display.print(shot);
         } else { 
          display.print("  SHOT:"); display.print(shot);
          }
      display.setCursor(0, 50);
      if (sub_pos == 4) { display.println("> SAVE SETTING"); } else { display.println("  SAVE SETTING"); }
      
      display.display();
      updateDisplay = false;
    }
    UP->update();
    isUpButtonPressed = UP->clicked();
    DOWN->update();
    isDownButtonPressed = DOWN->clicked();
    ACCEPT->update();
    isAcceptButtonPressed = ACCEPT->clicked();
    LEFT->update();
    isLeftButtonPressed = LEFT->clicked();
    RIGHT->update();
    isRightButtonPressed = RIGHT->clicked();

//---------------- Handle UP button to increase delay-------------------//
    if (isUpButtonPressed && !wasUpButtonPressed) {
                sub_pos--;
          if(sub_pos < 1) {
            sub_pos = 4;
          }
          updateDisplay = true;
    }

//--------------------- DOWN button to decrease delay (minimum 100ms)----------------------//
    if (isDownButtonPressed && !wasDownButtonPressed) {
                sub_pos++;
          if(sub_pos > 4){
            sub_pos = 1;
          }
          updateDisplay = true;
    }
//--------------------------------Accept Button handling-------------------------------------//
    if (isAcceptButtonPressed && !wasAcceptButtonPressed) {
      switch (sub_pos) {
        case 1:
          currPage = MAIN_MENU;
          break;
        case 2:
        for (int i = 0; i < shot; i++) {
          delay(delayTime);
          digitalWrite(LDE, HIGH);
          delay(100); 
          digitalWrite(LDE, LOW);
          display.display();
             }
          break;
        case 3:
        for (int i = 0; i < shot; i++) {
          delay(delayTime);
          digitalWrite(LDE, HIGH);
          delay(100); 
          digitalWrite(LDE, LOW);
          display.display();
             }
          break;
       case 4:
          currPage = TIMELAPSEM_SETTING;
          break;
      }

   }
 //----------------------------------------Left Button Handling-------------------------------//
    if (isLeftButtonPressed && !wasLeftButtonPressed) {
              switch (sub_pos) {
        case 2:
         if (delayTime >= 200) { 
          delayTime -= 100;    
          updateDisplay = true;
      }
          break;
        case 3:
         if (shot >=  2) { 
          shot -= 1;    
          updateDisplay = true;
      }
          break;
      }
    }
//-------------------------------------Right button handling------------------------------------//
    if (isRightButtonPressed && !wasRightButtonPressed) {
              switch (sub_pos) {
        case 2:
        delayTime += 100;
        updateDisplay = true;
          break;
        case 3:
        shot ++;
        updateDisplay = true;
          break;
      }
    }
//-------------------------------------------------------------------------------------------------// 
    
    wasLeftButtonPressed = isLeftButtonPressed;
    wasRightButtonPressed = isRightButtonPressed;
    wasUpButtonPressed = isUpButtonPressed;
    wasDownButtonPressed = isDownButtonPressed;
    wasAcceptButtonPressed = isAcceptButtonPressed;
    delay(10);
  }
}

//==============================================================================================================================//
void page_TIMELAPSEBULB_SETTING() {

}
//==============================================================================================================================//
void page_CUSTOMTL_SETTING() {

}
//==============================================================================================================================//
void page_SUB_MENU1() {
}
//==============================================================================================================================//
void page_SUB_MENU2() {
}
//==============================================================================================================================//
void page_SUB_MENU3() {
}
//==============================================================================================================================//
void page_SUB_MENU4() {
}
//==============================================================================================================================//
