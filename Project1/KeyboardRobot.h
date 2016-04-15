#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <cstring>
#include "Point.h"
#include "Sensor.h"
#include "Direction.h"
#include "configuration.h"

#define NUM_OF_KEYS 5

class KeyboardRobot
{
	Point robotPosition;
	Direction direction = Direction::STAY;
	char arrowKeys[NUM_OF_KEYS];
	const Sensor* sensor;
	//int batteryLevel = (int)configuration::BatteryCapacity;
	int batteryLevel = config.BatteryCapacity;

public:
	bool wasEscPressed = false;
	void setSensor(const Sensor& _sensor);
	Direction step();
	void setPosition(Point p);
	void setPosition(int x, int y);
	Point getPosition();
	void setArrowKeys(const char* keys);
	void move();
	int getDirection(char key);
	void setDirection(Direction dir);
	void reduceBatteryLevel();
	bool isOnDirt();
	int getBatteryLevel();
	void increaseBatteryLevel();
	void setBatteryLevel(int);
	void resetData();
};

#endif