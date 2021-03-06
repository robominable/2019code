#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPoten,       sensorPotentiometer)
#pragma config(Sensor, in2,    RarmPoten,      sensorPotentiometer)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           FLWheel,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LArm,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           BLWheel,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LBLift,        tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port6,           RBLift,        tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port7,           BRWheel,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           RArm,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           FRWheel,       tmotorVex393_MC29, openLoop, reversed)
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
int armPotenVal = 4095;
int armPotenTarget = 4095;

int RarmPotenVal = 0;
int RarmPotenTarget = 0;

int liftPotenVal = 0;
int liftPotenTarget = 0;

int RliftPotenVal = 0;

float KpArm = 0.000002;
float KiArm = 0;
float KdArm = 0.2;

float KpRArm = 0.000002;
float KiRArm = 0;
float KdRArm = 0.2;

float KpLift = 0.000000000002;
float KiLift = 0;
float KdLift = 1; //2

int mtrpowerArm = 0;
int mtrpowerRArm = 0;
int mtrpowerLift = 0;
int mtrpowerRLift = 0;

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;
}

task autonomous()
{

}

task usercontrol()
{
	//startTask(gripControl);
	//int rev = 127;

	//*********************************************************************************************************

	int creep = 25;

	//Arm PID Variables
	//***********************************************************************
	int waitTime = 1;

	float TpArm = 0; //TUNABLE: [Starting] Power of right launcher
	float errorArm = 0; //Error of right launcher

	float iArm = 0; //Integral of right launcher

	float dArm = 0; //Derivative of right launcher
	float errorArmPrevious = 0;

	float editArm = 0; //Edit: How much to change right launch speed

	//*********************************************************************8
	float TpRArm = 0; //TUNABLE: [Starting] Power of right launcher
	float errorRArm = 0; //Error of right launcher

	float iRArm = 0; //Integral of right launcher

	float dRArm = 0; //Derivative of right launcher
	float errorRArmPrevious = 0;

	float editRArm = 0; //Edit: How much to change right launch speed

	//*****************************************************************************8

	//Lift PID Variables
	float TpLift = 0; //TUNABLE: [Starting] Power of right launcher
	float errorLift = 0; //Error of right launcher

	float iLift = 0; //Integral of right launcher

	float dLift = 0; //Derivative of right launcher
	float errorLiftPrevious = 0;

	float editLift = 0; //Edit: How much to change right launch speed

	nMotorEncoder[LBLift] = 0;

	//*****************************************************************************8

	//RLift PID Variables
	float TpRLift = 0; //TUNABLE: [Starting] Power of right launcher
	float errorRLift = 0; //Error of right launcher

	float iRLift = 0; //Integral of right launcher

	float dRLift = 0; //Derivative of right launcher
	float errorRLiftPrevious = 0;

	float editRLift = 0; //Edit: How much to change right launch speed

	nMotorEncoder[RBLift] = 0;

	while (true)
	{
		wait1Msec(waitTime);

		//Arm PID ****************************************************************************************************

		errorArm = ( armPotenTarget - SensorValue[armPoten] ); // Error = Target - Observed

		if ((errorArm > 0 && errorArmPrevious < 0) || (errorArm < 0 && errorArmPrevious > 0) || (errorArm == 0))
		{
			iArm = 0;
		}

		if (abs(errorArm)>5)
		{
			playImmediateTone(600,5);
		}
		iArm = iArm + errorArm; // Integral = Integral + Error

		dArm = errorArm - errorArmPrevious; // Derivative = Error - PreviousError

		errorArmPrevious = errorArm;

		editArm = KpArm * errorArm + KiArm * iArm + KdArm * dArm; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		//if  ((TpRLaunch + editRightLaunch) > 0)
		//{
			motor[LArm] = TpArm + editArm; // MotorPower = PreviousMotorPower + Edit
			TpArm += editArm; // MotorPower = PreviousMotorPower + Edit
		//}

		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		armPotenVal = SensorValue(armPoten);
		mtrpowerArm = motor[LArm];

		//RArm PID ******************************************************************************************************

		errorRArm = ( RarmPotenTarget - SensorValue(RarmPoten) ); // Error = Target - Observed

		if ((errorRArm > 0 && errorRArmPrevious < 0) || (errorRArm < 0 && errorRArmPrevious > 0) || (errorRArm == 0))
		{
			iRArm = 0;
		}

		if (abs(errorRArm)>5)
		{
			playImmediateTone(600,5);
		}
		iRArm = iRArm + errorRArm; // Integral = Integral + Error

		dRArm = errorRArm - errorRArmPrevious; // Derivative = Error - PreviousError

		errorRArmPrevious = errorRArm;

		editRArm = KpRArm * errorRArm + KiRArm * iRArm + KdRArm * dRArm; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		//if  ((TpRLaunch + editRightLaunch) > 0)
		//{
			motor[RArm] = TpRArm + editRArm; // MotorPower = PreviousMotorPower + Edit
			TpRArm += editRArm; // MotorPower = PreviousMotorPower + Edit
		//}

		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		RarmPotenVal = SensorValue(RarmPoten);
		mtrpowerRArm = motor[RArm];

		//Lift PID ***************************************************************************************************

		errorLift = ( liftPotenTarget - nMotorEncoder[LBLift] ); // Error = Target - Observed

		if ((errorLift > 0 && errorLiftPrevious < 0) || (errorLift < 0 && errorLiftPrevious > 0) || (errorLift == 0))
		{
			iLift = 0;
		}

		if (abs(errorLift)>5)
		{
			playImmediateTone(800,5);
		}
		iLift = iLift + errorLift; // Integral = Integral + Error

		dLift = errorLift - errorLiftPrevious; // Derivative = Error - PreviousError

		errorLiftPrevious = errorLift;

		editLift = KpLift * errorLift + KiLift * iLift + KdLift * dLift; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		if  ((TpLift + editLift) <= -20)
		{
			motor[LBLift] = -20;
			TpLift = TpLift + editLift;
		}
		else
		{
			motor[LBLift] = TpLift + editLift; // MotorPower = PreviousMotorPower + Edit
			TpLift = TpLift + editLift; // MotorPower = PreviousMotorPower + Edit
		}

		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		liftPotenVal = nMotorEncoder[LBLift];
		mtrpowerLift = motor[LBLift];

		//RLift PID ***************************************************************************************************

		errorRLift = ( liftPotenTarget - nMotorEncoder[RBLift] ); // Error = Target - Observed

		if ((errorRLift > 0 && errorRLiftPrevious < 0) || (errorRLift < 0 && errorRLiftPrevious > 0) || (errorRLift == 0))
		{
			iRLift = 0;
		}

		if (abs(errorRLift)>5)
		{
			playImmediateTone(800,5);
		}
		iRLift = iRLift + errorRLift; // Integral = Integral + Error

		dRLift = errorRLift - errorRLiftPrevious; // Derivative = Error - PreviousError

		errorRLiftPrevious = errorRLift;

		editRLift = KpLift * errorRLift + KiLift * iRLift + KdLift * dRLift; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		if  ((TpRLift + editRLift) <= -20)
		{
			motor[RBLift] = -20;
			TpRLift = TpRLift + editRLift;
		}
		else
		{
			motor[RBLift] = TpRLift + editRLift; // MotorPower = PreviousMotorPower + Edit
			TpRLift = TpRLift + editRLift; // MotorPower = PreviousMotorPower + Edit
		}

		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		RliftPotenVal = nMotorEncoder[RBLift];
		mtrpowerRLift = motor[RBLift];

		//*Driver Controls ************************************************************************************************

		//Set Target Arm Position
		if (vexRT[Btn7L]) { armPotenTarget = 993; RarmPotenTarget = 2904; } //closed
		else if (vexRT[Btn7U]) { armPotenTarget = 2795; RarmPotenTarget = 1160; } //middle
		else if (vexRT[Btn7R]) { armPotenTarget = 4095; RarmPotenTarget = 0; } //start


		//Set Target Lift Position
		if (vexRT[Btn8L]) { liftPotenTarget = 0; } //full down 	poten4095
		else if (vexRT[Btn8U]) { liftPotenTarget = 100; } //down 	poten2978
		else if (vexRT[Btn8R]) { liftPotenTarget = 950; } //up   	poten1528

		//Drive Wheels
		if ((vexRT[Ch3] < creep) && (vexRT[Ch3] >-creep) && (vexRT[Ch4] < creep) && (vexRT[Ch4] >-creep)){motor[FLWheel] = 0;} else {motor[FLWheel] = vexRT[Ch3] + vexRT[Ch4]; }
		if ((vexRT[Ch3] < creep) && (vexRT[Ch3] >-creep) && (vexRT[Ch1] < creep) && (vexRT[Ch1] >-creep)){motor[BLWheel] = 0;} else {motor[BLWheel] = vexRT[Ch3] - vexRT[Ch1]; }
		if ((vexRT[Ch2] < creep) && (vexRT[Ch2] >-creep) && (vexRT[Ch4] < creep) && (vexRT[Ch4] >-creep)){motor[FRWheel] = 0;} else {motor[FRWheel] = vexRT[Ch2] - vexRT[Ch4]; }
		if ((vexRT[Ch2] < creep) && (vexRT[Ch2] >-creep) && (vexRT[Ch1] < creep) && (vexRT[Ch1] >-creep)){motor[BRWheel] = 0;} else {motor[BRWheel] = vexRT[Ch2] + vexRT[Ch1]; }
		//Disable Lift Encoder
		if (vexRT[Btn6U]) { nMotorEncoder[RBLift] = 0; liftPotenTarget = 0; motor[RBLift] = 0;}
	}
}
