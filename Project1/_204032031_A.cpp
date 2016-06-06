#include "_204032031_A.h"


REGISTER_ALGORITHM(_204032031_A)

	// setSensor is called once when the Algorithm is initialized 
void _204032031_A::setSensor(const AbstractSensor& _sensor)  {
		sensor = &_sensor;
	}


	// setConfiguration is called once when the Algorithm is initialized - see below 
void _204032031_A::setConfiguration(map<string, int> config) {
	configuration = config;
	batteryLevel = configuration["BatteryCapacity"];
}

	// step is called by the simulation for each time unit 
Direction _204032031_A::step(Direction lastStep)
{
	Direction chosenDirection;
	updateAlgorithmInfo(lastStep);
	determineMode();

	switch (mode)
	{
	case GOING:
		chosenDirection = getDirection();
		if (chosenDirection != Direction::Stay)
			route.push_back(chosenDirection);
		break;
	case BACKING:
		chosenDirection = getDirectionFromRoute();
		break;
	case CHARGING:
		chosenDirection = Direction::Stay;
		break;
	default:
		break;
	}

	return chosenDirection;
}

	// this method is called by the simulation either when there is a winner or 
	// when steps == MaxSteps - MaxStepsAfterWinner 
	// parameter stepsTillFinishing == MaxStepsAfterWinner 
void _204032031_A::aboutToFinish(int stepsTillFinishing) {
	// ignore
}

Direction _204032031_A::getDirection()
{
	SensorInformation sensorInfo = sensor->sense();
	Direction checkDir = direction;
	_204032031_Point possibleNextPoint;

	if (sensorInfo.dirtLevel != 0)
		return Direction::Stay;
	else
	{
		do
		{
			if (!sensorInfo.isWall[(int)checkDir])
			{
				possibleNextPoint = currPosition;
				possibleNextPoint.move(checkDir);
				if (houseMapping[possibleNextPoint].visited == false)
				{
						direction = checkDir;
						return direction;
				}
			}	
		} while (++checkDir != direction);

		do
		{
			if (!sensorInfo.isWall[(int)checkDir])
			{
				direction = checkDir;
				return direction;
			}
		} while (++checkDir != direction);
	}

	return Direction::Stay;
}

Direction _204032031_A::getDirectionFromRoute()
{
	Direction chosenDirection = opposite(route.back());
	route.pop_back();

	return chosenDirection;
}

void _204032031_A::updateAlgorithmInfo(Direction lastStep)
{
	int stepsFromDocking = -1;
	currPosition.move(lastStep); // update the robot position, as managed by the algorithm, to the new position
	sensorInfo = sensor->sense();
	//debug << "position: " << position << ", dirtLevel = " << s.dirtLevel << endl;
	// update the map with the info on the dirt level
	houseMapping[currPosition] = { (sensorInfo.dirtLevel != 0) ? sensorInfo.dirtLevel - 1 : 0,false, true};
	// update all 4 cells around me with Wall information and if possible also with stepsToDocking
	for (Direction d : directions)
	{
		_204032031_Point p = currPosition.neighbour(d);
		auto neighbour = houseMapping.find(p);
		if (neighbour == houseMapping.end()) //maybe if neighbour not exist in map
		{
			CellInfo& cellInfo = houseMapping[p]; // create CellInfo
			cellInfo.isWall = sensorInfo.isWall[(int)d];
			cellInfo.visited = false;
		}
	}
	updateBattery();
}


void _204032031_A::determineMode()
{
//	if (batteryLevel < configuration["BatteryCapacity"] && currPosition.isSame(dockingPoint))
	//	mode = CHARGING;

	if (batteryLevel == configuration["BatteryCapacity"])
		mode = GOING;
	else
	{
		if (batteryLevel <= configuration["BatteryCapacity"]*50/100 + 1) //battery 50%
			mode = BACKING;

		if (currPosition.isSame(dockingPoint))
			mode = CHARGING;
	}


}

void _204032031_A::updateBattery()
{
	if (currPosition.isSame(dockingPoint)) 
	{
		if (batteryLevel < configuration["BatteryCapacity"] - configuration["BatteryRechargeRate"])
		{
			batteryLevel += configuration["BatteryRechargeRate"];
		}
		else if (batteryLevel >= configuration["BatteryCapacity"] - configuration["BatteryRechargeRate"])
		{
			batteryLevel = configuration["BatteryCapacity"];
		}
	}
	else
	{
		if (batteryLevel <= configuration["BatteryConsumptionRate"])
			batteryLevel = 0;
		else
			batteryLevel -= configuration["BatteryConsumptionRate"];
	}
}

int _204032031_A::getBatteryLevel()
{
	return batteryLevel;
}


