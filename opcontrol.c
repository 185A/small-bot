/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

 void driveSet(int right, int left);
 void driveOP();
 void descorer();
 void catapult();


 const unsigned int TrueSpeed[128] =
 {
   0,  0,  0,  0,  0,  0,  0,  19,  19, 20,
   20, 21, 21, 21, 22, 22, 22, 23, 24, 24,
  25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
  28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
  33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
  37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
  41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
  46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
  52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
  61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
  71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
  80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
  88, 89, 89, 90, 90,127,127,127
 };

void driveSet(int right, int left)
{
	motorSet(2,right);
	motorSet(3,left);
	motorSet(4,right);
	motorSet(7,left);
	motorSet(8,right);
	motorSet(9,left);
}

void driveOP()
{
	static int jl = 0, jr = 0;
	const int slew = 18;
	int joyleft = joystickGetAnalog(1,3);
	int joyright = joystickGetAnalog(1,2);
	int jlset, jrset;

	if(joyleft > jl + slew)
	{
		jl += slew;
	}
	else if(joyleft < jl - slew)
	{
		jl -= slew;
	}
	else if(joyleft < jl || joyleft >= jl)
	{
		jl = joyleft;
	}

	if(joyright > jr + slew)
	{
		jr += slew;
	}
	else if(joyright < jr - slew)
	{
		jr -= slew;
	}
	else if(joyright < jr || joyright >= jr)
	{
		jr = joyright;
	}

	if(jl < 0)
	{
		jlset = -1 * TrueSpeed[-1 * jl];
	}
	else
	{
		jlset = TrueSpeed[jl];
	}
	if(jr < 0)
	{
		jrset = -1 * TrueSpeed[-1 * jr];
	}
	else
	{
		jrset = TrueSpeed[jr];
	}

	driveSet(jlset,jrset);
}

void descorer()
{

int btn6u = joystickGetDigital(1,6,JOY_UP);
int btn6d = joystickGetDigital(1,6,JOY_DOWN);

if(btn6d == 1)
{
	motorSet(1,127);
}
else if(btn6u == 1)
{
	motorSet(1,-127);
}
else
{
	motorSet(1,0);
}

}

void catapult()
{



}












void operatorControl() {
	while (1) {
		delay(20);
	}
}
