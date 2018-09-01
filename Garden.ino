#include "Arduino.h"

#include <UTFT.h>
#include <URTouch.h>
#include <avr/pgmspace.h>
#include <Wire.h>
//#include <DS1307new.h>
//#include "Const.h"
#include <UTFT_Buttons_fab.h>

#define LARGE true
#define SMALL false
#define PORTRAIT	0
#define LANDSCAPE	1

UTFT myGLCD(ITDB32S,38,39,40,41);
URTouch  myTouch(6,5,4,3,2);
// set up UTFT_Buttons
UTFT_Buttons  myButtons(&myGLCD, &myTouch);

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];

//VARIABLES
int x, y;
unsigned long prevMillis05 = 0;
unsigned long prevMillis1 = 0;
unsigned long prevMillis5 = 0;
unsigned long prevMillis60 = 0;
unsigned long prevMillis600 = 0;



struct RTC_T
{
  int tHour;
  int tMinute;
  int tDow;
  int tDay;
  int tMonth;
  int tYear;
} tmpRTC, prevRTC;


//GLOBAL VARIAVBLES
byte screenId=0;
int pressedButton=-1;

//GARDEN VARIABLES
boolean Prg1;


void printHeader(char* headline)
{

    uint8_t *current_font = myGLCD.getFont();
    word current_color = myGLCD.getColor();
    word current_back  = myGLCD.getBackColor();

    changeFont(SMALL, 255, 0, 0, 255, 0, 0);
     myGLCD.fillRect (1, 1, 318, 15);
     myGLCD.setColor(255, 255, 255);
     myGLCD.print(headline, CENTER, 2);

    myGLCD.setFont(current_font);
    myGLCD.setColor(current_color);
    myGLCD.setBackColor(current_back);

}



void clearScreen()
{
 myGLCD.setColor(0, 0, 0);
 myGLCD.fillRect(1, 1, 318, 225);
}


void printTime(int thour, int tminute, int posx, int posy)
{
  char tmpTime[6], charT[3];

  tmpTime[0] = '\0';

  if (thour>=0 && thour<=9) {          //add space
    strcat(tmpTime, " ");
    itoa(thour, charT, 10);
    strcat(tmpTime, charT);
  }
  else
    itoa(thour, tmpTime, 10);

  strcat(tmpTime, ":");

  if (tminute>=0 && tminute<=9) {         //add 0
    strcat(tmpTime, "0");
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }
  else {
    itoa(tminute, charT, 10);
    strcat(tmpTime, charT);
  }

  myGLCD.print(tmpTime, posx, posy);           // Display time
}






void changeFont(boolean font, byte cr, byte cg, byte cb, byte br, byte bg, byte bb)
{
  myGLCD.setBackColor(br, bg, bb);    //font background
  myGLCD.setColor(cr, cg, cb);        //font colour
  if (font==LARGE)
    myGLCD.setFont(BigFont);          //font size
  else if (font==SMALL)
    myGLCD.setFont(SmallFont);
}

void changeFont(boolean font, uint32_t fontColor, uint32_t bckgrdColor)
{
  myGLCD.setBackColor(bckgrdColor);    //font background
  myGLCD.setColor(fontColor);        //font colour
  if (font==LARGE)
    myGLCD.setFont(BigFont);          //font size
  else if (font==SMALL)
    myGLCD.setFont(SmallFont);
}


////////////////////////////////////////////////////////////////////////////////////////////
//                                               SCREENS
////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------main screen ----------screenId = 0
void mainScreen(boolean refreshAll=false)
{
  Serial.println("mainScreen start");


  if ( refreshAll)                                    //draw static elements
    {
     myGLCD.clrScr();
     printHeader("MAIN SCREEN" );
     myGLCD.setColor(0, 0, 125);
     changeFont(SMALL, 255, 255, 255, 0, 0, 0);
     myGLCD.print("MAIN SCREEN",20,130);
     myButtons.setTextFont(SmallFont);
     myButtons.setSymbolFont(Dingbats1_XL);
     but_1G = myButtons.addButton( b1G[0],  b1G[1], b1G[2],  b1G[3], "GARDEN");
     myButtons.drawButtons();
     delay(100);

     }

//REFRESGH TIME
/*  if ((RTC.hour!=prevRTC.tHour) || (RTC.minute!=prevRTC.tMinute) || refreshAll) {    //time
    prevRTC.tHour = RTC.hour;
    prevRTC.tMinute = RTC.minute;
    changeFont(SMALL, 225, 225, 0, 0, 0, 0);
    printTime(RTC.hour, RTC.minute, 250, 5);

  }
  */

 }


//---------------------------------------HomeGarden screen ----------screenId = 1
void homeGarden (boolean refreshAll=false)
{
  Serial.println("homeGarden start");

  if ( refreshAll)
    {

     myGLCD.clrScr();
     printHeader("HOME GARDEN" );
     myButtons.setTextFont(SmallFont);
     myButtons.setSymbolFont(Dingbats1_XL);
     myGLCD.setColor(0, 0, 125);
     changeFont(SMALL, 255, 255, 255, 0, 0, 0);
     myGLCD.print("HOMEGARDEN ",20,130);
     but_1HG = myButtons.addButton( b1HG[0],  b1HG[1], b1HG[2],  b1HG[3], "PROGRAMS");
     but_2HG = myButtons.addButton( b2HG[0],  b2HG[1], b2HG[2],  b2HG[3], "SET-UP");
     but_3HG = myButtons.addButton( b3HG[0],  b3HG[1], b3HG[2],  b3HG[3], "CANCEL");
     myButtons.drawButtons();
     delay(100);
     }

 }





//-----------------------------------gardenSetup screen-------screenId=4 ---------------
//Setup of Stations ON/OFF, PERCENT OF HUMIDITY
//Inserire il TimeOut per l'uscita forzata dalla pagina !!!

void gardenSetUp(boolean refreshAll=false)
{
    Serial.println("gardenSetUp >>");
    int pressedSetUpBut=-1;
    if (refreshAll)
    {

      //set auxliary variables
      boolean S0aux=StationOnOff[0];
      boolean S1aux=StationOnOff[1];
      boolean S2aux=StationOnOff[2];
      boolean S3aux=StationOnOff[3];
      boolean S4aux=StationOnOff[4];
      boolean S5aux=StationOnOff[5];
      int humAux=0;

      unsigned int HT0aux=humThr[0];
      unsigned int HT1aux=humThr[1];
      unsigned int HT2aux=humThr[2];
      unsigned int HT3aux=humThr[3];
      unsigned int HT4aux=humThr[4];
      unsigned int HT5aux=humThr[5];


      myGLCD.clrScr();
      printHeader("SET UP GARDEN" );
      myGLCD.setColor(0, 0, 125);

      changeFont(SMALL, VGA_SILVER, VGA_TRANSPARENT);

      myGLCD.print("Stazioni",posRifX1,posRifY1);
      myGLCD.drawLine(posRifX1,posRifY1+12,posRifX1+75,posRifY1+12);

      myGLCD.print("Umidita'",posRifX2,posRifY2);
      myGLCD.drawLine(posRifX2,posRifY2+12,posRifX2+90,posRifY2+12);

      myGLCD.print("s1",b0S[0]-20,b0S[1]+2);
      myGLCD.print("s2",b0S[0]-20,b0S[1]+32);
      myGLCD.print("s3",b0S[0]-20,b0S[1]+62);
      myGLCD.print("s4",b0S[0]-20,b0S[1]+92);
      myGLCD.print("s5",b0S[0]-20,b0S[1]+122);
      myGLCD.print("s6",b0S[0]-20,b0S[1]+152);

      //First print of Humidity Values
      myGLCD.setFont(BigFont);
      myGLCD.printNumI(HT0aux, b6S[0]-40, b6S[1]+2 ,2,'0');
      myGLCD.printNumI(HT1aux, b6S[0]-40, b6S[1]+32 ,2,'0');
      myGLCD.printNumI(HT2aux, b6S[0]-40, b6S[1]+62 ,2,'0');
      myGLCD.printNumI(HT3aux, b6S[0]-40, b6S[1]+92 ,2,'0');
      myGLCD.printNumI(HT4aux, b6S[0]-40, b6S[1]+122 ,2,'0');
      myGLCD.printNumI(HT5aux, b6S[0]-40, b6S[1]+152 ,2,'0');


       myButtons.setTextFont(SmallFont);
       myButtons.setSymbolFont(Dingbats1_XL);

       //S1
       if(S0aux) but_0S=myButtons.addButtonON( b0S[0], b0S[1], b0S[2], b0S[3], "ON");
       else but_0S=myButtons.addButtonOFF( b0S[0], b0S[1], b0S[2], b0S[3], "OFF");
       //S2
       if(S1aux) but_1S=myButtons.addButtonON( b0S[0], b0S[1]+30, b0S[2], b0S[3], "ON");
       else but_1S=myButtons.addButtonOFF( b0S[0], b0S[1]+30, b0S[2], b0S[3], "OFF");
       //S3
       if(S2aux) but_2S=myButtons.addButtonON( b0S[0], b0S[1]+60, b0S[2], b0S[3], "ON");
       else but_2S=myButtons.addButtonOFF( b0S[0], b0S[1]+60, b0S[2], b0S[3], "OFF");
       //S4
       if(S3aux) but_3S=myButtons.addButtonON( b0S[0], b0S[1]+90, b0S[2], b0S[3], "ON");
       else but_3S=myButtons.addButtonOFF( b0S[0], b0S[1]+90, b0S[2], b0S[3], "OFF");
      //S5
       if(S4aux) but_4S=myButtons.addButtonON( b0S[0], b0S[1]+120, b0S[2], b0S[3], "ON");
       else but_4S=myButtons.addButtonOFF( b0S[0], b0S[1]+120, b0S[2], b0S[3], "OFF");
       //S6
       if(S5aux)but_5S=myButtons.addButtonON( b0S[0], b0S[1]+150, b0S[2], b0S[3], "ON");
       else but_5S=myButtons.addButtonOFF( b0S[0], b0S[1]+150, b0S[2], b0S[3], "OFF");

       //Up Humidity
       but_6S=myButtons.addButton( b6S[0], b6S[1], b6S[2], b6S[3], "+");
       but_7S=myButtons.addButton( b7S[0], b7S[1], b7S[2], b7S[3], "-");
       but_8S=myButtons.addButton( b6S[0], b6S[1]+30, b6S[2], b6S[3], "+");
       but_9S=myButtons.addButton( b7S[0], b7S[1]+30, b7S[2], b7S[3], "-");
       but_10S=myButtons.addButton( b6S[0], b6S[1]+60, b6S[2], b6S[3], "+");
       but_11S=myButtons.addButton( b7S[0], b7S[1]+60, b7S[2], b7S[3], "-");
       but_12S=myButtons.addButton( b6S[0], b6S[1]+90, b6S[2], b6S[3], "+");
       but_13S=myButtons.addButton( b7S[0], b7S[1]+90, b7S[2], b7S[3], "-");
       but_14S=myButtons.addButton( b6S[0], b6S[1]+120, b6S[2], b6S[3], "+");
       but_15S=myButtons.addButton( b7S[0], b7S[1]+120, b7S[2], b7S[3], "-");
       but_16S=myButtons.addButton( b6S[0], b6S[1]+150, b6S[2], b6S[3], "+");
       but_17S=myButtons.addButton( b7S[0], b7S[1]+150, b7S[2], b7S[3], "-");


       //SAVE AND CANCEL
       but_18S = myButtons.addButton( b18S[0], b18S[1], b18S[2], b18S[3], "SAVE");
       but_19S = myButtons.addButton( b19S[0], b19S[1], b19S[2], b19S[3], "CANCEL");

       myButtons.drawButtons();
       delay(100);

       while(1)
          {
            pressedSetUpBut = myButtons.checkButtons();

            if (pressedSetUpBut==but_18S)  //Press SAVE
            {
              //Save Stations set
              StationOnOff[0] = S0aux;
              StationOnOff[1] = S1aux;
              StationOnOff[2] = S2aux;
              StationOnOff[3] = S3aux;
              StationOnOff[4] = S4aux;
              StationOnOff[5] = S5aux;
              //Save Humidity Trhesholds
              humThr[0]=HT0aux;
              humThr[1]=HT1aux;
              humThr[2]=HT2aux;
              humThr[3]=HT3aux;
              humThr[4]=HT4aux;
              humThr[5]=HT5aux;
              myButtons.deleteAllButtons();
              screenId=1; // To return to HomeGarden
              break;
            } else if (pressedSetUpBut==but_19S)  //Press CANCEL
            {
              screenId=1; // To return to HomeGarden
              myButtons.deleteAllButtons();
              break;
            }
            if (pressedSetUpBut==but_0S)  //Press S1 OFF/ON
            {
              S0aux=!S0aux;
              delay(100);
              if(S0aux) myButtons.relabelButtonONOFF (but_0S, "ON", true,true);
              else myButtons.relabelButtonONOFF( but_0S, "OFF", true,false);
            }
            if (pressedSetUpBut==but_1S)  //Press S2 OFF/ON
            {
              S1aux=!S1aux;
              delay(100);
              if(S1aux) myButtons.relabelButtonONOFF( but_1S, "ON", true,true);
              else myButtons.relabelButtonONOFF( but_1S, "OFF", true,false);
            }
            if (pressedSetUpBut==but_2S)  //Press S3 OFF/ON
            {
              S2aux=!S2aux;
              delay(100);
              if(S2aux) myButtons.relabelButtonONOFF( but_2S, "ON", true,true);
              else myButtons.relabelButtonONOFF( but_2S, "OFF", true,false);
            }
            if (pressedSetUpBut==but_3S)  //Press S4 OFF/ON
            {
              S3aux=!S3aux;
              delay(100);
              if(S3aux) myButtons.relabelButtonONOFF( but_3S, "ON", true,true);
              else myButtons.relabelButtonONOFF( but_3S, "OFF", true,false);
            }
            if (pressedSetUpBut==but_4S)  //Press S5 OFF/ON
            {
              S4aux=!S4aux;
              delay(100);
              if(S4aux) myButtons.relabelButtonONOFF( but_4S, "ON", true, true);
              else myButtons.relabelButtonONOFF( but_4S, "OFF", true, false);
            }
            if (pressedSetUpBut==but_5S)  //Press S6 OFF/ON
            {
              S5aux=!S5aux;
              delay(100);
              if(S5aux) myButtons.relabelButtonONOFF( but_5S, "ON", true,true);
              else myButtons.relabelButtonONOFF( but_5S, "OFF", true,false);
            }
             if (pressedSetUpBut==but_6S)  //Press HUMIDITY THRESHOLD 0 UP
            {
             HT0aux = ++HT0aux % 100;
               myGLCD.printNumI(HT0aux, b6S[0]-40,b6S[1]+2,2,'0');
            }
              if (pressedSetUpBut==but_7S)  //Press HUMIDITY THRESHOLD 0 DOWN
            {
              if (--HT0aux==65535)HT0aux=99;
              myGLCD.printNumI(HT0aux, b6S[0]-40, b6S[1]+2 ,2,'0');;
            }
            if (pressedSetUpBut==but_8S)  //Press HUMIDITY THRESHOLD 1 UP
            {
             HT1aux = ++HT1aux % 100;
               myGLCD.printNumI(HT1aux, b6S[0]-40,b6S[1]+32,2,'0');
            }
              if (pressedSetUpBut==but_9S)  //Press HUMIDITY THRESHOLD 1 DOWN
            {
              if (--HT1aux==65535)HT1aux=99;
              myGLCD.printNumI(HT1aux, b6S[0]-40, b6S[1]+32,2,'0');;
            }
            if (pressedSetUpBut==but_10S)  //Press HUMIDITY THRESHOLD 2 UP
            {
             HT2aux = ++HT2aux % 100;
               myGLCD.printNumI(HT2aux, b6S[0]-40,b6S[1]+62,2,'0');
            }
            if (pressedSetUpBut==but_11S)  //Press HUMIDITY THRESHOLD 2 DOWN
            {
              if (--HT2aux==65535)HT2aux=99;
              myGLCD.printNumI(HT2aux, b6S[0]-40, b6S[1]+62,2,'0');;
            }
            if (pressedSetUpBut==but_12S)  //Press HUMIDITY THRESHOLD 3 UP
            {
             HT3aux = ++HT3aux % 100;
               myGLCD.printNumI(HT3aux, b6S[0]-40,b6S[1]+92,2,'0');
            }
            if (pressedSetUpBut==but_13S)  //Press HUMIDITY THRESHOLD 3 DOWN
            {
              if (--HT3aux==65535)HT3aux=99;
              myGLCD.printNumI(HT3aux, b6S[0]-40, b6S[1]+92,2,'0');;
            }
             if (pressedSetUpBut==but_14S)  //Press HUMIDITY THRESHOLD 4 UP
            {
             HT4aux = ++HT4aux % 100;
               myGLCD.printNumI(HT4aux, b6S[0]-40,b6S[1]+122,2,'0');
            }
            if (pressedSetUpBut==but_15S)  //Press HUMIDITY THRESHOLD 4 DOWN
            {
              if (--HT4aux==65535)HT4aux=99;
              myGLCD.printNumI(HT4aux, b6S[0]-40, b6S[1]+122,2,'0');;
            }
            if (pressedSetUpBut==but_16S)  //Press HUMIDITY THRESHOLD 5 UP
            {
             HT5aux = ++HT5aux % 100;
               myGLCD.printNumI(HT5aux, b6S[0]-40,b6S[1]+152,2,'0');
            }
            if (pressedSetUpBut==but_17S)  //Press HUMIDITY THRESHOLD 5 DOWN
            {
              if (--HT5aux==65535)HT5aux=99;
              myGLCD.printNumI(HT5aux, b6S[0]-40, b6S[1]+152,2,'0');;
            }


         } //end sub-while
      Serial.println("ESC MAIN WHILE");
    } //end if(RefreAll)
    Serial.println("END GARDEN SET");
    homeGarden(true);
}//end GardenSet()








//-----------------------------------set Garden Program-------screenId=1 ---------------

void gardenSet(boolean refreshAll=false)
{
    int but1;
    int but2;
    int but3;
    int pressed_button;

    if (Prg1) Serial.println("gardenSet START >> Prg1=true");
    else Serial.println("gardenSet START >> Prg1=false");
    if (refreshAll)
    {
      boolean mainWhile=true;

      while(mainWhile)
      {
          Serial.println("gardenSet mainWhile");
          if (Prg1) {
            Serial.println("gardenSet mainWhile check: Prg1=true");
            }
          else {
            Serial.println("gardenSet mainWhile check: Prg1=false");
          }
          myGLCD.clrScr();
          printHeader("PROGRAMMA 1" );
          myGLCD.setColor(0, 0, 125);

          changeFont(SMALL, 255, 255, 0, 0, 0, 0);
          myGLCD.print("Time:", 20, 51);
          myGLCD.print("Date:", 20, 140);

          myButtons.setTextFont(SmallFont);
          myButtons.setSymbolFont(Dingbats1_XL);
          if(Prg1) {but1 = myButtons.addButton( 250,  20, 40,  20, "ON");}
          else {but1 = myButtons.addButton( 250,  20, 40,  20, "OFF"); }
          but2 = myButtons.addButton( prgSAVE[0], prgSAVE[1], prgSAVE[2], prgSAVE[3], "SAVE");
          but3 = myButtons.addButton( prgCANC[0], prgCANC[1], prgCANC[2], prgCANC[3], "CANCEL");
          myButtons.drawButtons();
          delay(100);

          while(1)
          {
            pressed_button = myButtons.checkButtons();
            if (pressed_button==but1)  //Press OFF/ON
            {
              Serial.println("Pressed ON/OFF");
              Prg1=!Prg1;
               myButtons.deleteAllButtons();
              break;
            } else if (pressed_button==but3)  //Press CANCEL
            {
              Serial.println("Pressed CANCEL");
              screenId=0;
              mainWhile=false;
              myButtons.deleteAllButtons();
              break;
            }
            else if (pressed_button==but2) //PRESS SAVE
            {
              Serial.println("Pressed SAVE");
              screenId=0;
              mainWhile=false;
              myButtons.deleteAllButtons();
              break;
            }

          } //end sub-while
      }//end main-while
      Serial.println("ESC MAIN WHILE");
    } //end if(RefreAll)
    Serial.println("END GARDEN SET");

}//end GardenSet()





void processMyTouch()
{
    Serial.println("processMyTouch>>>>>>>>>");
    Serial.print("screenId=");
    Serial.println(screenId);
    Serial.print("pressedButton=");
    Serial.println(pressedButton);

    if ((screenId==1) && (pressedButton!=but_3HG) && (pressedButton!=but_2HG)) //Pressed SAVE or CANCEL from gardenSetup()
    {
      delay(50);
      screenId=1;
      myButtons.deleteAllButtons();
      homeGarden(true);
    }
    if (((screenId==0) && (pressedButton==but_1G)) )  // MAINSCREEN->CANCEL
    {
      delay(50);
      screenId=1;
      myButtons.deleteAllButtons();
      homeGarden(true);
    }
    if ((screenId==1) && (pressedButton==but_3HG)) // HomeGarden-->CANCEL
    {
      delay(50);
      screenId=0;
      myButtons.deleteAllButtons();
      mainScreen(true);
    }
     if ((screenId==1) && (pressedButton==but_2HG)) // HomeGarden-->SETUP
    { delay(50);
      screenId=4;
      myButtons.deleteAllButtons();
      gardenSetUp(true);
    }

}





void setup() {
  Serial.begin(9600);

  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_MEDIUM);


  //VARIABLES SET

  //Valori da leggere sulla SD
  StationOnOff[0]=true;
  StationOnOff[1]=true;
  StationOnOff[2]=false;
  StationOnOff[3]=false;
  StationOnOff[4]=false;
  StationOnOff[5]=false;
  StationOnOff[6]=false;


 //TEST VALUES
  humidity =18;

  //changeFont(SMALL, 255, 255, 0, 64, 64, 64);
//  myGLCD.setFont(SmallFont);
//  myGLCD.print("  Stilo v.3.0", LEFT, 227);
//  myGLCD.setColor(255, 128, 128);
//  myGLCD.print("Aquarium Controller", RIGHT, 227);
  myButtons.setButtonColors(VGA_WHITE,VGA_GRAY,VGA_WHITE,VGA_RED,VGA_BLUE);
  mainScreen(true);

}





 void loop() {
    unsigned long currentMillis = millis();
    pressedButton=myButtons.checkButtons();
    if (pressedButton!=-1 )  {
     Serial.println("In loop call processMyTouch");
     processMyTouch();
   // prevMillis600 = currentMillis;

    }


 //inserire check Timeout

 }


