#include "KeyboardRobot.h"

//setSensor: Set sensor data member.
void KeyboardRobot::setSensor(const Sensor& _sensor)
{
	sensor = &_sensor;
}

//setPosition: set robotPosition with a specifiec point.
void KeyboardRobot::setPosition(Point p)
{
	robotPosition = p;
}
//setPosition: set robotPosition with a specifiec x and y coordinates.
void KeyboardRobot::setPosition(int x, int y)
{
	robotPosition.setPoint(x, y);
}

//getPosition: return robotPosition.
Point KeyboardRobot::getPosition()
{
	return robotPosition;
}

//move: set the new X and Y of the robot according to the current direction.
void KeyboardRobot::move()
{
	robotPosition.move(direction);
}

//setDirection: set direction data member.
void KeyboardRobot::setDirection(Direction dir)
{
	direction = dir;
}

//getDirection: return direction according to the key. if the key isn't a direction one, function will return -1.
int KeyboardRobot::getDirection(char key)
{
	for (int i = 0; i < NUM_OF_KEYS; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

//setArrowKeys: set arrowKeys array.
void KeyboardRobot::setArrowKeys(const char* keys)
{
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}

//step: get input from the user, set and return the new direction of the robot.
//if there is a wall in the next step of the robot, robot will change to "stay" direction.
Direction KeyboardRobot::step()
{
	char keyPressed = 0;
	int dir = DEFAULT_DIR;
	SensorInformation currSensorInfo;

	if (_kbhit())
	{
		keyPressed = _getch();
		if (keyPressed == ESC_KEY)
			wasEscPressed = true;
		if ((dir = getDirection(keyPressed)) != -1)
			direction = (Direction)dir;
	}

	currSensorInfo = sensor->sense();
	if (currSensorInfo.isWall[(int)direction])
		direction = Direction::STAY;

	return (Direction)(direction);
}

//reduceBatteryLevel: reduce battery level according to BatteryConsumptionRate in the configuration file.
void KeyboardRobot::reduceBatteryLevel(int batteryConsumptionRate)
{
//	if (!((direction == Direction::STAY) && (!isOnDirt())))
		//if (batteryLevel <= int(configuration::BatteryConsumptionRate))
		if (batteryLevel <= batteryConsumptionRate)
			batteryLevel = 0;
		else
			//batteryLevel -= int(configuration::BatteryConsumptionRate);
			batteryLevel -= batteryConsumptionRate;
}

//isOnDirt: return true if the robot is currently positioned on dirt.
bool KeyboardRobot::isOnDirt() {
	SensorInformation currSensorInfo;
	currSensorInfo = sensor->sense();

	if (currSensorInfo.dirtLevel >= MIN_DIRT_LEVEL + 1 && currSensorInfo.dirtLevel <= MAX_DIRT_LEVEL)
		return true;
	else
		return false;

}

//getBatteryLevel: return battery level data member.
int KeyboardRobot::getBatteryLevel() {
	return batteryLevel;
}

//increaseBatteryLevel: increase battery level according to BatteryRachargeRate in the configuration file.
void KeyboardRobot::increaseBatteryLevel(int batteryRachargeRate) {
	//batteryLevel += (int)configuration::BatteryRachargeRate;
	batteryLevel += batteryRachargeRate;
}

//setBatteryLevel: set batteryLevel.
void KeyboardRobot::setBatteryLevel(int batteryNewLevel) {
	batteryLevel = batteryNewLevel;
}

//resetData: gets the initial battery capacity and resets all data keyboard robot contains.
void KeyboardRobot::resetData(int batteryCapacity)
{
	direction = Direction::STAY;
	batteryLevel = batteryCapacity;
	delete sensor;
}
/*
Sensor * KeyboardRobot::getSensor()
{
	return sensor;
}*/


