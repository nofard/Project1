#define _CRT_SECURE_NO_WARNINGS
#include "configuration.h"

bool Configuration::initConfiguration() 
{
	ifstream configFile("config.ini");
	char buff[BUFF_SIZE];
	char *configParameter;
	int parameterValue;

	initDefaultConfiguration();

	if (configFile)// if config file exist
	{
		if (configFile.fail())  //exists but fails to open file
		{
			cout << "config.ini exists but cannot be opened" << endl;
			return false;
		}
		else
		{
			while (!configFile.eof())
			{
				configFile.getline(buff, BUFF_SIZE - 1);
				configParameter = strtok(buff, "=");
				parameterValue = atoi(strtok(NULL, " "));
				initParameterValue(configParameter, parameterValue);
			}
			return checkConfigValidation();
		}
	}
	else
		return true;
}

void Configuration::initParameterValue(char* configParameter, int parameterValue)
{
	if (!strcmp(configParameter, "MaxStepsAfterWinner"))
		MaxStepsAfterWinner = parameterValue;

	if (!strcmp(configParameter, "BatteryCapacity"))
		BatteryCapacity = parameterValue;

	if (!strcmp(configParameter, "BatteryConsumptionRate"))
		BatteryConsumptionRate = parameterValue;

	if (!strcmp(configParameter, "BatteryRachargeRate"))
		BatteryRachargeRate = parameterValue;
}

bool Configuration::checkConfigValidation()
{
	if (MaxStepsAfterWinner < 0 || BatteryCapacity < 0 || BatteryConsumptionRate < 0 || BatteryRachargeRate < 0)
	{
		cout << "config.ini have bad values" << endl;
		return false;
	}	
	else
		return true;
}
map<string, int> Configuration::convertDataToMap()
{
	map<string, int> dataMap;

	dataMap.insert(std::pair<string, int>("MaxStepsAfterWinner", MaxStepsAfterWinner));
	dataMap.insert(std::pair<string, int>("BatteryCapacity", BatteryCapacity));
	dataMap.insert(std::pair<string, int>("BatteryConsumptionRate", BatteryConsumptionRate));
	dataMap.insert(std::pair<string, int>("BatteryRachargeRate", BatteryRachargeRate));
	
	return dataMap;
}