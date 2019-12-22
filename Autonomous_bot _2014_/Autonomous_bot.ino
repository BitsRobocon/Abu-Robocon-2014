

/*TEAM ROBOCON 
BITS PILANI*/

//Autonomous Bot

#include<Servo.h>
#include<LiquidCrystal.h>

Servo bright,bleft,middle,sright,sleft;    
int input=0;
int posbright,posbleft,posmiddle,possright,possleft;
int iposbright,iposbleft,iposmiddle,ipossright,ipossleft;
int ser=0;

int a,b,c;

LiquidCrystal lcd (31,32,33,34,35,36);

int flag=0;

void setup()
{
  Serial.begin(57600);
    
  bright.attach(7);
  bleft.attach(6);
  middle.attach(5);
  sright.attach(3);
  sleft.attach(4);
  
  lcd.begin(16,2);
  
 lcd.print("BITS PILANI");
 
}

void loop()
{


  Serial.print("Autonomous bot");
  
 ser=Serial.available();
  while(!ser)
  {
    ser=Serial.available();
  }
 
  input=Serial.parseInt();
  
  input=23;
  
      if(input==23)       //See-Saw
      {
        lcd.print("See Saw");
       seesaw();
      }
      else if(input==12)
      {
        swingready();
      }
     
      else if(input==13)
      {
        swing();
      }
      else if(input==5)
      {
        polewalk();
      }
      else 
      {
        vella();
      }
 
}
  
void servopos()
{ 
  for (posbright=iposbright,posmiddle=iposmiddle,possright=ipossright ; posbright!=a||posmiddle!=b||possright!=c; )
  {
    if(posbright>a) posbright--;
    if(posbright<a) posbright++;
    if(posbright==a) posbright=posbright;
    
    if(posmiddle>b) posmiddle--;
    if(posmiddle<b) posmiddle++;
    if(posmiddle==b) posmiddle=posmiddle;
    
    if(possright>c) possright--;
    if(possright<c) possright++;
    if(possright==c) possright=possright;
    
    bright.write(posbright);
    bleft.write(180-posbright);
    
    middle.write(posmiddle);
    
    sright.write(possright);
    sleft.write(180-possright);
    
    delay(50);
  }
}
  
void seesaw()
{
  lcd.clear();
  lcd.print("Ready to place");
  lcd.setCursor(4,1);
  lcd.print("See-Saw");
  
  readservos();
  //Big Arm
  
  a=110;
  b=140;
  c=110;
  
  servopos();
  
}
 
void swingready()
{
  lcd.clear();
  lcd.print("Ready to place");
  lcd.setCursor(4,1);
  lcd.print("Swing");
  
  readservos();
  //Big Arm
  
  a=130;
  b=120;
  c=130;
  
  servopos();
  
}

void swing()
{
  lcd.clear();
  lcd.print("Ready for");
  lcd.setCursor(4,1);
  lcd.print("Swing");
  
  readservos();
  //Big Arm
  
  a=145;
  b=140;
  c=145;
  
  servopos();
  
}

void polewalk()
{
  lcd.clear();
  lcd.print("Pole Walk");
}



void readservos()
{
  iposbright=bright.read();
  iposbleft=bleft.read();
  iposmiddle=middle.read();
  ipossright=sright.read();
  ipossleft=sleft.read();
}
void vella()
{
  readservos();
    lcd.setCursor(4,1);
    lcd.print("Vella");
  
  bright.write(iposbright);
  bleft.write(iposbleft);
  middle.write(iposmiddle);
  sright.write(ipossright);
  sleft.write(ipossleft);
  
}

