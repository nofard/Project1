#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <fstream>
#include "io_utils.h"
#include <map>
using namespace std;
class Configuration
{
	int MaxSteps;
	int MaxStepsAfterWinner;
	int BatteryCapacity;
	int BatteryConsumptionRate;
	int BatteryRechargeRate;

	
public:
	//initDefaultConfiguration: initilize data members to default values.
	void initDefaultConfiguration()
	{
		MaxStepsAfterWinner = 200;
		BatteryCapacity = 400;
		BatteryConsumptionRate = 1;
		BatteryRechargeRate = 20;
	}

	//get and set functions:
	int getMaxSteps() { return MaxSteps; }
	void setMaxSteps(int _maxSteps) { MaxSteps = _maxSteps; }
	
	int getBatteryCapacity() { return BatteryCapacity; }
	void setBatteryCapacity(int _batteryCapacity) { BatteryCapacity = _batteryCapacity; }
	
	int getMaxStepsAfterWinner() { return MaxStepsAfterWinner; }
	void setMaxSteps(int _maxStepsAfterWinner) { MaxStepsAfterWinner = _maxStepsAfterWinner; }
	

	int getBatteryConsumptionRate() { return BatteryConsumptionRate; }
	void setBatteryConsumptionRate(int _BatteryConsumptionRate) { BatteryConsumptionRate = _BatteryConsumptionRate; }

	int getBatteryRechargeRate() { return BatteryRechargeRate; }
	void setBatteryRechargeRate(int _BatteryRechargeRate) { BatteryRechargeRate = _BatteryRechargeRate; }

	bool initConfiguration();
	void initParameterValue(char* configParameter, int parameterValue);
	bool checkConfigValidation();
	map<string,int> convertDataToMap();
};

#endif