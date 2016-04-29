#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

class Configuration
{
	int MaxSteps;
	int MaxStepsAfterWinner;
	int BatteryCapacity;
	int BatteryConsumptionRate;
	int BatteryRachargeRate;
public:
	void initDefaultConfiguration()
	{
		MaxStepsAfterWinner = 200;
		BatteryCapacity = 400;
		BatteryConsumptionRate = 1;
		BatteryRachargeRate = 20;
	}

	int getMaxSteps() { return MaxSteps; }
	void setMaxSteps(int _maxSteps) { MaxSteps = _maxSteps; }
	
	int getBatteryCapacity() { return BatteryCapacity; }
	void setBatteryCapacity(int _batteryCapacity) { BatteryCapacity = _batteryCapacity; }
	
	int getBatteryConsumptionRate() { return BatteryConsumptionRate; }
	void setBatteryConsumptionRate(int _BatteryConsumptionRate) { BatteryConsumptionRate = _BatteryConsumptionRate; }

	int getBatteryRachargeRate() { return BatteryRachargeRate; }
	void setBatteryRachargeRate(int _BatteryRachargeRate) { BatteryRachargeRate = _BatteryRachargeRate; }
};

/*
static struct configuration
{
	int MaxSteps = 1200;
	int MaxStepsAfterWinner = 200;
	int BatteryCapacity = 400;
	int BatteryConsumptionRate = 1;
	int BatteryRachargeRate = 20;
}config;
*/


#endif