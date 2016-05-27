#include "_204032031_firstAlgorithm.h"


REGISTER_ALGORITHM(_204032031_firstAlgorithm)

	// setSensor is called once when the Algorithm is initialized 
void _204032031_firstAlgorithm::setSensor(const AbstractSensor& _sensor)  {
		sensor = &_sensor;
	}


	// setConfiguration is called once when the Algorithm is initialized - see below 
void _204032031_firstAlgorithm::setConfiguration(map<string, int> config) {
		// ignore
	}

	// step is called by the simulation for each time unit 
Direction _204032031_firstAlgorithm::step(Direction previousStep) {
		SensorInformation s = sensor->sense();
		Direction checkDir = direction;
		do {
			if (!s.isWall[(int)checkDir]) {
				direction = checkDir;
				
				return direction;
			}
		} while (++checkDir != direction);
		return Direction::Stay;
	}

	// this method is called by the simulation either when there is a winner or 
	// when steps == MaxSteps - MaxStepsAfterWinner 
	// parameter stepsTillFinishing == MaxStepsAfterWinner 
void _204032031_firstAlgorithm::aboutToFinish(int stepsTillFinishing) {
	// ignore
}

void _204032031_firstAlgorithm::reduceBatteryLevel()
{
	if (batteryLevel <= configuration["batteryConsumptionRate"])
		batteryLevel = 0;
	else
		batteryLevel -= configuration["batteryConsumptionRate"];
}

void _204032031_firstAlgorithm::chargeBattery(Point currPosition, Point dockingPosition)
{
	if (currPosition.isSame(dockingPosition)) {
		if (batteryLevel < 380)
		{
			batteryLevel += configuration["BatteryRachargeRate"];
		}
		else if (batteryLevel >= 380) 
		{
			batteryLevel = 400;
		}
	}
}

int _204032031_firstAlgorithm::getBatteryLevel()
{
	return batteryLevel;
}