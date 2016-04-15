#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_
/*
class Configuration
{
	int MaxSteps = 1200;
	int MaxStepsAfterWinner = 200;
	int BatteryCapacity = 400;
	int BatteryConsumptionRate = 1;
	int BatteryRachargeRate = 20;
public:
	
	void setMaxSteps(int _maxSteps) { MaxSteps = _maxSteps; }
	int getMaxSteps() { return MaxSteps; }
	void setBatteryCapacity(int _batteryCapacity) { BatteryCapacity = _batteryCapacity; }
};
*/



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