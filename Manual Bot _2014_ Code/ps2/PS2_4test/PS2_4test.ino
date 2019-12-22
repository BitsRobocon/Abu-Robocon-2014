#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class
boolean flagma=false;
boolean flagex=false;
int error = 0; 
byte type = 0;
byte vibrate = 0;
int high=8;
//motor pins

          int ma1=22;//right
          int ma2=23;//right
          int mb1=24;//left
          int mb2=25;//left
          int mc1=26;//front
          int mc2=27;//front
          int md1=28;//behind
          int md2=29;//behind
          
//pwm pins          
          int pwm1=3;
          int pwm2=4;
          int pwm3=5;
          int pwm4=6;
          
          
//relay pins          
          int ar1=32;
          int ar2=33;
          int al1=34;
          int al2=35;
          int am1=36;
          int am2=37;
          int ext1=38;
          int ext2=39;
          
//pnematic pins

          int rg1=42;//zero
          int rg2=43;
          int lg1=44;//zero
          int lg2=45;
          int mg1=46;//zero
          int mg2=47;
          
//gripper switcher

          boolean left=LOW;
          boolean right=LOW;
          boolean middle=LOW;
          
          

void setup(){
  
//serial on  
         Serial.begin(57600);

//define output
         
         pinMode(ma1,OUTPUT);
         pinMode(ma2,OUTPUT);
         pinMode(mb1,OUTPUT);
         pinMode(mb2,OUTPUT);
         pinMode(mc1,OUTPUT);
         pinMode(mc2,OUTPUT);
         pinMode(md1,OUTPUT);
         pinMode(md2,OUTPUT);
         
         pinMode(pwm1,OUTPUT);
         pinMode(pwm2,OUTPUT);
         pinMode(pwm3,OUTPUT);
         pinMode(pwm4,OUTPUT);
         
         pinMode(ar1,OUTPUT);
         pinMode(ar2,OUTPUT);
         pinMode(al1,OUTPUT);
         pinMode(al2,OUTPUT);
         pinMode(am1,OUTPUT);
         pinMode(am2,OUTPUT);
         pinMode(ext1,OUTPUT);
         pinMode(ext2,OUTPUT);
         
         pinMode(rg1,OUTPUT);
         pinMode(rg2,OUTPUT);
         pinMode(lg1,OUTPUT);
         pinMode(lg2,OUTPUT);
         pinMode(mg1,OUTPUT);
         pinMode(mg2,OUTPUT);
                  pinMode(high,OUTPUT);
                  digitalWrite(high,HIGH);
                            digitalWrite(lg2,HIGH);

         //setting solenoid valve grounds
           digitalWrite(rg1,LOW);
           digitalWrite(lg1,LOW);
           digitalWrite(mg1,LOW);
           
           digitalWrite(al1,LOW);
           digitalWrite(al2,HIGH);
           digitalWrite(ar1,LOW);
           digitalWrite(ar2,HIGH);
           digitalWrite(am1,LOW);
           digitalWrite(am2,HIGH);
                   
         error = ps2x.config_gamepad(13,11,10,12, true, true);   //GamePad(clock(blue), command(orange), attention(yellow), data(brown), Pressures?, Rumble?
         //13-blue
         //12-brown
         //11-orange
         //10-yellow
 
         if(error == 0)
{
                 Serial.println("Found Controller, configured successful");
                 Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
                 Serial.println("holding L1 or R1 will print out the analog stick values.");
                 Serial.println("Go to www.billporter.info for updates and to report bugs.");
         }
           
          else if(error == 1)
                 Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
           
          else if(error == 2)
                 Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
           
          else if(error == 3)
                 Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
 
           
           type = ps2x.readType();
                            

 

}

void loop(){

  
            
           ps2x.read_gamepad(false, vibrate); 
           
           //navigation
           
         
           
           
           if((ps2x.Analog(PSS_RX)!=123)||(ps2x.Analog(PSS_RY)!=123))
           {
                  //Serial.print("Stick Values:");
                  
                  //Serial.print(ps2x.Analog(PSS_RY), DEC); 
                  //Serial.print(",");
                  //Serial.println(ps2x.Analog(PSS_RX), DEC);
                  //backward(motors on left and right)
                  if(ps2x.Analog(PSS_RY)<100)
                  
                  {
                  
                            int x=map(ps2x.Analog(PSS_RY),100,0,50,255);
                            
                            digitalWrite(ma1,LOW);
                            digitalWrite(ma2,HIGH);
                            
                            digitalWrite(mb1,LOW);
                            digitalWrite(mb2,HIGH);
                            
                            analogWrite(pwm1,x);
                            analogWrite(pwm2,x);
                
                            
                            Serial.print("backward @ ");
                            Serial.println(x);
                    
                   }//end backward
                    
                    //forward(motors on left and right)
                    if(ps2x.Analog(PSS_RY)>150)
        
                    {
                            int x=map(ps2x.Analog(PSS_RY),150,255,50,255);
                            
                            digitalWrite(ma1,HIGH);
                            digitalWrite(ma2,LOW);
                            
                            digitalWrite(mb1,HIGH);
                            digitalWrite(mb2,LOW);
                           
                            analogWrite(pwm1,x);
                            analogWrite(pwm2,x);
                            
                            Serial.print("forward @ ");
                            Serial.println(x);
                        
                    }//end forward
                    
                    //left(motors on front and back)
                    else if(ps2x.Analog(PSS_RX)<100)
        
                    {
                        
                            int x=map(ps2x.Analog(PSS_RX),100,0,50,255);
                            
                            digitalWrite(mc1,LOW);
                            digitalWrite(mc2,HIGH);
                            
                            digitalWrite(md1,LOW);
                            digitalWrite(md2,HIGH);
                           
                            analogWrite(pwm3,x);
                            analogWrite(pwm4,x);
                            
                            Serial.print("left @ ");
                            Serial.println(x);
                            
                    }//emd left
                   
                
                    //right(motors on front and back)
                    else if(ps2x.Analog(PSS_RX)>150)
        
                    {
                      
                              int x=map(ps2x.Analog(PSS_RX),150,255,50,255);
                              
                              digitalWrite(mc1,HIGH);
                              digitalWrite(mc2,LOW);
                              
                              digitalWrite(md1,HIGH);
                              digitalWrite(md2,LOW);
                              
                              analogWrite(pwm3,x);
                              analogWrite(pwm4,x);            
                              
                              Serial.print("right @ ");
                              Serial.println(x);
        
                    }//end of right
       
          }// end of navigation
          
          //turn right
          if(ps2x.Button(PSB_PAD_RIGHT))
          {
            
                    digitalWrite(ma1,HIGH);
                    digitalWrite(ma2,LOW);
                 
                    digitalWrite(mb1,LOW);
                    digitalWrite(mb2,HIGH);
                    
                   digitalWrite(mc1,LOW);
                    digitalWrite(mc2,HIGH);
                          
                    digitalWrite(md1,LOW);
                    digitalWrite(md2,HIGH);
                    
                    for(int i=50;i<250;i=i+10)
                    {
                          analogWrite(pwm1,i);
                          analogWrite(pwm2,i);
                          analogWrite(pwm3,i);
                          analogWrite(pwm4,i);
                          delay(10);
                          
                    }
                    
                    digitalWrite(pwm1,HIGH);
                    digitalWrite(pwm2,HIGH);
                    digitalWrite(pwm3,HIGH);
                    digitalWrite(pwm4,HIGH);
                    
                    Serial.println("turning right");
          
        }//end of turn right
        
        
        //turn left
        if(ps2x.Button(PSB_PAD_LEFT))
          {
            
                    digitalWrite(ma1,LOW);
                    digitalWrite(ma2,HIGH);
                 
                    digitalWrite(mb1,HIGH);
                    digitalWrite(mb2,LOW);
                    
                    digitalWrite(mc1,HIGH);
                    digitalWrite(mc2,LOW);
                          
                    digitalWrite(md1,HIGH);
                    digitalWrite(md2,LOW);
                    
                    for(int i=60;i<250;i=i+10)
                    {
                          analogWrite(pwm1,i);
                          analogWrite(pwm2,i);
                          analogWrite(pwm3,i);
                          analogWrite(pwm4,i);
                          delay(10);
                          
                    }
                    
                    digitalWrite(pwm1,HIGH);
                    digitalWrite(pwm2,HIGH);
                    digitalWrite(pwm3,HIGH);
                    digitalWrite(pwm4,HIGH);
                    
                    Serial.println("turning left");
          
        }//end of turn left
          
          //
          //
          //arm movement relays
          //
          //right arm up
          if(ps2x.ButtonPressed(PSB_R1))
          {
                   Serial.println("right arm up");
                   digitalWrite(ar1,HIGH);
                   digitalWrite(ar2,HIGH);
                   
          }
           if(ps2x.ButtonReleased(PSB_R1))
          {
                   Serial.println("right arm off");
                   digitalWrite(ar1,LOW);
                   digitalWrite(ar2,HIGH);
                   
          }
        //right arm down
          if(ps2x.ButtonPressed(PSB_R2))
          {
                   Serial.println("right arm down");
                   digitalWrite(ar1,LOW);
                   digitalWrite(ar2,LOW);
                   
          }
           if(ps2x.ButtonReleased(PSB_R2))
          {
                   Serial.println("right arm off");
                   digitalWrite(ar1,LOW);
                   digitalWrite(ar2,HIGH);
                   
          }
          
          //left arm up
          if(ps2x.ButtonPressed(PSB_L1))
          {

            Serial.println("left arm up");

                   digitalWrite(al1,HIGH);
                   digitalWrite(al2,HIGH);
                   
          }
            if(ps2x.ButtonReleased(PSB_L1))
          {

            Serial.println("left arm Stop");

                   digitalWrite(al1,LOW);
                   digitalWrite(al2,HIGH);
                   
          }
          
          //left arm down
          if(ps2x.ButtonPressed(PSB_L2))
          {
                 Serial.println("left arm down");

                   digitalWrite(al1,LOW);
                   digitalWrite(al2,LOW);
                   
          }
          
            if(ps2x.ButtonReleased(PSB_L2))
          {
                 Serial.println("left arm stop");

                   digitalWrite(al1,HIGH);
                   digitalWrite(al2,LOW);
                   
          }
          
           //middle arm up
          if(ps2x.Analog(PSS_LY)<100)
          {
                                      Serial.println("middle arm up");

                   digitalWrite(am1,HIGH);
                   digitalWrite(am2,HIGH);
                   flagma=true;
                   
          }
        
          
          //middle arm down
          else if(ps2x.Analog(PSS_LY)>150)
          {
                                      Serial.println("middle arm down");

                   digitalWrite(am1,LOW);
                   digitalWrite(am2,LOW);
                  flagma=true;

          }
          //middle arm stop
           else if(ps2x.Analog(PSS_LY)==123 && flagma)
          {
                                      Serial.println("middle arm Stop");

                   digitalWrite(am1,HIGH);
                   digitalWrite(am2,LOW);
                   flagma=false;
                   
          }
          
          
          //extension ++
          if(ps2x.Button(PSB_PAD_UP))
          {
                     Serial.println("extension arm forward");
                   digitalWrite(ext1,HIGH);
                   digitalWrite(ext2,HIGH);
                                      flagex=true;

            
          }
          
          //extension --
          else if(ps2x.Button(PSB_PAD_DOWN))
          {
                Serial.println("extension arm backward");

                   digitalWrite(ext1,LOW);
                   digitalWrite(ext2,LOW); 
              flagex=true;

            
          }
          else if(ps2x.Analog(PSB_PAD_UP)==0 && ps2x.Analog(PSB_PAD_DOWN)==0 && flagex)
          {
             Serial.println("extension arm stop");

                   digitalWrite(ext1,HIGH);
                   digitalWrite(ext2,LOW); 
                   flagex=false;
          }
          
          
          //
          //
          //gripper control
          //
          //right gripper
           
      if(ps2x.ButtonReleased(PSB_RED))
          {
                     Serial.println("Gripper switched");
                    digitalWrite(ar1,LOW);
                   digitalWrite(ar2,LOW);
          }
          
          //left gripper
         if(ps2x.ButtonReleased(PSB_PINK))
        {
                     Serial.println("Gripper switched");
                    digitalWrite(ar1,HIGH);
                   digitalWrite(ar2,HIGH);
          }
         
          //middle gripper            
          if(ps2x.ButtonReleased(PSB_GREEN))
          {
                                 Serial.println("Gripper switched");

                    middle=!middle;
                    digitalWrite(mg2,middle);
                    
          }
          
          
          
          
          
          delay(100);
          
          digitalWrite(ma1,LOW);
          digitalWrite(ma2,LOW);
          
          digitalWrite(mb1,LOW);
          digitalWrite(mb2,LOW);
          
          digitalWrite(mc1,LOW);
          digitalWrite(mc2,LOW);
          
          digitalWrite(md1,LOW);
          digitalWrite(md2,LOW);
         
         /* digitalWrite(ar1,LOW);
          digitalWrite(ar2,LOW);
          
          digitalWrite(al1,LOW);
          digitalWrite(al2,LOW);
          
          digitalWrite(am1,LOW);
          digitalWrite(am2,LOW);
          
          digitalWrite(ext1,LOW);
          digitalWrite(ext2,LOW);*/
          
}
                    
                    
                    
                    
                    
