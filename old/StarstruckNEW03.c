#pragma config(Sensor, in1,    RarmPoten,      sensorPotentiometer)
#pragma config(Sensor, in3,    armPoten,       sensorPotentiometer)
#pragma config(Sensor, in8,    LiftPoten,      sensorPotentiometer)
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
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//User Created Tasks
//task gripControl();

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
	float TpLift = 0; //TUNABLE: [Starting] Power of right launcher
	float errorLift = 0; //Error of right launcher

	float iLift = 0; //Integral of right launcher

	float dLift = 0; //Derivative of right launcher
	float errorLiftPrevious = 0;

	float editLift = 0; //Edit: How much to change right launch speed


//Global Variables
int time = 0;

int armPotenVal = 50;
int armPotenTarget = 50;

int RarmPotenVal = 50;
int RarmPotenTarget = 50;

int liftPotenVal = 550;
int liftPotenTarget = 550;

float KpArm =  0.00003;//0.00003
float KiArm =  0.00000001;
float KdArm =  0.08; //0.08

float KpRArm = 0.00003;
float KiRArm = 0.00000001;
float KdRArm = 0.08;

float KpLift =  -0.0004;
float KiLift =  0;//-0.0000000000001;
float KdLift =  -0.22; //2

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
bool highHang = false;

//Prototyped Functions
void stopWheels();
void moveForward();//int waitTime);
void moveBackward();//int waitTime);
void strafeLeft();//int waitTime);
void strafeRight();//int waitTime);
void rotateLeft();//int waitTime);
void rotateRight();//int waitTime);
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
	time = 0;
	while (true)
	{
		/*
		drive:
		void moveForward();//int waitTime);
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

		//RUN ON TIME
		//LEFT SIDE
		///*
		if (time == 0)
		{
			motor[FLWheel] = 55;
			motor[BLWheel] = 110;
			motor[FRWheel] = 127;
			motor[BRWheel] = 97;
			//liftPotenTarget = 3100; RliftPotenTarget = 3100;

		}

		if (time == 1200)
		{
			RarmPotenTarget = 1011; armPotenTarget = 912;
		}

		if(time == 800)
		{
			stopWheels();
			liftPotenTarget = 2300;
		}

		if (time == 3000)
		{
			motor[FLWheel] = 90;
			motor[BLWheel] = 127;
			motor[FRWheel] = 127;
			motor[BRWheel] = 127;
		}

		if (time == 4200)
		{
			stopWheels();
		}

		if (time == 5000)
		{
			motor[FLWheel] = 50;
			motor[BLWheel] = 50;
			motor[FRWheel] = -50;
			motor[BRWheel] = -50;
		}

		if (time == 5800)
		{
			stopWheels();
		}
		//*/
		//RIGHT SIDE *********************************************************************
		/*
		if (time == 0)
		{
			motor[FLWheel] = 127;
			motor[BLWheel] = 50;
			motor[FRWheel] = 50;
			motor[BRWheel] = 110;
			//liftPotenTarget = 3100; RliftPotenTarget = 3100;

		}

		if (time == 1200)
		{
			RarmPotenTarget = 1011; armPotenTarget = 912;
		}

		if(time == 800)
		{
			stopWheels();
			liftPotenTarget = 2300;
		}

		if (time == 3000)
		{
			motor[FLWheel] = 127;
			motor[BLWheel] = 127;
			motor[FRWheel] = 90;
			motor[BRWheel] = 127;
		}

		if (time == 4200)
		{
			stopWheels();
		}

		if (time == 5000)
		{
			motor[FLWheel] = -50;
			motor[BLWheel] = -50;
			motor[FRWheel] = 50;
			motor[BRWheel] = 50;
		}

		if (time == 5800)
		{
			stopWheels();
		}
		//*/
		//**********************************************
		//ALWAYS-ON
		liftPosition();
		armPosition();

		//TIME COUNTER
		wait1Msec(1);
		time = time + 1;
	}
}
task usercontrol()
{
	autoArm = true;
	autoLift = false;

	bool armOpenV = false;
	bool armOpenStraight = false;

	bool liftEncoderZeroed = false;

	int creep = 25;

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
			if (vexRT[Btn8U]) { RarmPotenTarget = 2870; armPotenTarget = 2745; } //closed //2870, 2745
			else if (vexRT[Btn8L]) { RarmPotenTarget = 2350; armPotenTarget = 2250; } //Closed V
			else if (vexRT[Btn8R]) { RarmPotenTarget = 1938; armPotenTarget = 1789; } //Open V
			else if (vexRT[Btn8D]) { RarmPotenTarget = 1278; armPotenTarget = 1116; } //Straight

			//Arm Mini Adjust
			if (vexRT[Btn6U]) {armPotenTarget = armPotenTarget + 2; RarmPotenTarget = RarmPotenTarget + 2;}
			if (vexRT[Btn6D]) {armPotenTarget = armPotenTarget - 2; RarmPotenTarget = RarmPotenTarget - 2;}
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
				}
				if ( (vexRT[Btn7L] == false) && (vexRT[Btn7U] == false) && (vexRT[Btn7R] == true) && (vexRT[Btn7D] == true) )
				{
					autoLiftPrimed = false;
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
			//Set Target Lift Position
			if (vexRT[Btn7D]/* && (armPotenTarget != 4095) && (RarmPotenTarget != 0)*/) { liftPotenTarget = 550; armOpenV = true;} //NEW down	poten4095
			else if (vexRT[Btn7L]/* && (armPotenTarget != 4095) && (RarmPotenTarget != 0)*/) { liftPotenTarget = 1500;} //NEW middle 	poten2978
			else if (vexRT[Btn7U]/* && (armPotenTarget != 4095) && (RarmPotenTarget != 0)*/) { liftPotenTarget = 3033; armOpenStraight = true;} //NEW up   	poten1528

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
			if (vexRT[Btn5D] && !vexRT[Btn5U]) {liftPotenTarget = liftPotenTarget - 1;}

			if (highHang == false)
			{
				if (liftPotenTarget > 3529) {liftPotenTarget = 3529;}
			}
		}

		//Manual Lift Control
		if (autoLift == false && freezeLift == false)
		{
			motor[RBLift] = ((vexRT[Btn5U] - vexRT[Btn5D]) * 127) + ((vexRT[Btn7R] - vexRT[Btn7D]) * 40 );
			motor[LBLift] = ((vexRT[Btn5U] - vexRT[Btn5D]) * 127) + ((vexRT[Btn7U] - vexRT[Btn7L]) * 40 );
		}

		armPosition();

		liftPosition();

		//Manual Arm Control
		if (autoArm == false && freezeArm == false)
		{
			motor[RArm] = ( vexRT[Btn6U] - vexRT[Btn6D] ) * 40;
			motor[LArm] = ( vexRT[Btn6U] - vexRT[Btn6D] ) * 40;
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

void moveForward ()//int waitTime)
{
	motor[FLWheel] = 127;
	motor[BLWheel] = 127;
	motor[FRWheel] = 127;
	motor[BRWheel] = 127;
	/*wait1Msec(waitTime);
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;*/
}

void moveBackward ()//int waitTime)
{
	motor[FLWheel] = -127;
	motor[BLWheel] = -127;
	motor[FRWheel] = -127;
	motor[BRWheel] = -127;
	/*wait1Msec(waitTime);
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;*/
}

void strafeLeft ()//int waitTime)
{
	motor[FLWheel] = -127;
	motor[BLWheel] = 127;
	motor[FRWheel] = 127;
	motor[BRWheel] = -127;
	/*wait1Msec(waitTime);
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;*/
}

void strafeRight ()//int waitTime)
{
	motor[FLWheel] = 127;
	motor[BLWheel] = -127;
	motor[FRWheel] = -127;
	motor[BRWheel] = 127;
	/*wait1Msec(waitTime);
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;*/
}

void rotateLeft ()//int waitTime)
{
	motor[FLWheel] = -127;
	motor[BLWheel] = -127;
	motor[FRWheel] = 127;
	motor[BRWheel] = 127;
	/*wait1Msec(waitTime);
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;*/
}

void rotateRight ()//int waitTime)
{
	motor[FLWheel] = 127;
	motor[BLWheel] = 127;
	motor[FRWheel] = -127;
	motor[BRWheel] = -127;
	/*wait1Msec(waitTime);
	motor[FLWheel] = 0;
	motor[BLWheel] = 0;
	motor[FRWheel] = 0;
	motor[BRWheel] = 0;*/
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

		//RArm PID ******************************************************************************************************

		errorRArm = ( RarmPotenTarget - SensorValue(RarmPoten) ); // Error = Target - Observed

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

		TpRArm = TpRArm + editRArm; // MotorPower = PreviousMotorPower + Edit

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

	if (autoLift == true)
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
