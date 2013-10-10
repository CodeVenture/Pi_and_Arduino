#include <SoftwareSerial.h>

#define txPin 8
#define rxPin 9

SoftwareSerial LCD = SoftwareSerial(rxPin, txPin);

const int LCDdelay=10;  //subject to change

void lcdInit()
{
  pinMode(txPin, OUTPUT);  //set txPin on the Arduino to output mode
  pinMode(rxPin, INPUT);   //set rxPin on the Arduino to input mode
  LCD.begin(9600);         //initialize SoftwareSerial with 9600 baud
  delay(2);
  LCD.write(0x9F);         //send control header 
  LCD.write(0x82);         //send power_off command
  delay(1);
  LCD.write(0x9F);         //send control_header
  LCD.write(0x83);         //send power_on command
  delay(1);
  LCD.write(0xA5);         //send initialize_acknowledge command
  /*while(1)
  {
      if (LCD.available() > 0 && LCD.read()==0xAA)    //wait until display is ready by looking for initialize_done response on the serial port 
          break;
  }*/
  delay(500);
  clearLCD();                           //run function to initially clear the LCD screen
  backlightOn();
  writeLCD(0,2, "INITIALIZED");         //write to LCD to show everything worked as expected
  writeLCD(1,6, ":-)");
  delay(2000);
  backlightOff();
  clearLCD();                           //clear the screen for the main use
}

void lcdPosition(int row, int col)
{
  LCD.write(0x9F);   //send control header
  LCD.write(0xFF);   //send cursor header
  LCD.write(col);    //send column
  LCD.write(row);    //send row
  delay(LCDdelay);
}

void clearLCD()
{
  LCD.write(0x9F);   //send control header
  LCD.write(0x65);   //send clear-display command
  delay(LCDdelay);
}

void backlightOn() 
{
  LCD.write(0x9F);   //send control header
  LCD.write(0x81);   //send backlight_on command
  delay(LCDdelay);
}
void backlightOff()
{
  LCD.write(0x9F);   //send control header
  LCD.write(0x80);   //send backlight_off command
  delay(LCDdelay);
}

void writeLCD(int row, int col, String content)      //writeLCD() function for string value
{
  lcdPosition(row,col);      //run function to set cursor to the desired position
  LCD.write(0xFE);           //send character_header command
  LCD.print(content);        //print content to LCD
}

void writeLCD(int row, int col, int content)         //writeLCD() function for integer values
{
  lcdPosition(row,col);
  LCD.write(0xFE);
  LCD.print(content);
}

void writeLCD(int row, int col, char content)        //writeLCD() function for character values
{
  lcdPosition(row,col);
  LCD.write(0xFE);
  LCD.print(content);
}

void setup()
{
  lcdInit();               //run function to initialize the LCD
  backlightOn();           //run function to turn backlight on
}

void loop()
{
  /*clearLCD();            //example showing passed seconds since initialization on th LCD
  lcdPosition(1,0);
  LCD.write(0xFE);
  LCD.print(millis()/1000,DEC);
  delay(989);*/
  
  clearLCD();              //example showing timed text output on various locations on the screen
  backlightOff();
  delay(2000);
  backlightOn();
  delay(250);
  writeLCD(0,0,"Who let the dogs");
  writeLCD(1,6,"out?");
  delay(1800);
  clearLCD();
  writeLCD(1,0,"Who?");
  delay(800);
  clearLCD();
  writeLCD(1,12,"Who?");
  delay(400);
  clearLCD();
  writeLCD(1,6,"Who?");
  delay(1500);
}
