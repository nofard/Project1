#include "KeyboardRobot.h"

void KeyboardRobot::setSensor(const Sensor& _sensor)
{
	sensor = &_sensor;
}

void KeyboardRobot::setPosition(Point p)
{
	robotPosition = p;
}

void KeyboardRobot::setPosition(int x, int y)
{
	robotPosition.setPoint(x, y);
}



Point KeyboardRobot::getPosition()
{
	return robotPosition;
}
void KeyboardRobot::move()
{
	robotPosition.move(direction);
	//robotPosition.draw('@');
}

void KeyboardRobot::setDirection(Direction dir)
{
	direction = dir;
}

int KeyboardRobot::getDirection(char key)
{
	for (int i = 0; i < NUM_OF_KEYS; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

void KeyboardRobot::setArrowKeys(const char* keys)
{
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}

Direction KeyboardRobot::step()
{
	char keyPressed = 0;
	int dir = -1;
	SensorInformation currSensorInfo;

	if (_kbhit())
	{
		keyPressed = _getch();
		if (keyPressed == 27)
			wasEscPressed = true;
		if ((dir = getDirection(keyPressed)) != -1)
			//setDirection((Direction)dir);
			direction = (Direction)dir;
	}

	currSensorInfo = sensor->sense();
	if (currSensorInfo.isWall[(int)direction])
		direction = Direction::STAY;

	return (Direction)(direction);
}

void KeyboardRobot::reduceBatteryLevel() 
{
	if (!((direction == Direction::STAY) && (!isOnDirt())))
		batteryLevel -= int(configuration::BatteryConsumptionRate);
}

bool KeyboardRobot::isOnDirt() {
	SensorInformation currSensorInfo;
	currSensorInfo = sensor->sense();

	if (currSensorInfo.dirtLevel >= 1 && currSensorInfo.dirtLevel <= 9)
		return true;
	else
		return false;

}
int KeyboardRobot::getBatteryLevel() {
	return batteryLevel;
}
void KeyboardRobot::increaseBatteryLevel() {
	batteryLevel += (int)configuration::BatteryRachargeRate;
}
void KeyboardRobot::setBatteryLevel(int batteryNewLevel) {
	batteryLevel = batteryNewLevel;
}


