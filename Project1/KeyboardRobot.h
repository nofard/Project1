#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "Sensor.h"

#define NUM_OF_KEYS 5
#define ESC_KEY 27

class KeyboardRobot
{
	Point robotPosition;
	Direction direction = Direction::STAY;
	char arrowKeys[NUM_OF_KEYS];
	const Sensor* sensor;
	int batteryLevel;

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
	void reduceBatteryLevel(int batteryConsumptionRate);
	bool isOnDirt();
	int getBatteryLevel();
	void increaseBatteryLevel(int batteryRachargeRate);
	void setBatteryLevel(int);
	void resetData(int batteryCapacity);
};

#endif