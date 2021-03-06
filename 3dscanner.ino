//////////////////////////////////////////////////////////////////////
//              3D Scanner motorcontrol Demo                        //
//                                                                  //
//              you need:                                           //
//              4 Stepper                                           //
//              3 or 4 Pololu A4988 or compatible Motordrivers      //
//              1 CNC Shield                                        //
//              1 Arduino Uno or better                             //
//                                                                  //
//              connect the bridge between X and a axis to          //
//              mirror the x to the a axis                          //
//              x and a axis are set tho half step (camera height)  //
//              y is set to 1/16 step              (camera tilt)    //
//              z is set to 1/16 step              (turntable)      //
//                                                                  //
//              more infos: https://github.com/ronbal/3dScanner     //
//              contact: ronny@ronbal.de                            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include <AccelStepper.h>   //includes the Accelstepper Library / fügt die library ein

#define motor_enable_pin 8  // total Enable pin on CNC Shield / aktiviert die Motor Treiber vom shield
    
// Define a stepper and the pins it will use / die pins für die Motoren definieren
AccelStepper stepper(AccelStepper::DRIVER, 2, 5); // Stepper one an two connected to X and A axis for the high / der erste  und zweite Motor werden an die x und a Achse des Shields angeschlossen
AccelStepper camera(AccelStepper::DRIVER, 3, 6); // Stepper three for Camera tilt connected to y axis / der dritte Motor ist für den Kamerawinkel
AccelStepper table(AccelStepper::DRIVER, 4, 7); // Stepper four turntable connectedt to Z axis / Motor 4 ist für den Drehteller


void setup()
{  


   pinMode(motor_enable_pin    , OUTPUT);             //sets the enable pin to output / den enable pin als Ausgang deklarieren
   digitalWrite(motor_enable_pin    , LOW);           // set the motors senabled / die enable bin auf low setzen damit sind die Motoren aktiv 
  

  stepper.setMaxSpeed(1000);                          //set Motorspeed for x axis to 1000 Steps per second / maximaLe motorgemotor Geschwindigkeit auf 1000 Steps pro Sekunde setzen für die x und a achse
  stepper.setAcceleration(100);                       // sets the desired acceleration in steps per second per second / Beschleunigung für die X / A Achse auf 100 Steps pro Sekunde setzen
  
   table.setMaxSpeed(20000);                          // turntable max Speed / Dreheller max speed
  table.setAcceleration(1000);                        // turntable acceleration / Drehteile beschleunigung
 
   camera.setMaxSpeed(1000);                          // camera tilt max speed / Kamerawinkel Geschwindigkeit 
  camera.setAcceleration(1000);                       // camera tilt acceleration / Kamerawinkel beschleunigung
  
  camera.moveTo(700);                                 // move the camera tilt 700 steps forwardto position 700 thats is on my setup 0 degree
 cameraangle();                                       // calls the subroutine to perform the movement
 
  camera.setMaxSpeed(1000);                           // slow down the camera tilt speed
 camera.setAcceleration(100);                         // slow down the camera tilt speed
 
 
}

void loop()
{
/////////////////////////////////////////////////////////////////////////////////////////////  
// drive the camera down and tilt the camara up to shoot from a low position uppwards      //
/////////////////////////////////////////////////////////////////////////////////////////////
 stepper.moveTo(-10000);                              // move the camera height 10000 Steps down to position -10000
 cameraheight();                                      // calls the subroutine to perform the movement for x axis
  camera.moveTo(900);                                 // tilt the camera up 200 Steps to position 900
   cameraangle();                                     // calls the subroutine to perform the movement for y axis
    tableturn();                                      // calls the subroutine to start the turntable

/////////////////////////////////////////////////////////////////////////////////////////////  
// drive the camera up and tilt the camara straight ahead to shoot from front              //
/////////////////////////////////////////////////////////////////////////////////////////////
    stepper.moveTo(10000);                            // move camera height  20000 steps up to position 10000 
 cameraheight();                                      // calls the subroutine to perform the movement for x axis
   camera.moveTo(700);                                // tilt the camera down -200 Steps to position 700
   cameraangle();                                     // calls the subroutine to perform the movement for y axis
   tableturn();                                       // calls the subroutine to start the turntable

/////////////////////////////////////////////////////////////////////////////////////////////  
// drive the camera up and tilt the camara down to shoot from a heigh position             //
/////////////////////////////////////////////////////////////////////////////////////////////
   stepper.moveTo(20000);                            // move camera height  10000 steps up to positin 20000
 cameraheight();                                     // calls the subroutine to perform the movement for x axis
camera.moveTo(500);                                  // tilt the camera down -200 Steps to position 500
 cameraangle();                                      // calls the subroutine to perform the movement for y axis
 tableturn();                                        // calls the subroutine to start the turntable




/////////////////////////////////////////////////////////////////////////////////////////////  
// got to start position                                                                   //
/////////////////////////////////////////////////////////////////////////////////////////////
 stepper.moveTo(0);                                 // move camera height  20000 steps down to position 0

 cameraheight();                                    // calls the subroutine to perform the movement for x axis
  camera.moveTo(700);                               // tilt the camera to position 700
   cameraangle();                                   // calls the subroutine to start the turntable

}


/////////////////////////////////////////////////////////////////////////////////////////////  
// Subroutines
/////////////////////////////////////////////////////////////////////////////////////////////
 
void cameraangle()                                                 //camera tilt subroutine
{
  while(camera.distanceToGo() != 0 || table.distanceToGo() !=0){  //while the motor doesnt reached the position
    camera.run();                                                 // move to the tilt to goal position
    stepper.run();                                                // move to the height to goal position
    
   }
   
    
}

void tableturn()                                                 //turntable move soubroutine
{

  int x = 0;                                                     // set the counter to 0
  while(x < 32){                                                 // while the counter is not 32 perform the loop
    
    table.moveTo(table.currentPosition()+100);                   // add 100 Steps to the current postion of the Stepper for the turntable
    while(table.distanceToGo() !=0){                             //while the motor doesnt reached the position
    table.run();}                                                // turn the table
    
    x=x+1;                                                       // add 1 to the counter
    shoot();                                                     // calls your shoot subroutine
    }
   
    
}

void cameraheight()                                             // camera height subroutine
{
  while(stepper.distanceToGo() != 0){                           //while the motor doesnt reached the position
    stepper.run();}                                             // move the height to the goal position
    
}


void shoot()
{
  //your camera shoot code here
}

