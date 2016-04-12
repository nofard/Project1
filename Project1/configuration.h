#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

//enum class configuration
//{
//	MaxSteps,
//	MaxStepsAfterWinner = 200,
//	BatteryCapacity = 400,
//	BatteryConsumptionRate = 1,
//	BatteryRachargeRate = 20
//};


static struct configuration
{
	int MaxSteps = 1200;
	int MaxStepsAfterWinner = 200;
	int BatteryCapacity = 400;
	int BatteryConsumptionRate = 1;
	int BatteryRachargeRate = 20;
}config;


/*
int MaxSteps = 1200;
int MaxStepsAfterWinner = 200;
int BatteryCapacity = 400;
int BatteryConsumptionRate = 1;
int BatteryRachargeRate = 20;
*/

#endif