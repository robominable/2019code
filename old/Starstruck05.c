#pragma config(Sensor, in1,    armPoten,       sensorPotentiometer)
#pragma config(Motor,  port1,           DL,            tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           UL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           URLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           DRLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           ULLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           DLLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           DR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           URArm,         tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//User Created Tasks
//task gripControl();

//Global Variables
int armPotenVal = 0;
int armPotenTarget = 1877;

float KpArm = 0.000002;
float KiArm = 0;
float KdArm = 0.2;

int mtrpower = 0;

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;
  slaveMotor ( DL, URArm );
  slaveMotor ( UL, URArm );
  slaveMotor ( DR, URArm );
  slaveMotor ( DRLift, URLift );
  slaveMotor ( DLLift, URLift );
  slaveMotor ( ULLift, URLift );
}

task autonomous()
{

}

task usercontrol()
{
	//startTask(gripControl);
	//int rev = 127;

	//*********************************************************************************************************8
	int waitTime = 1;

	float TpRLaunch = 0; //TUNABLE: [Starting] Power of right launcher
	float errorRightLaunch = 0; //Error of right launcher

	float iRightLaunch = 0; //Integral of right launcher

	float dRightLaunch = 0; //Derivative of right launcher
	float errorRightLaunchPrevious = 0;

	float editRightLaunch = 0; //Edit: How much to change right launch speed




	while (true)
	{
		wait1Msec(waitTime);

		errorRightLaunch = ( armPotenTarget - SensorValue(armPoten) ); // Error = Target - Observed

		if ((errorRightLaunch > 0 && errorRightLaunchPrevious < 0) || (errorRightLaunch < 0 && errorRightLaunchPrevious > 0) || (errorRightLaunch == 0))
		{
			iRightLaunch = 0;
		}

		if (abs(errorRightLaunch)>5)
		{
			playImmediateTone(600,5);
		}
		iRightLaunch = iRightLaunch + errorRightLaunch; // Integral = Integral + Error

		dRightLaunch = errorRightLaunch - errorRightLaunchPrevious; // Derivative = Error - PreviousError

		errorRightLaunchPrevious = errorRightLaunch;

		editRightLaunch = KpArm * errorRightLaunch + KiArm * iRightLaunch + KdArm * dRightLaunch; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		//if  ((TpRLaunch + editRightLaunch) > 0)
		//{
			motor[URArm] = TpRLaunch + editRightLaunch; // MotorPower = PreviousMotorPower + Edit
			TpRLaunch = TpRLaunch + editRightLaunch; // MotorPower = PreviousMotorPower + Edit
		//}

			//****************************************************************************************************************
		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		armPotenVal = SensorValue(armPoten);
		mtrpower = motor[URArm];

		//Set Target Arm Position
		if (vexRT[Btn7L]) { armPotenTarget = 250; } //421
		else if (vexRT[Btn7U]) { armPotenTarget = 1877; }
		else if (vexRT[Btn7R]) { armPotenTarget = 3380; }//3465

		//Lift
		motor[URLift] = (vexRT[Btn6U] - vexRT[Btn6D]) * 127;

		/*
		if (abs(armPotenVal - armPotenTarget) < 10)
		{ motor[URArm] = 0; }
		else if (armPotenVal > armPotenTarget)
		{ motor[URArm] = -20; }
		else if (armPotenVal < armPotenTarget)
		{ motor[URArm] = 20; }*/

		//Independent Arm Motor Control
	  /*motor[URArm] = vexRT[Btn6U] * rev + vexRT[Btn6D] * -rev;
	  motor[DR] = vexRT[Btn6U] * rev + vexRT[Btn6D] * -rev;
	  motor[UL] = vexRT[Btn6U] * rev + vexRT[Btn6D] * -rev;
	  motor[DL] = vexRT[Btn6U] * rev + vexRT[Btn6D] * -rev;*/
	}
}

/*
task gripControl()
{
	int waitTime = 1;

	float TpRLaunch = 0; //TUNABLE: [Starting] Power of right launcher
	float errorRightLaunch = 0; //Error of right launcher

	float iRightLaunch = 0; //Integral of right launcher

	float dRightLaunch = 0; //Derivative of right launcher
	float errorRightLaunchPrevious = 0;

	float editRightLaunch = 0; //Edit: How much to change right launch speed

	while(true)
	{
		wait1Msec(waitTime);

		errorRightLaunch = ( armPotenTarget - SensorValue(armPotenVal) ); // Error = Target - Observed

		if ((errorRightLaunch > 0 && errorRightLaunchPrevious < 0) || (errorRightLaunch < 0 && errorRightLaunchPrevious > 0) || (errorRightLaunch == 0))
		{
			iRightLaunch = 0;
		}

		if (abs(errorRightLaunch)>5)
		{
			playImmediateTone(600,5);
		}
		iRightLaunch = iRightLaunch + errorRightLaunch; // Integral = Integral + Error

		dRightLaunch = errorRightLaunch - errorRightLaunchPrevious; // Derivative = Error - PreviousError

		errorRightLaunchPrevious = errorRightLaunch;

		editRightLaunch = KpArm * errorRightLaunch + KiArm * iRightLaunch + KdArm * dRightLaunch; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		//if  ((TpRLaunch + editRightLaunch) > 0)
		//{
			motor[URArm] = TpRLaunch + editRightLaunch; // MotorPower = PreviousMotorPower + Edit
			TpRLaunch = TpRLaunch + editRightLaunch; // MotorPower = PreviousMotorPower + Edit
		//}
	}
}*/
