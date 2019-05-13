#pragma config(Sensor, in1,    RarmPoten,      sensorPotentiometer)
#pragma config(Sensor, in2,    armPoten,       sensorNone)
#pragma config(Sensor, in7,    LiftPoten,      sensorPotentiometer)
#pragma config(Sensor, dgtl9,  jump9,          sensorDigitalIn)
#pragma config(Motor,  port1,           BRWheel,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FRWheel,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RArm,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RBLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           ALift,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           BLWheel,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LBLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LArm,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           FLWheel,       tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)0
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//Arm PID************************************************************************************
	bool autoArm = false;

	bool freezeArm = false;

	void resetArmPID();

	int waitTimeUsercontrol = 1;

	float TpArm = 0; //TUNABLE: [Starting] Power of right launcher
	float errorArm = 0; //Error of right launcher

	float iArm = 0; //Integral of right launcher

	float dArm = 0; //Derivative of right launcher
	float errorArmPrevious = 0;

	float editArm = 0; //Edit: How much to change right launch speed

	int armPotenVal = 4040;
	int armPotenTarget = 4040;

	//Lift PID**************************************************************************************

	bool autoLift = false;
	bool autoLiftPrimed = false;

	bool freezeLift = false;
	bool blockLiftPID = false;

	void resetLiftPID();

	float TpLift = 0; //TUNABLE: [Starting] Power of right launcher
	float errorLift = 0; //Error of right launcher

	float iLift = 0; //Integral of right launcher

	float dLift = 0; //Derivative of right launcher
	float errorLiftPrevious = 0;

	float editLift = 0; //Edit: How much to change right launch speed

	bool IgnoreLiftFloor = true;

	int liftPotenVal = 550;
	int liftPotenTarget = 550;

	int LBLiftVal = 0;

//Drive Vars
void driveCheck();
int driveEndTime = 1000000;

int FLTarget = 0;
int BLTarget = 0;
int FRTarget = 0;
int BRTarget = 0;

float FLmod = 1.27;//1.08;
float BLmod = 1.16;//1.19;
float FRmod = 1.14;//0.85;
float BRmod = 1.13;

void setDriveMotors();

//Auton Variables*******************************************************************************
int time = 0;
int waitDrive = 1000000;

float KpArm =  0.00009;//0.00003
float KiArm =  0;//.000000001;
float KdArm =  0.13; //0.08

float KpLift =  -0.0004;
float KiLift =  -0;//-0.0000000000001;
float KdLift =  -0.24; //2

int mtrpowerArm = 0;
int mtrpowerLift = 0;

//Prototyped Auton Functions
void stopWheels();
void moveForward(int target, int waitTime);
void moveBackward(int target, int waitTime);
void strafeLeft(int target, int waitTime);
void strafeRight(int target, int waitTime);
void rotateLeft(int target, int waitTime);
void rotateRight(int target, int waitTime);
void armPosition ();
void liftPosition ();


void pre_auton()//**************************************************************************************
{
	slaveMotor(ALift, LBLift);
	slaveMotor(RBLift, LBLift);
	slaveMotor(RArm, LArm);
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;
	autoArm = true;
	autoLift = true;
	blockLiftPID = false;
	time = 0;
}

task autonomous()//*******************************************************************************************8
{/*
	autoLift = true;
	resetLiftPID();

		drive:
		void moveForward(target);//int waitTime);
		void moveBackward();//int waitTime);
		void strafeLeft();//int waitTime);
		void strafeRight();//int waitTime);
		void rotateLeft();//int waitTime);
		void rotateRight();//int waitTime);

		armPositions:
		{ RarmPotenTarget = 1352; armPotenTarget = 2662; } //closed //2870, 2745
			else if (vexRT[Btn8L]) { RarmPotenTarget = 1502; armPotenTarget = 2359; } //Closed V
			else if (vexRT[Btn8R]) { RarmPotenTarget = 2102; armPotenTarget = 1916; } //Open V
			else if (vexRT[Btn8D]) { RarmPotenTarget = 2898; armPotenTarget = 1162; } //Straight

		liftPositions:
		{ liftPotenTarget = 550; armOpenV = true;} //NEW down	poten4095
		{ liftPotenTarget = 1500;} //NEW middle 	poten2978
		{ liftPotenTarget = 3033; armOpenStraight = true;}

FLmod = 1.27;//1.08;
BLmod = 1.16;//1.19;
FRmod = 0.79;//0.85;
BRmod = 1.13;
		*/

	if (SensorValue(jump9) == 1)
	{
		while (true)
		{
			//LEFT SIDE
			//RUN AT TIME
			if (time == 0)
			{

			}


			//ALWAYS-ON
			liftPosition();
			armPosition();
			driveCheck();

			//TIME COUNTER
			wait1Msec(1);
			time = time + 1;
		}
		}

	else if (SensorValue(jump9) == 0)
	{
		while (true)
		{
			//RIGHT SIDE
			//RUN AT TIME
			if (time == 0)
			{

			}


			//ALWAYS-ON
			liftPosition();
			armPosition();
			driveCheck();

			//TIME COUNTER
			wait1Msec(1);
			time = time + 1;
		}
	}
	autoArm = false;
	autoLift = false;
	blockLiftPID = false;
	time = 0;
	//resetDrive();
}

task usercontrol()//********************************************************************************************8
{
	autoArm = true;
	autoLift = false;
	blockLiftPID = true;
	int creep = 25;

	while (true)
	{
		//*Driver Controls ************************************************************************************************

		//autoArm ON OFF CTRL
		if ( (vexRT[Btn6U] == true) && (vexRT[Btn6D] == true) )
		{
			freezeArm = true;
			autoArm = false;
			resetArmPID();
			if ( (vexRT[Btn8U] == true) && (vexRT[Btn8R] == true) && (vexRT[Btn8L] == false) && (vexRT[Btn8D] == false) )
			{
				autoArm = true;
			}
			if ( (vexRT[Btn8U] == false) && (vexRT[Btn8R] == false) && (vexRT[Btn8L] == true) && (vexRT[Btn8D] == true) )
			{
				autoArm = false;
			}
		}
		else
		{
			freezeArm = false;
		}

		//Auto Arm Control
		if (autoArm == true && freezeArm == false)
		{
			//Set Target Arm Position
			if (vexRT[Btn8U]) { armPotenTarget = 1100; } //closed //2870, 2745
			else if (vexRT[Btn8L]) { armPotenTarget = 1402; } //Closed V
			else if (vexRT[Btn8R]) { armPotenTarget = 2002; } //Open V
			else if (vexRT[Btn8D]) { armPotenTarget = 2798; } //Straight

			//Arm Mini Adjust
			if (vexRT[Btn6U]) {armPotenTarget = armPotenTarget + 2;}
			if (vexRT[Btn6D]) {armPotenTarget = armPotenTarget - 2;}
		}

		//Manual Arm Control
		if (autoArm == false && freezeArm == false)
		{
			motor[LArm] = ((vexRT[Btn6U] - vexRT[Btn6D]) * 127) + ((vexRT[Btn8U] - vexRT[Btn8D]) * 40 );
			motor[RArm] = ((vexRT[Btn6U] - vexRT[Btn6D]) * 127) + ((vexRT[Btn8U] - vexRT[Btn8D]) * 40 );
		}

		armPosition();

		//autoLift ON OFF CTRL && LIFT ENCODER RESET
		if ( (vexRT[Btn5U] == true) && (vexRT[Btn5D] == true) )
		{
			freezeLift = true;
			autoLift = false;
			resetLiftPID();
			if ( (vexRT[Btn7U] == true) && (vexRT[Btn7R] == true) && (vexRT[Btn7L] == false) && (vexRT[Btn7D] == false) )
			{
				autoLift = true;
			}
			if ( (vexRT[Btn7U] == false) && (vexRT[Btn7R] == false) && (vexRT[Btn7L] == true) && (vexRT[Btn7D] == true) )
			{
				autoLift = false;
			}
		}
		else
		{
			freezeLift = false;
		}

		//Auto Lift Control
		if (autoLift == true && freezeLift == false)
		{
			//Set Target Lift Position
			if (vexRT[Btn7D]) { liftPotenTarget = 550; } //down
			else if (vexRT[Btn7L]) {  liftPotenTarget = 1500; } //middle
			else if (vexRT[Btn7U]) {  liftPotenTarget = 3000; } //up

			//Arm Mini Adjust
			if (vexRT[Btn5U]) {liftPotenTarget = liftPotenTarget + 2;}
			if (vexRT[Btn5D]) {liftPotenTarget = liftPotenTarget - 2;}
		}

		//Manual Lift Control
		if (autoLift == false && freezeLift == false)
		{
			motor[LBLift] = ((vexRT[Btn5U] - vexRT[Btn5D]) * 127) + ((vexRT[Btn7U] - vexRT[Btn7D]) * 40 );
		}

		if (autoLift == false && freezeLift == false && SensorValue(LiftPoten) < 430 && IgnoreLiftFloor == false)
		{
			liftPotenTarget = 450;
			autoLiftPrimed = true;
			autoLift = true;
		}

		if (SensorValue(LiftPoten) >= 430 && autoLift == true)
		{
			autoLift = false;
			autoLiftPrimed = false;
			motor[LBLift] = 0;
		}

		liftPosition();

		//Drive Wheels
		if ((vexRT[Ch3] < creep) && (vexRT[Ch3] >-creep) && (vexRT[Ch4] < creep) && (vexRT[Ch4] >-creep)){motor[FLWheel] = 0;} else {motor[FLWheel] = vexRT[Ch3] + vexRT[Ch4]; }
		if ((vexRT[Ch3] < creep) && (vexRT[Ch3] >-creep) && (vexRT[Ch1] < creep) && (vexRT[Ch1] >-creep)){motor[BLWheel] = 0;} else {motor[BLWheel] = vexRT[Ch3] - vexRT[Ch1]; }
		if ((vexRT[Ch2] < creep) && (vexRT[Ch2] >-creep) && (vexRT[Ch4] < creep) && (vexRT[Ch4] >-creep)){motor[FRWheel] = 0;} else {motor[FRWheel] = vexRT[Ch2] - vexRT[Ch4]; }
		if ((vexRT[Ch2] < creep) && (vexRT[Ch2] >-creep) && (vexRT[Ch1] < creep) && (vexRT[Ch1] >-creep)){motor[BRWheel] = 0;} else {motor[BRWheel] = vexRT[Ch2] + vexRT[Ch1]; }

		wait1Msec(waitTimeUsercontrol);
		}
}

//Drive Auton Functions************************************************************************************************

void driveCheck()
{
	if(time < driveEndTime){}
	else{stopWheels();}
}

void setDriveMotors()
{
	motor[FLWheel] = FLTarget * FLmod;
	motor[BLWheel] = BLTarget * BLmod;
	motor[FRWheel] = FRTarget * FRmod;
	motor[BRWheel] = BRTarget * BRmod;
	driveEndTime = time + waitDrive;
}

void stopWheels()
{
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;
}

void resetDrive()
{
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;
}

void moveForward (int target, int waitTime)
{
	FLTarget = target;
	BLTarget = target;
	FRTarget = target;
	BRTarget = target;
	waitDrive = waitTime;
	setDriveMotors();
}

void moveBackward (int target, int waitTime)
{
	FLTarget = -target;
	BLTarget = -target;
	FRTarget = -target;
	BRTarget = -target;
	waitDrive = waitTime;
	setDriveMotors();
}

void strafeLeft (int target, int waitTime)
{
	FLTarget = -target;
	BLTarget = target;
	FRTarget = target;
	BRTarget = -target;
	waitDrive = waitTime;
	setDriveMotors();
}

void strafeRight (int target, int waitTime)
{
	FLTarget = target;
	BLTarget = -target;
	FRTarget = -target;
	BRTarget = target;
	waitDrive = waitTime;
	setDriveMotors();
}

void rotateLeft (int target, int waitTime)
{
	FLTarget = -target;
	BLTarget = -target;
	FRTarget = target;
	BRTarget = target;
	waitDrive = waitTime;
	setDriveMotors();
}

void rotateRight (int target, int waitTime)
{
	FLTarget = target;
	BLTarget = target;
	FRTarget = -target;
	BRTarget = -target;
	waitDrive = waitTime;
	setDriveMotors();
}

void angledStrafe (int target, int angle, int waitTime)
{
	FLTarget = target * (sinDegrees(angle) + cosDegrees(angle));
	BLTarget = target * (sinDegrees(angle) - cosDegrees(angle));
	FRTarget = target * (sinDegrees(angle) - cosDegrees(angle));
	BRTarget = target * (sinDegrees(angle) + cosDegrees(angle));
	waitDrive = waitTime;
	setDriveMotors();
}

//Arm PID************************************************************************************************
void armPosition ()
{
	if (autoArm == true)
		{
		//Arm PID *****************************************

		errorArm = ( armPotenTarget - SensorValue[RarmPoten] ); // Error = Target - Observed

		if ((errorArm > 0 && errorArmPrevious < 0) || (errorArm < 0 && errorArmPrevious > 0) || (errorArm == 0))
		{
			iArm = 0;
		}

		if (abs(errorArm)>5)
		{
			//playImmediateTone(600,5);
		}
		iArm = iArm + errorArm; // Integral = Integral + Error

		dArm = errorArm - errorArmPrevious; // Derivative = Error - PreviousError

		errorArmPrevious = errorArm;

		editArm = KpArm * errorArm + KiArm * iArm + KdArm * dArm; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		//if  (autoArm == true)
		//{
		motor[LArm] = TpArm + editArm; // MotorPower = PreviousMotorPower + Edit
		//}
		TpArm += editArm; // MotorPower = PreviousMotorPower + Edit

		if (TpArm > 128)
		{
			TpArm = 127;
		}

		if (TpArm < -128)
		{
			TpArm = -127;
		}

		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		armPotenVal = SensorValue(armPoten);
		mtrpowerArm = motor[LArm];

	}
}

//Lift PID******************************************************************************************************
void liftPosition ()
{
	//Lift PID ******************************************

	if ((autoLift == true) )//&& (blockLiftPID == false))
	{
		LBLiftVal = SensorValue(LiftPoten); //- LBLiftEncoderOffset;

		errorLift = ( LBLiftVal - liftPotenTarget ); // Error = Target - Observed

		if ((errorLift > 0 && errorLiftPrevious < 0) || (errorLift < 0 && errorLiftPrevious > 0) || (errorLift == 0))
		{
			iLift = 0;
		}

		if (abs(errorLift)>5)
		{
			//playImmediateTone(800,5);
		}
		iLift = iLift + errorLift; // Integral = Integral + Error

		dLift = errorLift - errorLiftPrevious; // Derivative = Error - PreviousError

		errorLiftPrevious = errorLift;

		editLift = KpLift * errorLift + KiLift * iLift + KdLift * dLift; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		/*if  (autoLift == true)
		{
		motor[LBLift] = -20;
		TpLift = TpLift + editLift;
		}
		else*/
		motor[LBLift] = TpLift + editLift; // MotorPower = PreviousMotorPower + Edit

		TpLift = TpLift + editLift; // MotorPower = PreviousMotorPower + Edit

		if (TpLift > 128)
		{
			TpLift = 127;
		}

		if (TpLift < -128)
		{
			TpLift = -127;
		}

		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		liftPotenVal = LBLiftVal;
		mtrpowerLift = motor[LBLift];
	}
}

//Reset Lift******************************************************************************
void resetLiftPID()
{
	motor[LBLift] = 0;
	TpLift = 0; //TUNABLE: [Starting] Power of right launcher
	errorLift = 0; //Error of right launcher

	iLift = 0; //Integral of right launcher

	dLift = 0; //Derivative of right launcher
	errorLiftPrevious = 0;

	editLift = 0; //Edit: How much to change right launch speed

	liftPotenTarget = SensorValue(LiftPoten);
}

void resetArmPID()
{
	motor[RArm] = 0;
	motor[LArm] = 0;
	TpArm = 0; //TUNABLE: [Starting] Power of right launcher
	errorArm = 0; //Error of right launcher

	iArm = 0; //Integral of right launcher

	dArm = 0; //Derivative of right launcher
	errorArmPrevious = 0;

	editArm = 0; //Edit: How much to change right launch speed

	armPotenTarget = SensorValue(armPoten);
}
