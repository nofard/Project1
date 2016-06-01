#include "_204032031_secondAlgorithm.h"


REGISTER_ALGORITHM(_204032031_secondAlgorithm)

// setSensor is called once when the Algorithm is initialized 
void _204032031_secondAlgorithm::setSensor(const AbstractSensor& _sensor)  {
	sensor = &_sensor;
}


// setConfiguration is called once when the Algorithm is initialized - see below 
void _204032031_secondAlgorithm::setConfiguration(map<string, int> config) {
	configuration = config;
	batteryLevel = configuration["BatteryCapacity"];
}

// step is called by the simulation for each time unit 
Direction _204032031_secondAlgorithm::step(Direction lastStep)
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
void _204032031_secondAlgorithm::aboutToFinish(int stepsTillFinishing) {
	// ignore
}

Direction _204032031_secondAlgorithm::getDirection()
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

Direction _204032031_secondAlgorithm::getDirectionFromRoute()
{
	Direction chosenDirection = opposite(route.back());
	route.pop_back();

	return chosenDirection;
}

void _204032031_secondAlgorithm::updateAlgorithmInfo(Direction lastStep)
{
	int stepsFromDocking = -1;
	currPosition.move(lastStep); // update the robot position, as managed by the algorithm, to the new position
	sensorInfo = sensor->sense();
	//debug << "position: " << position << ", dirtLevel = " << s.dirtLevel << endl;
	// update the map with the info on the dirt level
	//stepsFromDocking = calcStepsToDocking(stepsFromDocking + 1, currPosition);

	houseMapping[currPosition] = { (sensorInfo.dirtLevel != 0) ? sensorInfo.dirtLevel - 1 : 0, 0 };
	// update all 4 cells around me with Wall information and if possible also with stepsToDocking
	for (Direction d : directions)
	{
		Point p = currPosition.neighbour(d);
		auto neighbour = houseMapping.find(p);
		if (neighbour == houseMapping.end()) //maybe if neighbour not exist in map
		{
			CellInfo& cellInfo = houseMapping[p]; // create CellInfo
			cellInfo.isWall = sensorInfo.isWall[(int)d];
			if (!sensorInfo.isWall[(int)d]) 
			{
				cellInfo.stepsToDocking = calcStepsToDocking(stepsFromDocking + 1, p);
			}
		}
	}
	updateBattery();
}


void _204032031_secondAlgorithm::determineMode()
{
	if (batteryLevel < configuration["BatteryCapacity"] && currPosition.isSame(dockingPoint))
		mode = CHARGING;
	if (batteryLevel <= configuration["BatteryCapacity"] / 2 + 1)
		mode = BACKING;
	if (batteryLevel == configuration["BatteryCapacity"])
		mode = GOING;
}

void _204032031_secondAlgorithm::updateBattery()
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

int _204032031_secondAlgorithm::getBatteryLevel()
{
	return batteryLevel;
}

int _204032031_secondAlgorithm::calcStepsToDocking(int stepsFromDocking, const Point& position) {
	// if this cell already has a better route - keep it!
	auto thisCellInfo = houseMapping.find(position);
	if (thisCellInfo != houseMapping.end() && thisCellInfo->second.stepsToDocking != -1 &&
		thisCellInfo->second.stepsToDocking < stepsFromDocking) {
		return thisCellInfo->second.stepsToDocking;
	}
	// check if there is a better route via neighbours that we visited already
	int bestRouteSteps = stepsFromDocking;
	for (Point p : position.neighbours()) {
		auto neighbour = houseMapping.find(p);
		if (neighbour != houseMapping.end() && neighbour->second.stepsToDocking != -1 &&
			neighbour->second.stepsToDocking < bestRouteSteps - 1) {
			bestRouteSteps = neighbour->second.stepsToDocking + 1;
		}
	}
	if (bestRouteSteps < stepsFromDocking) {
		updateStepsToDocking(bestRouteSteps, position);
	}
	return bestRouteSteps;
}

void _204032031_secondAlgorithm::updateStepsToDocking(int stepsToDocking, const Point& position) {
	if (houseMapping[position].stepsToDocking > stepsToDocking || houseMapping[position].stepsToDocking == -1) {
		houseMapping[position].stepsToDocking = stepsToDocking;
		for (Point p : position.neighbours()) {
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