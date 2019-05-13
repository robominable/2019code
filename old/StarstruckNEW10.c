#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    RarmPoten,      sensorPotentiometer)
#pragma config(Sensor, in2,    armPoten,       sensorPotentiometer)
#pragma config(Sensor, in8,    LiftPoten,      sensorPotentiometer)
#pragma config(Sensor, dgtl5,  FREncoder,      sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  FLEncoder,      sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  jump9,          sensorDigitalIn)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           BRWheel,       tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port2,           FRWheel,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RArm,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RBLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           ALift,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           BLWheel,       tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port7,           LBLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LArm,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           FLWheel,       tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)0
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//User Created Tasks
//task gripControl();

int driveEncoderPID (int encoderInTarget);
void FRWheelgo();
void FLWheelgo();
void BRWheelgo();
void BLWheelgo();
void resetDrive ();

float errorEncoderPreviousFR = 0;
float errorEncoderPreviousFL = 0;
float errorEncoderPreviousBR = 0;
float errorEncoderPreviousBL = 0;

int FLTarget = 0;
int FRTarget = 0;
int BLTarget = 0;
int BRTarget = 0;

int TpEncoderFL = 0;
int TpEncoderBL = 0;
int TpEncoderFR = 0;
int TpEncoderBR = 0;

int iEncoderFL = 0;
int iEncoderBL = 0;
int iEncoderFR = 0;
int iEncoderBR = 0;

//PID STUFF
//Arm PID Variables
	//***********************************************************************
	int waitTime = 1;

	float TpArm = 0; //TUNABLE: [Starting] Power of right launcher
	float errorArm = 0; //Error of right launcher

	float iArm = 0; //Integral of right launcher

	float dArm = 0; //Derivative of right launcher
	float errorArmPrevious = 0;

	float editArm = 0; //Edit: How much to change right launch speed

	//*********************************************************************
	float TpRArm = 0; //TUNABLE: [Starting] Power of right launcher
	float errorRArm = 0; //Error of right launcher

	float iRArm = 0; //Integral of right launcher

	float dRArm = 0; //Derivative of right launcher
	float errorRArmPrevious = 0;

	float editRArm = 0; //Edit: How much to change right launch speed

	//***************************************************************************

	//Lift PID Variables
	void resetLiftPID();

	float TpLift = 0; //TUNABLE: [Starting] Power of right launcher
	float errorLift = 0; //Error of right launcher

	float iLift = 0; //Integral of right launcher

	float dLift = 0; //Derivative of right launcher
	float errorLiftPrevious = 0;

	float editLift = 0; //Edit: How much to change right launch speed

	bool IgnoreLiftFloor = false;


//Global Variables
int time = 0;

int armPotenVal = 50;
int armPotenTarget = 50;

int RarmPotenVal = 4040;
int RarmPotenTarget = 4040;

int liftPotenVal = 550;
int liftPotenTarget = 550;

float KpArm =  0.00009;//0.00003
float KiArm =  0;//.000000001;
float KdArm =  0.133; //0.08

float KpRArm = 0.00009;
float KiRArm = 0;//.000000001;
float KdRArm = 0.13;

float KpLift =  -0.00002;
float KiLift =  -0;//-0.0000000000001;
float KdLift =  -0.12; //2

float KpEncoder =  0.002;
float KiEncoder =  0;
float KdEncoder =  0.2;

int mtrpowerArm = 0;
int mtrpowerRArm = 0;
int mtrpowerLift = 0;

bool autoArm = false;
bool autoArmPrimed = false;
bool autoLift = false;
bool autoLiftPrimed = false;

bool freezeLift = false;
bool freezeArm = false;

bool safetysignal = false;

//Generic Encoder PID
float TpEncoder = 0; //TUNABLE: [Starting] Power of right launcher
float errorEncoder = 0; //Error of right launcher

float iEncoder = 0; //Integral of right launcher

float dEncoder = 0; //Derivative of right launcher
float errorEncoderPrevious = 0;

float editEncoder = 0; //Edit: How much to change right launch speed

int encoderVal = 50;



int motorPIDout = 0;

bool blockLiftPID = false;

//Prototyped Functions
void stopWheels();
void moveForward(int target);//int waitTime);
void moveBackward(int target);//int waitTime);
void strafeLeft(int target);//int waitTime);
void strafeRight(int target);//int waitTime);
void rotateLeft(int target);//int waitTime);
void rotateRight(int target);//int waitTime);
void armPosition ();
void liftPosition ();

//fake encoder value
int LBLiftVal = 0;

//int LBLiftEncoderOffset = 0;

void pre_auton()
{
	slaveMotor(ALift, LBLift);
	slaveMotor(RBLift, LBLift);
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;
}

task autonomous()
{
	autoArm = true;
	autoLift = true;
	blockLiftPID = false;
	time = 0;
	resetDrive();
	/*
		drive:
		void moveForward(target);//int waitTime);
		void moveBackward();//int waitTime);
		void strafeLeft();//int waitTime);
		void strafeRight();//int waitTime);
		void rotateLeft();//int waitTime);
		void rotateRight();//int waitTime);

		armPositions:
		{ RarmPotenTarget = 2870; armPotenTarget = 2745; } //closed //2870, 2745
			else if (vexRT[Btn8L]) { RarmPotenTarget = 2350; armPotenTarget = 2250; } //Closed V
			else if (vexRT[Btn8R]) { RarmPotenTarget = 1938; armPotenTarget = 1789; } //Open V
			else if (vexRT[Btn8D]) { RarmPotenTarget = 1278; armPotenTarget = 1116; } //Straight

		liftPositions:
		{ liftPotenTarget = 550; armOpenV = true;} //NEW down	poten4095
		{ liftPotenTarget = 1500;} //NEW middle 	poten2978
		{ liftPotenTarget = 3033; armOpenStraight = true;}
		*/

	if (SensorValue(jump9) == 1)
	{
		while (true)
		{
			//LEFT SIDE
			//RUN AT TIME
			if (time == 0)
			{
				moveForward(500);
			}

			if (time == 0)
			{
				 RarmPotenTarget = 1938; armPotenTarget = 1789;
			}

			if (time == 700)
			{
				 RarmPotenTarget = 2870; armPotenTarget = 2745;
				 rotateRight(800);
			}

			if (time == 1700)
			{
				 moveBackward(500);
				 liftPotenTarget = 3033;
			}

			if (time == 3700)
			{
				 RarmPotenTarget = 1278; armPotenTarget = 1116;
				 liftPotenTarget = 500;
			}




			//ALWAYS-ON
			liftPosition();
			armPosition();
			FRWheelgo();
			FLWheelgo();
			BRWheelgo();
			BLWheelgo();

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
				moveForward(1000);
				liftPotenTarget = 2000;
				RarmPotenTarget = 950; armPotenTarget = 900;
			}


			//ALWAYS-ON
			liftPosition();
			armPosition();
			FRWheelgo();
			FLWheelgo();
			BRWheelgo();
			BLWheelgo();

			//TIME COUNTER
			wait1Msec(1);
			time = time + 1;
		}
	}
}

task usercontrol()
{
	autoArm = true;
	autoLift = false;

	int creep = 25;

	blockLiftPID = true;

	while (true)
	{
		wait1Msec(waitTime);

		//*Driver Controls ************************************************************************************************

		//autoArm ON OFF CTRL
		if ( (vexRT[Btn6U] == true) && (vexRT[Btn6D] == true) )
		{
			freezeArm = true;
			autoArm = false;
			if ( (vexRT[Btn8U] == true) && (vexRT[Btn8R] == true) && (vexRT[Btn8L] == false) && (vexRT[Btn8D] == false) )
			{
				autoArmPrimed = true;
			}
			if ( (vexRT[Btn8U] == false) && (vexRT[Btn8R] == false) && (vexRT[Btn8L] == true) && (vexRT[Btn8D] == true) )
			{
				autoArmPrimed = false;
			}
		}
		else
		{
			freezeArm = false;
			if (autoArmPrimed == true) {autoArm = true;}
		}

		//Auto Arm Control
		if (autoArm == true)
		{
			//Set Target Arm Position
			if (vexRT[Btn8U]) { RarmPotenTarget = 1352; armPotenTarget = 2662; } //closed //2870, 2745
			else if (vexRT[Btn8L]) { RarmPotenTarget = 1502; armPotenTarget = 2359; } //Closed V
			else if (vexRT[Btn8R]) { RarmPotenTarget = 2102; armPotenTarget = 1916; } //Open V
			else if (vexRT[Btn8D]) { RarmPotenTarget = 2898; armPotenTarget = 1162; } //Straight

			//Arm Mini Adjust
			if (vexRT[Btn6U]) {armPotenTarget = armPotenTarget + 2; RarmPotenTarget = RarmPotenTarget - 2;}
			if (vexRT[Btn6D]) {armPotenTarget = armPotenTarget - 2; RarmPotenTarget = RarmPotenTarget + 2;}
		}


		//autoLift ON OFF CTRL && LIFT ENCODER RESET
		if ( (vexRT[Btn5U] == true) && (vexRT[Btn5D] == true) )
		{
			freezeLift = true;
			autoLift = false;

			motor[LBLift] = 0;
			/*if ( (LBLiftVal != 0) || (RBLiftVal != 0) )
			{
				liftEncoderZeroed = false;
			}*/

			if ( (vexRT[Btn7L] == true) && (vexRT[Btn7U] == true) && (vexRT[Btn7R] == true) && (vexRT[Btn7D] == true) ) //&& (liftEncoderZeroed == false) )
			{
				//LBLiftEncoderOffset = SensorValue[LiftPoten];
				LBLiftVal = 0;
				liftPotenTarget = 0;
				//liftEncoderZeroed = true;
			}
			else
			{
				if ( (vexRT[Btn7L] == true) && (vexRT[Btn7U] == true) && (vexRT[Btn7R] == false) && (vexRT[Btn7D] == false) )
				{
					autoLiftPrimed = true;
					IgnoreLiftFloor = false;
				}
				if ( (vexRT[Btn7L] == false) && (vexRT[Btn7U] == false) && (vexRT[Btn7R] == true) && (vexRT[Btn7D] == true) )
				{
					autoLiftPrimed = false;
					IgnoreLiftFloor = true;
				}
			}
		}
		else
		{
			freezeLift = false;
			if (autoLiftPrimed == true) {autoLift = true;}
		}

		//Auto Lift Control
		if (autoLift == true)
		{
			/*if (SensorValue(LiftPoten) > 1100)
			{
				motor[LBLift] = ((vexRT[Btn5U] - vexRT[Btn5D]) * 127) + ((vexRT[Btn7U] - vexRT[Btn7D]) * 40 );
			}
			else
			{
				motor[LBLift] = vexRT[Btn5U] * 127 + (vexRT[Btn7U] - vexRT[Btn7D]) * 40;
			}
			//Set Target Lift Position
			/*if (vexRT[Btn7D]/* && (armPotenTarget != 4095) && (RarmPotenTarget != 0)) { liftPotenTarget = 550; armOpenV = true;} //NEW down	poten4095
			else if (vexRT[Btn7L]/* && (armPotenTarget != 4095) && (RarmPotenTarget != 0)) { liftPotenTarget = 1500;} //NEW middle 	poten2978
			else if (vexRT[Btn7U]/* && (armPotenTarget != 4095) && (RarmPotenTarget != 0)) { liftPotenTarget = 3033; armOpenStraight = true;} //NEW up   	poten1528

			if ( (armOpenV == true) && (SensorValue(LiftPoten) < 570) )
			{
				armOpenV = false;
				RarmPotenTarget = 1938; armPotenTarget = 1789;
			}

			if ( (armOpenStraight == true) && (SensorValue(LiftPoten) > 3013) )
			{
				armOpenStraight = false;
				RarmPotenTarget = 1278; armPotenTarget = 1116;
			}

			//Lift Mini Adjust
			if (vexRT[Btn5U] && !vexRT[Btn5D]) {liftPotenTarget = liftPotenTarget + 1;}
			if (vexRT[Btn5D] && !vexRT[Btn5U]) {liftPotenTarget = liftPotenTarget - 1;}*/
		}

		//Manual Lift Control
		if (autoLift == false && freezeLift == false)
		{
			//motor[RBLift] = ((vexRT[Btn5U] - vexRT[Btn5D]) * 127) + ((vexRT[Btn7R] - vexRT[Btn7D]) * 40 );
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

		armPosition();

		liftPosition();

		//Manual Arm Control
		if (autoArm == false && freezeArm == false)
		{
			motor[LArm] = ((vexRT[Btn6U] - vexRT[Btn6D]) * 127) + ((vexRT[Btn8U] - vexRT[Btn8D]) * 40 );
			motor[RArm] = -((vexRT[Btn6U] - vexRT[Btn6D]) * 127) - ((vexRT[Btn8U] - vexRT[Btn8D]) * 40 );
		}

		//Drive Wheels
		if ((vexRT[Ch3] < creep) && (vexRT[Ch3] >-creep) && (vexRT[Ch4] < creep) && (vexRT[Ch4] >-creep)){motor[FLWheel] = 0;} else {motor[FLWheel] = vexRT[Ch3] + vexRT[Ch4]; }
		if ((vexRT[Ch3] < creep) && (vexRT[Ch3] >-creep) && (vexRT[Ch1] < creep) && (vexRT[Ch1] >-creep)){motor[BLWheel] = 0;} else {motor[BLWheel] = vexRT[Ch3] - vexRT[Ch1]; }
		if ((vexRT[Ch2] < creep) && (vexRT[Ch2] >-creep) && (vexRT[Ch4] < creep) && (vexRT[Ch4] >-creep)){motor[FRWheel] = 0;} else {motor[FRWheel] = vexRT[Ch2] - vexRT[Ch4]; }
		if ((vexRT[Ch2] < creep) && (vexRT[Ch2] >-creep) && (vexRT[Ch1] < creep) && (vexRT[Ch1] >-creep)){motor[BRWheel] = 0;} else {motor[BRWheel] = vexRT[Ch2] + vexRT[Ch1]; }

		//Manual Safety Signal
		if ( (autoArm == false) && (vexRT[Btn5U] == true) && (vexRT[Btn5D] == true) && (vexRT[Btn6U] == true) && (vexRT[Btn6D] == true) && (safetysignal == false) )
		{
			safetysignal = true;
			playTone(1500, 50);
			wait1Msec(1000);
			if (SensorValue[armPoten] < 11)
			{
				playTone(1500, 50);
				wait1Msec(1000);
				if (SensorValue[RarmPoten] > 4085)
				{
					playTone(1500, 50);
					wait1Msec(1000);
				}
				else
				{
					playTone(1000, 50);
					wait1Msec(1000);
				}
			}
			else
			{
				playTone(1000, 50);
				wait1Msec(1000);
				if (SensorValue[RarmPoten] > 4085)
				{
					playTone(1500, 50);
					wait1Msec(1000);
				}
				else
				{
					playTone(1000, 50);
					wait1Msec(1000);
				}
			}
			safetysignal = false;
		}
	}
}

void stopWheels ()
{
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;
}

void resetDrive()
{
	SensorValue(FLEncoder) = 0;
	resetMotorEncoder(BLWheel);
	SensorValue(FREncoder) = 0;
	resetMotorEncoder(BRWheel);
	FLTarget = 0;
	BLTarget = 0;
	FRTarget = 0;
	BRTarget = 0;
}

void moveForward (int target)//int waitTime)
{
	resetDrive();
	FLTarget = target;
	BLTarget = target;
	FRTarget = target;
	BRTarget = target;
}

void moveBackward (int target)//int waitTime)
{
	resetDrive();
	FLTarget = -target;
	BLTarget = -target;
	FRTarget = -target;
	BRTarget = -target;
}

void strafeLeft (int target)//int waitTime)
{
	resetDrive();
	FLTarget = -target;
	BLTarget = target;
	FRTarget = target;
	BRTarget = -target;
}

void strafeRight (int target)//int waitTime)
{
	resetDrive();
	FLTarget = target;
	BLTarget = -target;
	FRTarget = -target;
	BRTarget = target;
}

void rotateLeft (int target)//int waitTime)
{
	resetDrive();
	FLTarget = -target;
	BLTarget = -target;
	FRTarget = target;
	BRTarget = target;
}

void rotateRight (int target)//int waitTime)
{
	resetDrive();
	FLTarget = target;
	BLTarget = target;
	FRTarget = -target;
	BRTarget = -target;
}

void FRWheelgo()
{
	iEncoder = iEncoderFR;
	TpEncoder = TpEncoderFR;
	errorEncoderPrevious = errorEncoderPreviousFR;
	encoderVal = SensorValue(FREncoder);
	motor[FRWheel] = driveEncoderPID (FRTarget);
	errorEncoderPreviousFR = errorEncoder;
	TpEncoderFR = TpEncoder;
	iEncoderFR = iEncoder;
}

void FLWheelgo()
{
	iEncoder = iEncoderFL;
	TpEncoder = TpEncoderFL;
	errorEncoderPrevious = errorEncoderPreviousFL;
	encoderVal = SensorValue(FLEncoder);
	motor[FLWheel] = driveEncoderPID (FLTarget);
	errorEncoderPreviousFL = errorEncoder;
	TpEncoderFL = TpEncoder;
	iEncoderFL = iEncoder;
}

void BRWheelgo()
{
	iEncoder = iEncoderBR;
	TpEncoder = TpEncoderBR;
	errorEncoderPrevious = errorEncoderPreviousBR;
	encoderVal = nMotorEncoder[BRWheel];
	motor[BRWheel] = driveEncoderPID (BRTarget);
	errorEncoderPreviousBR = errorEncoder;
	TpEncoderBR = TpEncoder;
	iEncoderBR = iEncoder;
}

void BLWheelgo()
{
	iEncoder = iEncoderBL;
	TpEncoder = TpEncoderBL;
	errorEncoderPrevious = errorEncoderPreviousBL;
	encoderVal = nMotorEncoder[BLWheel];
	motor[BLWheel] = driveEncoderPID (BLTarget);
	errorEncoderPreviousBL = errorEncoder;
	TpEncoderBL = TpEncoder;
	iEncoderBL = iEncoder;
}


int driveEncoderPID (int encoderInTarget)
{
	errorEncoder = ( encoderInTarget - encoderVal ); // Error = Target - Observed

	if ((errorEncoder > 0 && errorEncoderPrevious < 0) || (errorEncoder < 0 && errorEncoderPrevious > 0) || (errorEncoder == 0))
	{
		iEncoder = 0;
	}

	if (abs(errorEncoder)>5)
	{
		//playImmediateTone(600,5);
	}

	iEncoder = iEncoder + errorEncoder; // Integral = Integral + Error

	dEncoder = errorEncoder - errorEncoderPrevious; // Derivative = Error - PreviousError

	editEncoder = KpEncoder * errorEncoder + KiEncoder * iEncoder + KdEncoder * dEncoder; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		//if  (autoArm == true)
		//{
	motorPIDout = TpEncoder + editEncoder; // MotorPower = PreviousMotorPower + Edit
		//}
	TpEncoder += editEncoder; // MotorPower = PreviousMotorPower + Edit

	if (TpEncoder > 128)
	{
		TpEncoder = 127;
	}

	if (TpEncoder < -128)
	{
		TpEncoder = -127;
	}
	return motorPIDout;
}

void armPosition ()
{
	if (autoArm == true)
		{
		//Arm PID ****************************************************************************************************

		errorArm = ( armPotenTarget - SensorValue[armPoten] ); // Error = Target - Observed

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

		//RArm PID ****************************************************************************************************

		errorRArm = ( RarmPotenTarget - SensorValue[RarmPoten] ); // Error = Target - Observed

		if ((errorRArm > 0 && errorRArmPrevious < 0) || (errorRArm < 0 && errorRArmPrevious > 0) || (errorRArm == 0))
		{
			iRArm = 0;
		}

		if (abs(errorRArm)>5)
		{
			//playImmediateTone(600,5);
		}
		iRArm = iRArm + errorRArm; // Integral = Integral + Error

		dRArm = errorRArm - errorRArmPrevious; // Derivative = Error - PreviousError

		errorRArmPrevious = errorRArm;

		editRArm = KpRArm * errorRArm + KiRArm * iRArm + KdRArm * dRArm; // Edit = Kp * Error + Ki * Integral + Kd * Derivative
		//if  (autoArm == true)
		//{
		motor[RArm] = TpRArm + editRArm; // MotorPower = PreviousMotorPower + Edit
		//}
		TpRArm += editRArm; // MotorPower = PreviousMotorPower + Edit

		if (TpRArm > 128)
		{
			TpRArm = 127;
		}

		if (TpRArm < -128)
		{
			TpRArm = -127;
		}

		//get poten val!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		RarmPotenVal = SensorValue(RarmPoten);
		mtrpowerRArm = motor[RArm];

	}
}

void liftPosition ()
{
	//Lift PID ***************************************************************************************************

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

void resetLiftPID()
{
	TpLift = 0; //TUNABLE: [Starting] Power of right launcher
	errorLift = 0; //Error of right launcher

	iLift = 0; //Integral of right launcher

	dLift = 0; //Derivative of right launcher
	errorLiftPrevious = 0;

	editLift = 0; //Edit: How much to change right launch speed

	liftPotenTarget = SensorValue(LiftPoten);
}
