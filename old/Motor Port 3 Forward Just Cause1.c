#pragma config(Motor,  port2,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)0
#pragma autonomousDuration(20)
#pragma userControlDuration(120)


task main()
{
	while(true)
	{
  motor[port2] = 127;
  motor[port3] = 127;
  motor[port4] = 127;
	}
}
