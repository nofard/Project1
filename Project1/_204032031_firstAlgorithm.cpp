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
Direction _204032031_firstAlgorithm::step(Direction lastStep)
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
void _204032031_firstAlgorithm::aboutToFinish(int stepsTillFinishing) {
	// ignore
}

Direction _204032031_firstAlgorithm::getDirection()
{
	SensorInformation sensorInfo = sensor->sense();
	Direction checkDir = direction;

	if (sensorInfo.dirtLevel != 0)
		return Direction::Stay;
	else
	{
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

Direction _204032031_firstAlgorithm::getDirectionFromRoute()
{
	Direction chosenDirection = opposite(route.back());
	route.pop_back();

	return chosenDirection;
}

void _204032031_firstAlgorithm::updateAlgorithmInfo(Direction lastStep)
{
	int stepsFromDocking = -1;
	currPosition.move(lastStep); // update the robot position, as managed by the algorithm, to the new position
	sensorInfo = sensor->sense();
	//debug << "position: " << position << ", dirtLevel = " << s.dirtLevel << endl;
	// update the map with the info on the dirt level
	//stepsFromDocking = calcStepsToDocking(stepsFromDocking + 1, currPosition);
	CellInfo c = CellInfo(1, 1, false);
	//dataMap.insert(std::pair<string, int>("MaxStepsAfterWinner", MaxStepsAfterWinner));
	//houseMapping.insert(pair<Point, CellInfo>(currPosition, c));
//	houseMapping[{0, 0}] = c;
	houseMapping[currPosition] = { (sensorInfo.dirtLevel != 0) ? sensorInfo.dirtLevel - 1 : 0, 0 };
	// update all 4 cells around me with Wall information and if possible also with stepsToDocking
	/*for (Direction d : directions)
	{
		Point p = currPosition.neighbour(d);
		auto neighbour = houseMapping.find(p);
		if (neighbour == houseMapping.end()) //maybe if neighbour not exist in map
		{
			CellInfo& cellInfo = houseMapping[p]; // create CellInfo
			cellInfo.isWall = sensorInfo.isWall[(int)d];
			//if (!sensorInfo.isWall[(int)d]) 
			//{
			//	cellInfo.stepsToDocking = calcStepsToDocking(stepsFromDocking + 1, p);
			//}
		}
	}*/
	updateBattery();
}

void _204032031_firstAlgorithm::determineMode()
{
	if (batteryLevel < config["BatteryCapacity"] && currPosition.isSame(dockingPoint))
		mode = CHARGING;
	if (batteryLevel < config["BatteryCapacity"] / 2)
		mode = BACKING;
	if (batteryLevel == config["BatteryCapacity"])
		mode = GOING;
}

void _204032031_firstAlgorithm::updateBattery()
{
	if (currPosition.isSame(dockingPoint)) 
	{
		if (batteryLevel < 380)
		{
			batteryLevel += configuration["BatteryRachargeRate"];
		}
		else if (batteryLevel >= 380) 
		{
			batteryLevel = 400;
		}
	}
	else
	{
		if (batteryLevel <= configuration["batteryConsumptionRate"])
			batteryLevel = 0;
		else
			batteryLevel -= configuration["batteryConsumptionRate"];
	}
}

int _204032031_firstAlgorithm::getBatteryLevel()
{
	return batteryLevel;
}