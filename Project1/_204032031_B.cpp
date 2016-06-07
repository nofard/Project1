#include "_204032031_B.h"


REGISTER_ALGORITHM(_204032031_B)

// setSensor is called once when the Algorithm is initialized 
void _204032031_B::setSensor(const AbstractSensor& _sensor) {
	sensor = &_sensor;
}


// setConfiguration is called once when the Algorithm is initialized - see below 
void _204032031_B::setConfiguration(map<string, int> config) {
	configuration = config;
	batteryLevel = configuration["BatteryCapacity"];
}

// step is called by the simulation for each time unit 
Direction _204032031_B::step(Direction lastStep)
{
	Direction chosenDirection;
	updateAlgorithmInfo(lastStep);
	determineMode();

	switch (mode)
	{
	case GOING:
		chosenDirection = getDirection();
		break;
	case BACKING:
		chosenDirection = getDirectionToDocking();
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
void _204032031_B::aboutToFinish(int stepsTillFinishing) {
	// ignore
}

Direction _204032031_B::getDirection()
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
				if (houseMapping[possibleNextPoint].dirt > 0)
				{
					direction = checkDir;
					return direction;
				}
			}
		} while (--checkDir != direction);

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
		} while (--checkDir != direction);

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

void _204032031_B::updateAlgorithmInfo(Direction lastStep)
{
	currPosition.move(lastStep); // update the robot position, as managed by the algorithm, to the new position
	sensorInfo = sensor->sense();
	stepsFromDocking = calcStepsToDocking(stepsFromDocking + 1, currPosition);

	houseMapping[currPosition] = { (sensorInfo.dirtLevel != 0) ? sensorInfo.dirtLevel - 1 : 0, stepsFromDocking ,false, true };
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

			if (!sensorInfo.isWall[(int)d])
			{
				cellInfo.stepsToDocking = calcStepsToDocking(stepsFromDocking + 1, p);

				currPosition.move(d);
				sensorInfo = sensor->sense();
				cellInfo.dirt = sensorInfo.dirtLevel;
				currPosition.move(opposite(d));
			}
		}
	}
	updateBattery();
}

void _204032031_B::determineMode()
{
	if (batteryLevel == configuration["BatteryCapacity"])
		mode = GOING;
	else
	{
		if (batteryLevel <= configuration["BatteryCapacity"] * 50 / 100 + 1) //battery 50%
			mode = BACKING;

		if (currPosition.isSame(dockingPoint))
			mode = CHARGING;
	}
}

void _204032031_B::updateBattery()
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

int _204032031_B::getBatteryLevel()
{
	return batteryLevel;
}

int _204032031_B::calcStepsToDocking(int stepsFromDocking, const _204032031_Point& position)
{
	// if this cell already has a better route - keep it!
	auto thisCellInfo = houseMapping.find(position);
	if (thisCellInfo != houseMapping.end() && thisCellInfo->second.stepsToDocking != -1 && thisCellInfo->second.stepsToDocking < stepsFromDocking)
	{
		return thisCellInfo->second.stepsToDocking;
	}
	// check if there is a better route via neighbours that we visited already
	int bestRouteSteps = stepsFromDocking;
	for (_204032031_Point p : position.neighbours()) {
		auto neighbour = houseMapping.find(p);
		if (neighbour != houseMapping.end() && neighbour->second.stepsToDocking != -1 && neighbour->second.stepsToDocking < bestRouteSteps - 1)
		{
			bestRouteSteps = neighbour->second.stepsToDocking + 1;
		}
	}
	if (bestRouteSteps < stepsFromDocking)
	{
		updateStepsToDocking(bestRouteSteps, position);
	}
	return bestRouteSteps;
}

void _204032031_B::updateStepsToDocking(int stepsToDocking, const _204032031_Point& position)
{
	if (houseMapping[position].stepsToDocking > stepsToDocking || houseMapping[position].stepsToDocking == -1) {
		houseMapping[position].stepsToDocking = stepsToDocking;
		for (_204032031_Point p : position.neighbours()) {
			auto neighbour = houseMapping.find(p);
			if (neighbour != houseMapping.end()) {
				CellInfo cell = neighbour->second;
				if (cell.stepsToDocking > stepsToDocking + 1 || (!cell.isWall && cell.stepsToDocking == -1)) {
					updateStepsToDocking(stepsToDocking + 1, p);
				}
			}
		}
	}
}

Direction _204032031_B::getDirectionToDocking()
{
	int minStepsToDocking = MAX_STEPS_TO_DOCK;

	_204032031_Point chosenNeighbor = currPosition.neighbour(direction);
	for (_204032031_Point currNeighbor : currPosition.neighbours())
	{
		if (houseMapping[currNeighbor].stepsToDocking < minStepsToDocking && houseMapping[currNeighbor].isWall == false)
		{
			minStepsToDocking = houseMapping[currNeighbor].stepsToDocking;
			chosenNeighbor = currNeighbor;
		}
	}

	direction = getNeighborDirection(chosenNeighbor);
	return direction;
}

Direction _204032031_B::getNeighborDirection(_204032031_Point neighbor)
{
	_204032031_Point currNeighbor;
	for (Direction checkDir : directions)
	{
		if (neighbor == currPosition.neighbour(checkDir))
			return checkDir;
	}
	return Direction::Stay;
}
