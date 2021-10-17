/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// RightMotor           motor         10              
// LeftMotor            motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
color teamColor=blue;
bool pickedColor=false;

void doNothing()
{

}

void mySetColorUp()
{
  if (teamColor == red) teamColor=blue;
  else teamColor=red;
}

void myPickColor()
{ 
  pickedColor=true;
}

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Choose Color (up) - A when done");
  teamColor=red;

  while (!pickedColor)
  {
    Controller1.ButtonUp.pressed(mySetColorUp);
    Controller1.ButtonA.pressed(myPickColor);

    Brain.Screen.setPenColor(teamColor);
    Brain.Screen.drawCircle(240,125,110);
    Brain.Screen.drawCircle(180,100, 25);
    Brain.Screen.drawCircle(300,100, 25);
    Brain.Screen.drawCircle(240,180, 20);
    wait(25, msec);
  }

  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Done                  ");
  
  Controller1.ButtonUp.pressed( doNothing);
  Controller1.ButtonA.pressed( doNothing);
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  int i;
  int leftVel=10, rightVel=10;
  Brain.Screen.clearScreen();

  if ( teamColor == blue)
    leftVel = 20;
  else
    rightVel = 20;

  for (i=0; i<10; i++)
  {
    LeftMotor.setVelocity(leftVel, percent);
    RightMotor.setVelocity(rightVel, percent);
    LeftMotor.spin(forward);
    RightMotor.spin(forward);
    wait(2, seconds);
    LeftMotor.stop();
    RightMotor.stop();
    wait(1, seconds);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
   // Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;
  Brain.Screen.clearScreen();

  while (true) {
    // Get the velocity percentage of the left motor. (Axis3)
    int leftMotorSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int rightMotorSpeed = Controller1.Axis2.position();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      LeftMotor.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      LeftMotor.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      RightMotor.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      RightMotor.setVelocity(rightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    LeftMotor.spin(forward);
    RightMotor.spin(forward);

    Brain.Screen.drawCircle(100,100,leftMotorSpeed);
    Brain.Screen.drawCircle(300,100,rightMotorSpeed);
    wait(25, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
