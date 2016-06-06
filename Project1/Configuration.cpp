#define _CRT_SECURE_NO_WARNINGS
#include "configuration.h"

//initConfiguration: checks if config.ini file exists and can be reached, if not, prints the appropriate the message, and if can be init configuration object and returns if it was successful or not.
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
//initParameterValue: gets name of config parameter to update and its value and updates the value within the parameter
void Configuration::initParameterValue(char* configParameter, int parameterValue)
{
	if (!strcmp(configParameter, "MaxStepsAfterWinner"))
		MaxStepsAfterWinner = parameterValue;

	if (!strcmp(configParameter, "BatteryCapacity"))
		BatteryCapacity = parameterValue;

	if (!strcmp(configParameter, "BatteryConsumptionRate"))
		BatteryConsumptionRate = parameterValue;

	if (!strcmp(configParameter, "BatteryRechargeRate"))
		BatteryRechargeRate = parameterValue;
}
//checkConfigValidation: check if config parameters are positive values, prints the problematic ones and returns false if at least one of them is negative.
bool Configuration::checkConfigValidation()
{
	string badParameters = "";
	int cntBadParams = 0;

	if (MaxStepsAfterWinner < 0)
	{
		badParameters += " MaxStepsAfterWinner";
		cntBadParams++;
	}
	if (BatteryCapacity < 0)
	{
		badParameters += " BatteryCapacity";
		cntBadParams++;
	}
	if (BatteryConsumptionRate < 0)
	{
		badParameters += " BatteryConsumptionRate";
		cntBadParams++;
	}
	if (BatteryRechargeRate < 0)
	{
		badParameters += " BatteryRechargeRate";
		cntBadParams++;
	}
	
	
	if (cntBadParams > 0) {
		cout << "config.ini have bad values for " << cntBadParams << " parameter(s):" << badParameters << endl;
		return false;
	}
	else
		return true;
}
//convertDataToMap: insert config data members into map with parameter name and its value
map<string, int> Configuration::convertDataToMap()
{
	map<string, int> dataMap;

	dataMap.insert(std::pair<string, int>("MaxSteps", MaxSteps));
	dataMap.insert(std::pair<string, int>("MaxStepsAfterWinner", MaxStepsAfterWinner));
	dataMap.insert(std::pair<string, int>("BatteryCapacity", BatteryCapacity));
	dataMap.insert(std::pair<string, int>("BatteryConsumptionRate", BatteryConsumptionRate));
	dataMap.insert(std::pair<string, int>("BatteryRechargeRate", BatteryRechargeRate));
	
	return dataMap;
}