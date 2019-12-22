#include <PS2X_lib.h>  //for v1.6
#include <LiquidCrystal.h>
LiquidCrystal lcd(14,15,16,17,18,19);
PS2X ps2x; // create PS2 Controller Class
boolean flagsarm=false;
boolean flaglarm=false;
int error = 0; 
byte type = 0;
byte vibrate = 0;
//motor pins

          int front1=36  ; //front
          int front2=37  ; //front
          int right1=44  ; //right
          int right2=45  ; //right
          int behind1=40  ;//behind
          int behind2=41  ;//behind
          int left1=50  ;//left
          int left2=51  ;//left
          int fright1=47  ;//front right
          int fright2=46  ;//front right
          int fleft1=34  ;//front left
          int fleft2=35  ;//front left
          int bright1=43  ;//behind right
          int bright2=42  ;//behind right
          int bleft1=38  ;//behind left
          int bleft2=39  ;//behind left
          int larm1=;//left arm
          int larm2=;//left arm
          int sarm1=;//swing arm
          int sarm2=;//swing arm
          
          
          
         
          
          
//pwm pins          
          int pwm1=8  ; //front         
          int pwm2=4  ; //front right
          int pwm3=12  ; //right
          int pwm4=11  ; //behind right
          int pwm5=10  ; //behind
          int pwm6=9  ; //behind left
          int pwm7=7  ; //left
          int pwm8=6  ; //front left 
          int pwm9=;//left arm
          int pwn10=;//swing arm
  
  //gripper switcher 
  
          boolean left=LOW;         
          boolean swing=LOW;          
        
         
          
//pnematic pins + solenoid + relays

          int rarm1=  ; // right arm
          int rarm2=  ; // right arm
          int lg1=  ; //right gripper       
          int lg2=  ; //right gripper 
          int sw1=  ; //swing arm gripper
          int sw2=  ; //swing arm gripper
         
          
void setup(){
  
//serial on  
         Serial.begin(57600);
         lcd.begin(16, 2);
//define output
         
         pinMode(front1,OUTPUT);
         pinMode(front2,OUTPUT);
         pinMode(fright1,OUTPUT);
         pinMode(fright2,OUTPUT);
         pinMode(behind1,OUTPUT);
         pinMode(behind2,OUTPUT);
         pinMode(bleft1,OUTPUT);
         pinMode(bleft2,OUTPUT);
         pinMode(bright1,OUTPUT);
         pinMode(bright2,OUTPUT);
         pinMode(fleft1,OUTPUT);
         pinMode(fleft2,OUTPUT);
         pinMode(left1,OUTPUT);
         pinMode(left2,OUTPUT);
         pinMode(right1,OUTPUT);
         pinMode(right2,OUTPUT);
         pinMode(larm1,OUTPUT);
         pinMode(larm2,OUTPUT);
         pinMode(sarm1,OUTPUT);
         pinMode(sarm2,OUTPUT);
         
         pinMode(pwm1,OUTPUT);
         pinMode(pwm2,OUTPUT);
         pinMode(pwm3,OUTPUT);
         pinMode(pwm4,OUTPUT);
         pinMode(pwm5,OUTPUT);
         pinMode(pwm6,OUTPUT);
         pinMode(pwm7,OUTPUT);
         pinMode(pwm8,OUTPUT);
         pinMode(pwm9,OUTPUT);
         pinMode(pwm10,OUTPUT);
         
        
        
       
         pinMode(ar1,OUTPUT);
         pinMode(ar2,OUTPUT);
         pinMode(sw1,OUTPUT);
         pinMode(sw2,OUTPUT);
         pinMode(lg1,OUTPUT);
         pinMode(lg2,OUTPUT);
        
      

         //setting solenoid valve grounds
           digitalWrite(lg1,LOW);
           digitalWrite(lg2,LOW);
           digitalWrite(sw1,LOW);
           digitalWrite(sw2,LOW);
           digitalWrite(ar1,LOW);
           digitalWrite(ar2,LOW);
                   
         error = ps2x.config_gamepad(23,29,27,25, true, true);   //GamePad(clock(blue), command(orange), attention(yellow), data(brown), Pressures?, Rumble?
         //23-blue
         //25-brown
         //29-orange
         //27-yellow
 
         if(error == 0)
{
                 Serial.println("Found Controller, configured successful");
                 Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
                 Serial.println("holding L1 or R1 will print out the analog stick values.");
                 Serial.println("Go to www.billporter.info for updates and to report bugs.");
                 lcd.print("Controller Found");
                 lcd.setCursor(0,1);
                 lcd.print("All the Best");
         }
           
          else if(error == 1)
                 Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
                 lcd.print("Controller Not Found");
                 lcd.setCursor(0,1);
                 lcd.print("Check the Wiring");           
          else if(error == 2)
                 Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
           
          else if(error == 3)
                 Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
 
           
           type = ps2x.readType();
                            

 

}

void loop(){

  
            
           ps2x.read_gamepad(false, vibrate); 
           
           //navigation
           
         
           
           
           if((ps2x.Analog(PSS_LX)!=123)||(ps2x.Analog(PSS_LY)!=123))
           {
                  
                  if(ps2x.Analog(PSS_LY)<100)
                  
                  {
                  
                            int x=map(ps2x.Analog(PSS_LY),100,0,50,255);
                            digitalWrite(fright1,LOW);
                            digitalWrite(fright2,HIGH);
                            
                            digitalWrite(fleft1,LOW);
                            digitalWrite(fleft2,HIGH);
                            
                            digitalWrite(bright1,LOW);
                            digitalWrite(bright2,HIGH);
                            
                            digitalWrite(bleft1,LOW);
                            digitalWrite(bleft2,HIGH);
                            
                            digitalWrite(left1,HIGH);
                            digitalWrite(left2,LOW);
                            
                            digitalWrite(right1,LOW);
                            digitalWrite(right2,HIGH);
                           
                            digitalWrite(behind1,LOW);
                            digitalWrite(behind2,LOW);
                            
                            digitalWrite(front1, LOW);
                            digitalWrite(front2, LOW);
                           
                            analogWrite(pwm2,x);
                            analogWrite(pwm3,x);
                            analogWrite(pwm4,x);
                            analogWrite(pwm6,x);
                            analogWrite(pwm7,x);
                            analogWrite(pwm8,x);
                            
                            Serial.print("forward @ ");
                            Serial.println(x);
                            
                            lcd.clear();
                            lcd.print("Going Forward");
                    
                   }//end backward
                    
                    //forward
                    if(ps2x.Analog(PSS_LY)>150)
        
                    {
                            int x=map(ps2x.Analog(PSS_LY),150,255,50,255);
                            
                            digitalWrite(fright1,HIGH);
                            digitalWrite(fright2,LOW);
                            
                            digitalWrite(fleft1,HIGH);
                            digitalWrite(fleft2,LOW);
                            
                            digitalWrite(bright1,HIGH);
                            digitalWrite(bright2,LOW);
                            
                            digitalWrite(bleft1,HIGH);
                            digitalWrite(bleft2,LOW);
                           
                            digitalWrite(left1,HIGH);
                            digitalWrite(left2,LOW);
                            
                            digitalWrite(right1,HIGH);
                            digitalWrite(right2,LOW);
                            
                            digitalWrite(behind1,LOW); //no need of giving low
                            digitalWrite(behind2,LOW);
                            
                            digitalWrite(front1, LOW);
                            digitalWrite(front2, LOW);
                            
                            analogWrite(pwm2,x);
                            analogWrite(pwm3,x);
                            analogWrite(pwm4,x);
                            analogWrite(pwm6,x);
                            analogWrite(pwm7,x);
                            analogWrite(pwm8,x);
                
                            
                            Serial.print("backward @ ");
                            Serial.println(x);
                            
                            lcd.clear();
                            lcd.print("Going Backward");
                        
                    }//end forward
                    
                    //left(motors on front and back)
                    else if(ps2x.Analog(PSS_LX)<100)
        
                    {
                        
                            int x=map(ps2x.Analog(PSS_LX),100,0,50,255);
                            
                            digitalWrite(fright1,LOW);
                            digitalWrite(fright2,HIGH);
                            
                            digitalWrite(fleft1,HIGH);
                            digitalWrite(fleft2,LOW);
                            
                            digitalWrite(bright1,HIGH);
                            digitalWrite(bright2,LOW);
                            
                            digitalWrite(bleft1,LOW);
                            digitalWrite(bleft2,HIGH);
                            
                            digitalWrite(left1,LOW);
                            digitalWrite(left2,LOW);
                            
                            digitalWrite(right1,LOW);
                            digitalWrite(right2,LOW);
                           
                            digitalWrite(behind1,HIGH);
                            digitalWrite(behind2,LOW);
                            
                            digitalWrite(front1, HIGH);
                            digitalWrite(front2, LOW);
                           
                            analogWrite(pwm1,x);
                            analogWrite(pwm2,x);
                            analogWrite(pwm4,x);
                            analogWrite(pwm5,x);
                            analogWrite(pwm6,x);
                            analogWrite(pwm8,x);
                            
                            Serial.print("left @ ");
                            Serial.println(x);
                            
                            lcd.clear();
                            lcd.print("Going Left");                            
                    }//emd left
                  
                    else if(ps2x.Analog(PSS_LX)>150)
        
                    {
                      
                            int x=map(ps2x.Analog(PSS_LX),150,255,50,255);
                              
                            digitalWrite(fright1,HIGH);
                            digitalWrite(fright2,LOW);
                            
                            digitalWrite(fleft1,LOW);
                            digitalWrite(fleft2,HIGH);
                            
                            digitalWrite(bright1,LOW);
                            digitalWrite(bright2,HIGH);
                            
                            digitalWrite(bleft1,HIGH);
                            digitalWrite(bleft2,LOW);
                           
                            digitalWrite(left1,LOW);
                            digitalWrite(left2,LOW);
                            
                            digitalWrite(right1,LOW);
                            digitalWrite(right2,LOW);
                            
                            digitalWrite(behind1,LOW);
                            digitalWrite(behind2,HIGH);
                            
                            digitalWrite(front1, HIGH);
                            digitalWrite(front2, LOW);
                              
                            analogWrite(pwm1,x);
                            analogWrite(pwm2,x);
                            analogWrite(pwm4,x);
                            analogWrite(pwm5,x);
                            analogWrite(pwm6,x);
                            analogWrite(pwm8,x);          
                              
                              Serial.print("right @ ");
                              Serial.println(x);
                              
                            lcd.clear();
                            lcd.print("Going Right");                              
        
                    }//end of right
       
          }// end of navigation
          
          //turn right
          if(ps2x.Button(PSB_PAD_RIGHT))
          {
                            digitalWrite(fright1,HIGH);
                            digitalWrite(fright2,LOW);
                            
                            digitalWrite(fleft1,HIGH);
                            digitalWrite(fleft2,LOW);
                            
                            digitalWrite(bright1,HIGH);
                            digitalWrite(bright2,LOW);
                            
                            digitalWrite(bleft1,HIGH);
                            digitalWrite(bleft2,LOW);
                           
                            digitalWrite(left1,HIGH);
                            digitalWrite(left2,LOW);
                            
                            digitalWrite(right1,HIGH);
                            digitalWrite(right2,LOW);
                            
                            digitalWrite(behind1,HIGH);
                            digitalWrite(behind2,LOW);
                            
                            digitalWrite(front1, HIGH);
                            digitalWrite(front2, LOW);
                 
                    
                    for(int i=50;i<250;i=i+10)
                    {
                          analogWrite(pwm1,i);
                          analogWrite(pwm2,i);
                          analogWrite(pwm3,i);
                          analogWrite(pwm4,i);
                          analogWrite(pwm5,i);
                          analogWrite(pwm6,i);
                          analogWrite(pwm7,i);
                          analogWrite(pwm8,i);
                          delay(10);
                          
                    }
                    
                    digitalWrite(pwm1,HIGH);
                    digitalWrite(pwm2,HIGH);
                    digitalWrite(pwm3,HIGH);
                    digitalWrite(pwm4,HIGH);
                    digitalWrite(pwm5,HIGH);
                    digitalWrite(pwm6,HIGH);
                    digitalWrite(pwm7,HIGH);
                    digitalWrite(pwm8,HIGH);
                    
                    Serial.println("turning right");
                            lcd.clear();
                            lcd.print("Turning Right");          
        }//end of turn right
        
        
        //turn left
        if(ps2x.Button(PSB_PAD_LEFT))
          {
                            digitalWrite(fright1,LOW);
                            digitalWrite(fright2,HIGH);
                            
                            digitalWrite(fleft1,LOW);
                            digitalWrite(fleft2,HIGH);
                            
                            digitalWrite(bright1,LOW);
                            digitalWrite(bright2,HIGH);
                            
                            digitalWrite(bleft1,LOW);
                            digitalWrite(bleft2,HIGH);
                            
                            digitalWrite(left1,LOW);
                            digitalWrite(left2,HIGH);
                            
                            digitalWrite(right1,LOW);
                            digitalWrite(right2,HIGH);
                           
                            digitalWrite(behind1,LOW);
                            digitalWrite(behind2,HIGH);
                            
                            digitalWrite(front1, LOW);
                            digitalWrite(front2, HIGH);                            
                    
                    
                    for(int i=60;i<250;i=i+10)
                    {
                          analogWrite(pwm1,i);
                          analogWrite(pwm2,i);
                          analogWrite(pwm3,i);
                          analogWrite(pwm4,i);
                          analogWrite(pwm5,i);
                          analogWrite(pwm6,i);
                          analogWrite(pwm7,i);
                          analogWrite(pwm8,i);
                          delay(10);
                          
                    }
                    
                    digitalWrite(pwm1,HIGH);
                    digitalWrite(pwm2,HIGH);
                    digitalWrite(pwm3,HIGH);
                    digitalWrite(pwm4,HIGH);
                    digitalWrite(pwm5,HIGH);
                    digitalWrite(pwm6,HIGH);
                    digitalWrite(pwm7,HIGH);
                    digitalWrite(pwm8,HIGH);
                    
                    Serial.println("turning left");

                            lcd.clear();
                            lcd.print("Turning Left");          
        }//end of turn left
          
          
         if(ps2x.ButtonPressed(PSB_R1))
          {
                   Serial.println("see-saw arm up");
                   digitalWrite(rarm1,HIGH);
                   
                   
          }
           if(ps2x.ButtonReleased(PSB_R1))
          {
                   Serial.println("see-saw arm off");
                   digitalWrite(rarm1,LOW);
                   
                   
          }
        
          //left arm up
          
          if(ps2x.ButtonPressed(PSB_L1))
          int x=map(ps2x.Analog(PSB_L1),0,255,50,255);
          {

            Serial.println("left arm up");

                   digitalWrite(larm1,HIGH);
                   digitalWrite(larm2,HIGH);
                   analogWrite(pwm9,x);
                   flaglarm=true;
                   
          }
            if(ps2x.ButtonReleased(PSB_L1))
          {

            Serial.println("left arm Stop");

                   digitalWrite(larm1,LOW);
                   digitalWrite(larm2,HIGH);
                   analogWrite(pwm9,x);
                   flaglarm=false;

                   
          }
          
          //left arm down
          if(ps2x.ButtonPressed(PSB_L2))
          int x=map(ps2x.Analog(PSB_L2),0,255,50,255);
          {
                 Serial.println("left arm down");

                   digitalWrite(larm1,LOW);
                   digitalWrite(larm2,LOW);
                   analogWrite(pwm9,x);
                   flaglarm=true;
                   

                   
          }
          
            if(ps2x.ButtonReleased(PSB_L2))
          {
                 Serial.println("left arm stop");

                   digitalWrite(larm1,HIGH);
                   digitalWrite(larm2,LOW);
                   analogWrite(pwm9,x);
                   flaglarm=false;
                 
                  
          }
          
           //swing arm
          if(ps2x.Analog(PSS_LY)<100)
          int x=map(ps2x.Analog(PSS_LY),100,0,50,255);
          {
                Serial.println("swing arm up");

                   digitalWrite(sw1,HIGH);
                   digitalWrite(sw2,HIGH);
                   analogWrite(pwm10,x);
                   flagsarm=true;
                   
          }
        
          
          //middle arm down
          else if(ps2x.Analog(PSS_RY)>150)
          int x=map(ps2x.Analog(PSS_LY),150,255,50,255);
          {
                 Serial.println("swing arm down");

                   digitalWrite(sw1,LOW);
                   digitalWrite(sw2,LOW);
                   analogWrite(pwm10,x);
                   flagsarm=true;

          }
          //swing arm stop
           else if(ps2x.Analog(PSS_RY)==123 && flagsarm)
          {
                  Serial.println("swing arm Stop");

                   digitalWrite(sw1,HIGH);
                   digitalWrite(sw2,LOW);
                   analogWrite(pwm10,x);
                   flagsarm=false;
                   
          }
          
           
          //left gripper
         if(ps2x.ButtonReleased(PSB_PINK))
        {
                     Serial.println("Gripper switched");
                    left=!left;
                    digitalWrite(lg1,left);
          }
         
          //swing gripper            
          if(ps2x.ButtonReleased(PSB_GREEN))
          {
                    Serial.println("Gripper switched");

                    swing=!swing;
                    digitalWrite(sw1,swing);
                    
          }
          
         
          
          
          delay(100);
          
                            digitalWrite(fright1,LOW);
                            digitalWrite(fright2,LOW);
                            
                            digitalWrite(fleft1,LOW);
                            digitalWrite(fleft2,LOW);
                            
                            digitalWrite(bright1,LOW);
                            digitalWrite(bright2,LOW);
                            
                            digitalWrite(bleft1,LOW);
                            digitalWrite(bleft2,LOW);
                           
                            digitalWrite(left1,LOW);
                            digitalWrite(left2,LOW);
                            
                            digitalWrite(right1,LOW);
                            digitalWrite(right2,LOW);
                            
                            digitalWrite(behind1,LOW);
                            digitalWrite(behind2,LOW);
                            
                            digitalWrite(front1, LOW);
                            digitalWrite(front2, LOW);
                            
                            lcd.print("Hello");
                            lcd.setCursor(0,1);
                            lcd.print("Be Patient");
                            
        
}
                    
                    
                    
                    
                    
