/*
 Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
 It supports up to four controllers wirelessly
 For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <Servo.h>

USB Usb;
XBOXRECV Xbox(&Usb);

#define MDp1 26      //motor control pins
#define MDp2 27
#define MMp1 28
#define MMp2 29
#define Flipper1 34   //strike motor pins
#define Flipper2 35
#define Flipper3 36
#define Flipper4 37    

 int Xaxisp=9500;
 int Yaxisp=9500;
 int Xaxisn=-9500;
 int Yaxisn=-9500;

//Servo servo1;
//Servo servo2;

 

void setup() {
  pinMode(MDp1, OUTPUT); //Orange
  pinMode(MDp2, OUTPUT); //Blue
  pinMode(MMp1, OUTPUT); //Red
  pinMode(MMp2, OUTPUT); //Black

  pinMode(Flipper1, OUTPUT); //Orange
  pinMode(Flipper2, OUTPUT); //Yellow
  pinMode(Flipper3, OUTPUT); //Orange
  pinMode(Flipper4, OUTPUT); //Yellow
  
  //servo1.attach(26);  //the pin for the servo control, and range if desired
 // servo1.write(1); //set initial servo position if desired
  //servo2.attach(27);  //the pin for the servo control, and range if desired
 // servo2.write(1); //set initial servo position if desired
  int n=0;
  
  
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}
void loop() {
 
int autogear=5;
  
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i)) {
          Serial.print("L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\tR2: ");
          Serial.println(Xbox.getButtonPress(R2, i));
          Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);

          autogear=Xbox.getButtonPress(R2, i)+1;
           Serial.print("\tAutogear: ");
           Serial.println(autogear);
        }

          digitalWrite(MDp1, LOW); // set all LOW
          digitalWrite(MDp2, LOW);
          digitalWrite(MMp1, LOW);
          digitalWrite(MMp2, LOW);

          digitalWrite(Flipper1, LOW);   
          digitalWrite(Flipper2, LOW);  
          digitalWrite(Flipper3, LOW);   
          digitalWrite(Flipper4, LOW);   

          int Xget=0;
          int Yget=0;

         

         
          
           if (Xbox.getAnalogHat(LeftHatX, i) > Xaxisp || Xbox.getAnalogHat(LeftHatX, i) < Xaxisn)
           {
            Xget=Xbox.getAnalogHat(LeftHatX, i);
            }
          
           if (Xbox.getAnalogHat(LeftHatY, i) > Yaxisp || Xbox.getAnalogHat(LeftHatY, i) < Yaxisn)
           {
            Yget=Xbox.getAnalogHat(LeftHatY, i);
           }
          
          
          
          



        if (Xbox.getAnalogHat(LeftHatX, i) > Xaxisp || Xbox.getAnalogHat(LeftHatX, i) < Xaxisn || Xbox.getAnalogHat(LeftHatY, i) > Yaxisp || Xbox.getAnalogHat(LeftHatY, i) < Yaxisn || Xbox.getAnalogHat(RightHatX, i) > Xaxisp || Xbox.getAnalogHat(RightHatX, i) < Xaxisn || Xbox.getAnalogHat(RightHatY, i) > Yaxisp || Xbox.getAnalogHat(RightHatY, i) < Yaxisn) {
         ////////// LEFT ANALOG //////////
         
          // FORWARD RIGHT FAST
          if (Xget > Xaxisp && Yget ==0) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xget);
            Serial.print("\t");
            digitalWrite(MMp1,LOW );   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, HIGH );    // turn the LED off by making the voltage LOW
            digitalWrite(MDp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, HIGH);    // turn the LED off by making the voltage LOW
            delay(autogear);                       // wait for a second
            digitalWrite(MDp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW);    // turn the LED off by making the voltage LOW
            digitalWrite(MMp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, LOW);    // turn the LED off by making the voltage LOW
           
          }

           // FORWARD RIGHT SLOW 
          if (Xget > Xaxisp && Yget > Yaxisp ) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xget);
            Serial.print(Yget);
            Serial.print("\t");
            digitalWrite(MMp1,LOW );   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, HIGH );    // turn the LED off by making the voltage LOW
             digitalWrite(MDp1,LOW );   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW);    // turn the LED off by making the voltage LOW
            delay(autogear);                       // wait for a second
            digitalWrite(MDp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW);    // turn the LED off by making the voltage LOW
            digitalWrite(MMp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, LOW);    // turn the LED off by making the voltage LOW
           
          }
          
        // FORWARD LEFT SLOW
       if (Xget < Xaxisn && Yget > Yaxisp) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xget);
            Serial.print("\t");
             digitalWrite(MDp1,HIGH );   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW );    // turn the LED off by making the voltage LOW
            digitalWrite(MMp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, LOW);    // turn the LED off by making the voltage LOW
            delay(autogear);                       // wait for a second
            digitalWrite(MDp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW);    // turn the LED off by making the voltage LOW
            digitalWrite(MMp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, LOW);    // turn the LED off by making the voltage LOW
           
          }

          // FORWARD LEFT FAST
           if (Xget < Xaxisn && Yget==0 ) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xget);
            Serial.print(Yget);
            Serial.print("\t");
            digitalWrite(MMp1,HIGH );   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, LOW );    // turn the LED off by making the voltage LOW
             digitalWrite(MDp1,HIGH);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW);    // turn the LED off by making the voltage LOW
            delay(autogear);                       // wait for a second
            digitalWrite(MDp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW);    // turn the LED off by making the voltage LOW
            digitalWrite(MMp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, LOW);    // turn the LED off by making the voltage LOW
           
          }

          // FORWARD 
          if (Yget > Yaxisp && Xget==0 ) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Yget);
            Serial.print("\t");
            digitalWrite(MMp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, HIGH);    // turn the LED off by making the voltage LOW
             digitalWrite(MDp1, HIGH);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2,LOW );    // turn the LED off by making the voltage LOW
            
            delay(autogear);                       // wait for a second
            digitalWrite(MMp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MMp2, LOW);    // turn the LED off by making the voltage LOW
           
                           // wait for a second
            digitalWrite(MDp1, LOW);   // turn the LED on (HIGH is the voltage level)
            digitalWrite(MDp2, LOW);    // turn the LED off by making the voltage LOW



            
          }
          
          // BACK 
           if (Yget < Yaxisn  && Xget==0) {
            Serial.print(F("LeftHatY: "));
            Serial.print(Yget);
            Serial.print("\t");
            digitalWrite(MMp1, HIGH);   // 
            digitalWrite(MMp2, LOW);    // 
            digitalWrite(MDp1,LOW );   // 
            digitalWrite(MDp2, HIGH);    // 
            delay(autogear);                       // wait for autogear
            digitalWrite(MMp1, LOW);   // 
            digitalWrite(MMp2, LOW);    // 
            digitalWrite(MDp1, LOW);   // 
            digitalWrite(MDp2, LOW);    // 
            
          }

        

           // BACK RIGHT SLOW 
          if (Xget > Xaxisp && Yget < Yaxisn ) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xget);
            Serial.print(Yget);
            Serial.print("\t");
            digitalWrite(MMp1,LOW );   // 
            digitalWrite(MMp2, LOW );    // 
             digitalWrite(MDp1,LOW );   // 
            digitalWrite(MDp2, HIGH);    // 
            delay(autogear);                       // wait for autogear
            digitalWrite(MDp1, LOW);   // 
            digitalWrite(MDp2, LOW);    // 
            digitalWrite(MMp1, LOW);   // 
            digitalWrite(MMp2, LOW);    // 
           
          }
          
        // BACK LEFT SLOW
       if (Xget < Xaxisn && Yget < Yaxisn) {
            Serial.print(F("LeftHatX: "));
            Serial.print(Xget);
            Serial.print("\t");
             digitalWrite(MDp1, LOW);   // 
            digitalWrite(MDp2, LOW );    // 
            digitalWrite(MMp1,HIGH );   // 
            digitalWrite(MMp2, LOW);    // 
            delay(autogear);                       // wait for autogear
            digitalWrite(MDp1, LOW);   // 
            digitalWrite(MDp2, LOW);    // 
            digitalWrite(MMp1, LOW);   // 
            digitalWrite(MMp2, LOW);    // 
           
          }

         


          digitalWrite(MMp1, LOW);   // 
          digitalWrite(MMp2, LOW);    // 
          digitalWrite(MDp1, LOW);   // 
          digitalWrite(MDp2, LOW);    // 

          digitalWrite(Flipper1, LOW);   // 
          digitalWrite(Flipper2, LOW);    //



          

          ////////// LEFT ANALOG //////////

          ////////// RIGHT ANALOG //////////
         //ROTATE FORWARD
          
         /* if (Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500) {
            Serial.print(F("RightHatX: "));
            Serial.print(Xbox.getAnalogHat(RightHatX, i));
            Serial.print("\t");

             digitalWrite(Flipper1, HIGH);   // 
            digitalWrite(Flipper2, LOW);    // 
     
            digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, LOW);    // 
           
          }*/

            if (Xbox.getAnalogHat(RightHatY, i) > 7500) {
            Serial.print(F("RightHatY: "));
            Serial.print(Xbox.getAnalogHat(RightHatY, i));

            digitalWrite(Flipper1,HIGH);   // 
            digitalWrite(Flipper2, LOW );    // 
     delay(5); 
            digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, LOW);    // 
          }


          

          //ROTATE BACK
          if ( Xbox.getAnalogHat(RightHatY, i) < -7500) {
            Serial.print(F("RightHatY: "));
            Serial.print(Xbox.getAnalogHat(RightHatY, i));

            digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, HIGH);    // 
     delay(5); 
            digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, LOW);    // 
          }



          digitalWrite(Flipper1, LOW);   // 
          digitalWrite(Flipper2, LOW);    //
          digitalWrite(Flipper3, LOW);   // 
          digitalWrite(Flipper4, LOW);    //
          ////////// RIGHT ANALOG //////////


          
          Serial.println();
          
        }

        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
        }
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
        }
        if (Xbox.getButtonClick(LEFT, i)) {
          Xbox.setLedOn(LED3, i);
          Serial.println(F("Left"));
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
        }

        if (Xbox.getButtonClick(START, i)) {
          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
          Serial.println(F("L3"));
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          {Serial.println(F("L1"));
           digitalWrite(Flipper3,HIGH);   // 
            digitalWrite(Flipper4, LOW );    // 
     delay(200);
            digitalWrite(Flipper3, LOW);   // 
            digitalWrite(Flipper4, LOW);    // 
          }
        if (Xbox.getButtonClick(R1, i))
          {Serial.println(F("R1"));          
           digitalWrite(Flipper1,HIGH);   // 
            digitalWrite(Flipper2, LOW );    // 
     delay(200);
            digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, LOW);    // 
          }
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
        }

        if (Xbox.getButtonClick(A, i))
          {Serial.println(F("A"));
            digitalWrite(Flipper1,HIGH);   // 
            digitalWrite(Flipper2, LOW );    // 
     delay(200);
            digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, LOW);    // 
           
           //servo1.attach(26);
          //servo1.write(180);
          //servo1.detach();
           }
        if (Xbox.getButtonClick(B, i))
          {Serial.println(F("B"));
           digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, HIGH);    // 
     delay(200);
            digitalWrite(Flipper1, LOW);   // 
            digitalWrite(Flipper2, LOW);    //
          
          //servo2.attach(27);         // controlling servo with B button when uncommented
          //servo2.write(180);
          //servo2.detach();
          }
        if (Xbox.getButtonClick(X, i))
          {Serial.println(F("X"));
          digitalWrite(Flipper3,HIGH );   // controlling motors with X button
            digitalWrite(Flipper4, LOW);    // 
     delay(200);
            digitalWrite(Flipper3, LOW);   // 
            digitalWrite(Flipper4, LOW);    //
          
          
          }
          
        if (Xbox.getButtonClick(Y, i))
          {Serial.println(F("Y"));
            digitalWrite(Flipper3,LOW );   // controlling motors with Y button
            digitalWrite(Flipper4, HIGH);    // 
     delay(200);
            digitalWrite(Flipper3, LOW);   // 
            digitalWrite(Flipper4, LOW);    //
          
          
          }
      }
    }
  }
}
