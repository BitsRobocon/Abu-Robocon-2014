#include <LiquidCrystal.h>

#include <PS2X_lib.h>  //for v1.6

LiquidCrystal lcd(14,15,16,17,18,19);

PS2X ps2x; // create PS2 Controller Class
boolean flagsarm=false;
boolean flaglarm=false;
int error = 0; 
byte type = 0;
byte vibrate = 0;

int flag = 0;
int time=0;
int nettime1=0;
int nettime2=0;

//motor pins

          int front1=36;
          int front2=37;
          int right1=44  ; //right
          int right2=45  ; //right
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
          int larm1=48;//left arm
          int larm2=49;//left arm
          int sarm1=40;//swing arm
          int sarm2=41;//swing arm
          
          
          
         
          
          
//pwm pins          
          int pwm1=7 ;  //front
          int pwm2=4  ; //front right
          int pwm3=12  ; //right
          int pwm4=11  ; //behind right
          int pwm6=9  ; //behind left
          int pwm7=8  ; //left
          int pwm8=6  ; //front left 
          int pwm9=5;//left arm
          int pwm10=10;//swing arm
  
  
  
          boolean left=LOW;         
          boolean swing=LOW; 
          boolean right=LOW;         
        
         
          
//pnematic pins + solenoid + relays

          
          int rarm2=31  ; // SEE-SAW arm
          
          int lg2=33  ; //left GRIPPER
          
          int sw2=30  ; //swing arm gripper
         
          
void setup(){
  
//serial on  
         Serial.begin(57600);
         
         //lcd on         
          lcd.begin(16, 2);

//define output
         
         pinMode(front1,OUTPUT);
         pinMode(front2,OUTPUT);
         pinMode(fright1,OUTPUT);
         pinMode(fright2,OUTPUT);
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
         pinMode(pwm6,OUTPUT);
         pinMode(pwm7,OUTPUT);
         pinMode(pwm8,OUTPUT);
         pinMode(pwm9,OUTPUT);
         pinMode(pwm10,OUTPUT);
         
        
        
      
        
         pinMode(rarm2,OUTPUT);
        
         pinMode(sw2,OUTPUT);
         
         pinMode(lg2,OUTPUT);
        
      

         //setting solenoid valve grounds
           digitalWrite(lg2,LOW);
           digitalWrite(sw2,LOW);
           digitalWrite(rarm2,LOW);
                   
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
                 lcd.clear();         
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
           
               if(ps2x.Button(PSB_START)&&flag==0)     //to start the timmer
                                                                                                     {
                                                                                                       flag=1;
                                                                                                       time=millis()/1000;
                                                                                                     }
           
           if(flag>=1)
           {
           
           //navigation
        
           
           int x1=map(ps2x.Analog(PSS_LX),100,0,50,255);
           int x2=map(ps2x.Analog(PSS_LX),150,255,50,255);
           int y1=map(ps2x.Analog(PSS_LY),100,0,50,255);
           int y2=map(ps2x.Analog(PSS_LY),150,255,50,255);
           int x=map(ps2x.Analog(PSB_L1),0,255,50,255);
           int p1=map(ps2x.Analog(PSS_RX),150,255,50,255);
           int p2=map(ps2x.Analog(PSS_RX),100,0,50,255);
           int z1=map(ps2x.Analog(PSS_RY),150,255,50,255);
           int z2=map(ps2x.Analog(PSS_RY),100,0,50,255);
      
          
          
    if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)>150)) 
          {   digitalWrite(fright2,HIGH);
              digitalWrite(fright1,LOW); 
              analogWrite(pwm2,abs(0.707*(float)x2));
          }   
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(fright2 ,LOW);
              digitalWrite(fright1 ,HIGH);
              analogWrite(pwm2,abs(0.707*(float)x1));
          }    
          else if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(fright2 ,LOW);
              digitalWrite(fright1 ,LOW);
              analogWrite(pwm2,0);
          }    
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(fright1 ,LOW);
              digitalWrite(fright2 ,LOW);
              analogWrite(pwm2,0); 
          }    
          else if((ps2x.Analog(PSS_LX)>100)&&(ps2x.Analog(PSS_LX)<150))
          {   if (ps2x.Analog(PSS_LY)>150)
             { digitalWrite(fright2 ,HIGH);
               digitalWrite(fright1 ,LOW);
               analogWrite(pwm2,y2);
             }
            else if (ps2x.Analog(PSS_LY)<100)
             { digitalWrite(fright2 ,LOW);
              digitalWrite(fright1 ,HIGH);
              analogWrite(pwm2,y1);
             }
          }    
          else if((ps2x.Analog(PSS_LY)>100)&&(ps2x.Analog(PSS_LY)<150))
          {   if (ps2x.Analog(PSS_LX)>150)
            { digitalWrite(fright2 ,HIGH);
              digitalWrite(fright1 ,LOW);
              analogWrite(pwm2,0.76*(float)x2);
            } 
            else if (ps2x.Analog(PSS_LX)<100)
            { digitalWrite(fright2 ,LOW);
              digitalWrite(fright1 ,HIGH);
              analogWrite(pwm2,0.76*(float)x1);  
            }  
          }   
       
      
        if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)>150)) 
          {   digitalWrite(bleft1,HIGH);
              digitalWrite(bleft2,LOW); 
              analogWrite(pwm6,abs(0.707*(float)x2));
          }   
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(bleft1 ,LOW);
              digitalWrite(bleft2 ,HIGH);
              analogWrite(pwm6,abs(0.707*(float)x1));
          }    
          else if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(bleft1 ,LOW);
              digitalWrite(bleft2 ,LOW);
              analogWrite(pwm6,0);
          }    
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(bleft1 ,LOW);
              digitalWrite(bleft2 ,LOW);
              analogWrite(pwm6,0); 
          }    
          else if((ps2x.Analog(PSS_LX)>100)&&(ps2x.Analog(PSS_LX)<150))
          {   if (ps2x.Analog(PSS_LY)>150)
             { digitalWrite(bleft1 ,HIGH);
               digitalWrite(bleft2 ,LOW);
               analogWrite(pwm6,y2);
             }
            else if (ps2x.Analog(PSS_LY)<100)
             { digitalWrite(bleft1 ,LOW);
              digitalWrite(bleft2 ,HIGH);
              analogWrite(pwm6,y1);
             }
          }    
          else if((ps2x.Analog(PSS_LY)>100)&&(ps2x.Analog(PSS_LY)<150))
          {   if (ps2x.Analog(PSS_LX)>150)
            { digitalWrite(bleft1 ,HIGH);
              digitalWrite(bleft2 ,LOW);
              analogWrite(pwm6,x2);
            } 
            else if (ps2x.Analog(PSS_LX)<100)
            { digitalWrite(bleft1 ,LOW);
              digitalWrite(bleft2 ,HIGH);
              analogWrite(pwm6,x1);  
            }  
          }     
       
       //DONE
          if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(right1,LOW);
              digitalWrite(right2,HIGH); 
              analogWrite(pwm3,abs(x2));
          }   
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(right1 ,HIGH);
              digitalWrite(right2 ,LOW);
              analogWrite(pwm3,abs(x1));
          }    
          else if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(right1 ,LOW);
              digitalWrite(right2 ,HIGH);
              analogWrite(pwm3,abs(y2));
          }    
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(right1 ,HIGH);
              digitalWrite(right2 ,LOW);
              analogWrite(pwm3,abs(y1)); 
          }    
          else if((ps2x.Analog(PSS_LX)>100)&&(ps2x.Analog(PSS_LX)<150))
          {   if (ps2x.Analog(PSS_LY)>150)
             { digitalWrite(right1 ,LOW);
              digitalWrite(right2 ,HIGH);
              analogWrite(pwm3,0.707*(float)y2);
             }
            else if (ps2x.Analog(PSS_LY)<100)
             { digitalWrite(right1 ,HIGH);
              digitalWrite(right2 ,LOW);
              analogWrite(pwm3,0.707*(float)y1);
             }
            
          }    
          else if((ps2x.Analog(PSS_LY)>100)&&(ps2x.Analog(PSS_LY)<150))
          {   if (ps2x.Analog(PSS_LX)>150)
            { digitalWrite(right1 ,LOW);
              digitalWrite(right2 ,LOW);
              analogWrite(pwm3,x2);
            } 
            else if (ps2x.Analog(PSS_LX)<100)
            { digitalWrite(right1 ,LOW);
              digitalWrite(right2 ,LOW);
              analogWrite(pwm3,x1);  
            }  
          }     
       
       
          if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(left1,HIGH);
              digitalWrite(left2,LOW); 
              analogWrite(pwm7,0.707*(float)x2);
          }   
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(left1 ,LOW);
              digitalWrite(left2 ,HIGH);
              analogWrite(pwm7,abs(x1));
          }    
          else if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(left1 ,HIGH);
              digitalWrite(left2 ,LOW);
              analogWrite(pwm7,abs(y2));
          }    
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(left1 ,LOW);
              digitalWrite(left2 ,HIGH);
              analogWrite(pwm7,abs(y1)); 
          }    
          else if((ps2x.Analog(PSS_LX)>100)&&(ps2x.Analog(PSS_LX)<150))
          {   if (ps2x.Analog(PSS_LY)>150)
            {  digitalWrite(left1 ,HIGH);
              digitalWrite(left2 ,LOW);
              analogWrite(pwm7,abs(0.707*(float)y2));
            }
            else if (ps2x.Analog(PSS_LY)<100)
            {  digitalWrite(left1 ,LOW);
              digitalWrite(left2 ,HIGH);
              analogWrite(pwm7,abs(0.707*(float)y1));
            }
           
          }    
          else if((ps2x.Analog(PSS_LY)>100)&&(ps2x.Analog(PSS_LY)<150))
          {   if (ps2x.Analog(PSS_LX)>150)
            { digitalWrite(left1 ,LOW);
              digitalWrite(left2 ,LOW);
              analogWrite(pwm7,0);
            } 
            else if (ps2x.Analog(PSS_LX)<100)
            { digitalWrite(left1 ,LOW);
              digitalWrite(left2 ,LOW);
              analogWrite(pwm7,0);  
            }  
          }     
       
     
        if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(bright1,LOW);
              digitalWrite(bright2,LOW); 
              analogWrite(pwm4,0);
          }   
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(bright1 ,LOW);
              digitalWrite(bright2 ,LOW);
              analogWrite(pwm4,0);
          }    
          else if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(bright1 ,LOW);
              digitalWrite(bright2 ,HIGH);
              analogWrite(pwm4,abs(0.707*(float)y2 ));
          }    
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(bright1 ,HIGH);
              digitalWrite(bright2 ,LOW);
              analogWrite(pwm4,abs(0.707*(float)x2 )); 
          }    
          else if((ps2x.Analog(PSS_LX)>100)&&(ps2x.Analog(PSS_LX)<150))
          {   if (ps2x.Analog(PSS_LY)>150)
            {  digitalWrite(bright1 ,LOW);
              digitalWrite(bright2 ,HIGH);
              analogWrite(pwm4,y2);
            }
            else if (ps2x.Analog(PSS_LY)<100)
            {  digitalWrite(bright1 ,HIGH);
              digitalWrite(bright2 ,LOW);
              analogWrite(pwm4,y1);
            }
          }    
          else if((ps2x.Analog(PSS_LY)>100)&&(ps2x.Analog(PSS_LY)<150))
          {   if (ps2x.Analog(PSS_LX)>150)
            { digitalWrite(bright1 ,HIGH);
              digitalWrite(bright2 ,LOW);
              analogWrite(pwm4,x2);
            } 
            else if (ps2x.Analog(PSS_LX)<100)
            { digitalWrite(bright1 ,LOW);
              digitalWrite(bright2 ,HIGH);
              analogWrite(pwm4,x1);  
            }  
          }     
          
     
        if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(fleft1,LOW);
              digitalWrite(fleft2,LOW); 
              analogWrite(pwm8,0);
          }   
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(fleft1 ,LOW);
              digitalWrite(fleft2 ,LOW);
              analogWrite(pwm6,0);
          }    
          else if ((ps2x.Analog(PSS_LY)>150)&&(ps2x.Analog(PSS_LX)<100))
          {   digitalWrite(fleft1 ,LOW);
              digitalWrite(fleft2 ,HIGH);
              analogWrite(pwm8,abs(0.707*(float)x1));
          }    
          else if ((ps2x.Analog(PSS_LY)<100)&&(ps2x.Analog(PSS_LX)>150))
          {   digitalWrite(fleft1 ,HIGH);
              digitalWrite(fleft2 ,LOW);
              analogWrite(pwm8,abs(0.707*(float)x2)); 
          }    
          else if ((ps2x.Analog(PSS_LX)>100)&&(ps2x.Analog(PSS_LX)<150))
          {   if (ps2x.Analog(PSS_LY)>150)
            {  digitalWrite(fleft1 ,LOW);
              digitalWrite(fleft2 ,HIGH);
              analogWrite(pwm8,y2);
            }
            else if(ps2x.Analog(PSS_LY)<100)
            {  digitalWrite(fleft1 ,HIGH);
              digitalWrite(fleft2 ,LOW);
              analogWrite(pwm8,y1);
            }  
          }    
          else if((ps2x.Analog(PSS_LY)>100)&&(ps2x.Analog(PSS_LY)<150))
          {   if (ps2x.Analog(PSS_LX)>150)
            { digitalWrite(fleft1 ,HIGH);
              digitalWrite(fleft2 ,LOW);
              analogWrite(pwm8,0.76*(float)x2);
            } 
            else if (ps2x.Analog(PSS_LX)<100)
            { digitalWrite(fleft1 ,LOW);
              digitalWrite(fleft2 ,HIGH);
              analogWrite(pwm8,0.76*(float)x1);  
            }  
          }  
      if((ps2x.Analog(PSS_RY)>100)&&(ps2x.Analog(PSS_RY)<150)) 
      { if (ps2x.Analog(PSS_RX)>150)
        { digitalWrite(front1, LOW);
          digitalWrite(front2, HIGH);
          analogWrite(pwm1,0.707*(float)p1);  
        }
       else if (ps2x.Analog(PSS_RX)<100)
        { digitalWrite(front1, HIGH);
          digitalWrite(front2, LOW);
          analogWrite(pwm1,0.707*(float)p2);  
        }
      }
      if((ps2x.Analog(PSS_LY)>100)&&(ps2x.Analog(PSS_LY)<150)) 
      { if (ps2x.Analog(PSS_LX)>150)
        { digitalWrite(front1, LOW);
          digitalWrite(front2, HIGH);
          analogWrite(pwm1,0.76*(float)x2);  
        }
       else if (ps2x.Analog(PSS_LX)<100)
        { digitalWrite(front1, HIGH);
          digitalWrite(front2, LOW);
          analogWrite(pwm1,0.76*(float)x1);  
        }
      }
       
       
         
       
          if(ps2x.Button(PSB_PAD_LEFT))
          {
                            digitalWrite(fright1,HIGH);
                            digitalWrite(fright2,LOW);
                            
                            digitalWrite(fleft1,LOW);
                            digitalWrite(fleft2,HIGH);
                            
                            digitalWrite(bright1,HIGH);
                            digitalWrite(bright2,LOW);
                            
                            digitalWrite(bleft1,HIGH);
                            digitalWrite(bleft2,LOW);
                           
                            digitalWrite(left1,HIGH);
                            digitalWrite(left2,LOW);
                            
                            digitalWrite(right1,HIGH);
                            digitalWrite(right2,LOW);
                            
                         
                 
                    
                    for(int i=50;i<140;i=i+10)
                    {
                          
                          analogWrite(pwm2,0.75*(float)i);
                          analogWrite(pwm3,0.75*(float)i);
                          analogWrite(pwm4,0.75*(float)i);
                          analogWrite(pwm6,0.75*(float)i);
                          analogWrite(pwm7,0.75*(float)i);
                          analogWrite(pwm8,0.75*(float)i);
                          delay(10);
                          
                    }
                       for(int i=140;i>60;i=i-20)
                    {
                          
                          analogWrite(pwm2,0.75*(float)i);
                          analogWrite(pwm3,0.75*(float)i);
                          analogWrite(pwm4,0.75*(float)i);
                          analogWrite(pwm6,0.75*(float)i);
                          analogWrite(pwm7,0.75*(float)i);
                          analogWrite(pwm8,0.75*(float)i);
                          delay(10);
                          
                    }
                    
                   
                    digitalWrite(pwm2,HIGH);
                    digitalWrite(pwm3,HIGH);
                    digitalWrite(pwm4,HIGH);
                    digitalWrite(pwm6,HIGH);
                    digitalWrite(pwm7,HIGH);
                    digitalWrite(pwm8,HIGH);
                    
                    Serial.println("turning left");
          
        }//end of turn right
        
        
        //turn left
        if(ps2x.Button(PSB_PAD_RIGHT))
          {
                            digitalWrite(fright1,LOW);
                            digitalWrite(fright2,HIGH);
                            
                            digitalWrite(fleft1,HIGH);
                            digitalWrite(fleft2,LOW);
                            
                            digitalWrite(bright1,LOW);
                            digitalWrite(bright2,HIGH);
                            
                            digitalWrite(bleft1,LOW);
                            digitalWrite(bleft2,HIGH);
                            
                            digitalWrite(left1,LOW);
                            digitalWrite(left2,HIGH);
                            
                            digitalWrite(right1,LOW);
                            digitalWrite(right2,HIGH);
                           
                    
                    for(int i=60;i<140;i=i+10)
                    {
                          
                          analogWrite(pwm2,0.75*(float)i);
                          analogWrite(pwm3,0.75*(float)i);
                          analogWrite(pwm4,0.75*(float)i);
                          analogWrite(pwm6,0.75*(float)i);
                          analogWrite(pwm7,0.75*(float)i);
                          analogWrite(pwm8,0.75*(float)i);
                          delay(10);
                          
                    }
                      for(int i=140;i>60;i=i-20)
                    {
                          
                          analogWrite(pwm2,0.75*(float)i);
                          analogWrite(pwm3,0.75*(float)i);
                          analogWrite(pwm4,0.75*(float)i);
                          analogWrite(pwm6,0.75*(float)i);
                          analogWrite(pwm7,0.75*(float)i);
                          analogWrite(pwm8,0.75*(float)i);
                          delay(10);
                          
                    }
                    
                  
                    digitalWrite(pwm2,HIGH);
                    digitalWrite(pwm3,HIGH);
                    digitalWrite(pwm4,HIGH);
                    digitalWrite(pwm6,HIGH);
                    digitalWrite(pwm7,HIGH);
                    digitalWrite(pwm8,HIGH);
                    
                    Serial.println("turning right");
          
        }//end of turn left
          
        
          
           if(ps2x.Button(PSB_L1))
        
          {
            
            Serial.println("left arm up");
 
                   digitalWrite(larm1,HIGH);
                   digitalWrite(larm2,LOW);
                   analogWrite(pwm9,x);
                   flaglarm=true;
                   Serial.println("pressed");
                  }
                 
                   

          
          //left arm down
          else if(ps2x.Button(PSB_L2))
      
          {
                 Serial.println("left arm down");

                   digitalWrite(larm1,LOW);
                   digitalWrite(larm2,HIGH);
                   analogWrite(pwm9,x);
                   flaglarm=true;
                   

                   
          }
          else
          {
            Serial.println("left arm stop");

                   digitalWrite(larm1,HIGH);
                   digitalWrite(larm2,HIGH);
                   analogWrite(pwm9,0);
                   
          }
            
          
           //swing arm
          if(ps2x.Analog(PSS_RY)<100)
          
          {
                Serial.println("swing arm up");


                   digitalWrite(sarm1,HIGH);
                   digitalWrite(sarm1,LOW);
                 
                analogWrite(pwm10,z2);
                   flagsarm=true;
                   
          }
        
          
          //middle arm down
          else if(ps2x.Analog(PSS_RY)>150)
          {
                 Serial.println("swing arm down");

                   digitalWrite(sarm1,LOW);
                   digitalWrite(sarm2,HIGH);
                   analogWrite(pwm10,z1);
                   flagsarm=true;

          }
          //swing arm stop
           else if(ps2x.Analog(PSS_RY)==123 && flagsarm)
          {
                  Serial.println("swing arm Stop");

                   digitalWrite(sarm1,LOW);
                   digitalWrite(sarm2,LOW);
                   analogWrite(pwm10,0);
                   flagsarm=false;
                   
          }
            
         if(ps2x.ButtonPressed(PSB_BLUE))
          {
                   Serial.println("see-saw arm up");
                   right=!right;
                   digitalWrite(rarm2,right);
                   
                   
          }
          
        
          //left arm up
           
          //left gripper
         if(ps2x.ButtonReleased(PSB_PINK))
        {
                     Serial.println("Gripper switched");
                    left=!left;
                    digitalWrite(lg2,left);
          }
         
          //swing gripper            
          if(ps2x.ButtonReleased(PSB_GREEN))
          {
                    Serial.println("Gripper switched");

                    swing=!swing;
                    digitalWrite(sw2,swing);
                    
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
                            
                            digitalWrite(front1,LOW);
                            digitalWrite(front2,LOW);
                            
                            digitalWrite(sarm1,LOW);
                            digitalWrite(sarm1,LOW);
                            
                            digitalWrite(larm1,LOW);
                            digitalWrite(larm2,LOW);
                            
                            
                             lcd.clear();
                            nettime1= (millis()/1000)-time ;
 
                             lcd.setCursor(6,1);
                               if(nettime1<60)
                            {
                             
                              lcd.print("00:");
                              lcd.print(nettime1);
                            }
                            if(nettime1>=60&&nettime1<120)
                              {  
                              nettime2=nettime1-60;
                              if(nettime2>=0&&nettime2<10)
                                  {
                                    lcd.print("01:0");
                                    lcd.print(nettime2);
                                  }
                            else
                               {
                                  lcd.print("01:");
                                  lcd.print(nettime2);
                                }
                            
                           }
                              if(nettime1>=120&&nettime1<180)
                       {        
       
                              nettime2=nettime1-120;
                              if(nettime2>=0&&nettime2<10)
                              {
                              lcd.print("02:0");
                              lcd.print(nettime2);
                            }
                            else
                             {
                              lcd.print("02:");
                              lcd.print(nettime2);
                             }
                       }
                              if(nettime1>180)
                              {
                                lcd.print("Times Ups");
                              }
                              
                            
                            
                             if(ps2x.Button(PSB_SELECT))
                              {
                                flag++;
                            
                                if(flag>=5)
                                {
                                  flag=1;
                                }
                                delay(200);
                              }
                              
                              if(flag==2)
                              {
                                lcd.clear();
                                lcd.print("See-Saw");
                              }
                              if(flag==3)
                              {
                                lcd.clear();
                                lcd.print("Swing");
                              }
                              if(flag==4)
                              {
                                lcd.clear();
                                lcd.print("Pole Walk");
                              }
                              
                                if(ps2x.Button(PSB_START)&&flag==2)     //for see-saw
                                {
                                  Serial.println(12);
                                  delay(200);
                                  flag=1;
                                }
                                if(ps2x.Button(PSB_START)&&flag==3)     //for swing
                                {
                                  Serial.println(23);
                                  delay(200);
                                  flag=1;
                                }
                                if(ps2x.Button(PSB_START)&&flag==4)    //for pole walk
                                {
                                  Serial.println(13);
                                  delay(200);
                                  flag=1;
                                }
                            
                                  
        }


                                             else   if(flag==0)            //else for start if ,for timmer
                                             {
                                              lcd.print("Press Start But.");
                                              lcd.setCursor(0,1);
                                              lcd.print("  All the Best   ");
                                             }


}                 
                    
                    
                    
                    
