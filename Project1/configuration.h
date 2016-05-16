#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <fstream>
#include "io_utils.h"

class Configuration
{
	int MaxSteps;
	int MaxStepsAfterWinner;
	int BatteryCapacity;
	int BatteryConsumptionRate;
	int BatteryRachargeRate;
public:
	//initDefaultConfiguration: initilize data members to default values.
	void initDefaultConfiguration()
	{
		MaxStepsAfterWinner = 200;
		BatteryCapacity = 400;
		BatteryConsumptionRate = 1;
		BatteryRachargeRate = 20;
	}

	//get and set functions:
	int getMaxSteps() { return MaxSteps; }
	void setMaxSteps(int _maxSteps) { MaxSteps = _maxSteps; }
	
	int getBatteryCapacity() { return BatteryCapacity; }
	void setBatteryCapacity(int _batteryCapacity) { BatteryCapacity = _batteryCapacity; }
	
	int getBatteryConsumptionRate() { return BatteryConsumptionRate; }
	void setBatteryConsumptionRate(int _BatteryConsumptionRate) { BatteryConsumptionRate = _BatteryConsumptionRate; }

	int getBatteryRachargeRate() { return BatteryRachargeRate; }
	void setBatteryRachargeRate(int _BatteryRachargeRate) { BatteryRachargeRate = _BatteryRachargeRate; }

	bool initConfiguration();
	void initParameterValue(char* configParameter, int parameterValue);
	bool checkConfigValidation();
};

#endif