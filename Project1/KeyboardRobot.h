#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "AbstractSensor.h"
#include "Sensor.h"

#define NUM_OF_KEYS 5
#define ESC_KEY 27
#define DEFAULT_DIR -1

class KeyboardRobot
{
	Point robotPosition;
	Direction direction = Direction::Stay;
	char arrowKeys[NUM_OF_KEYS];
	const AbstractSensor* sensor;
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
	void increaseBatteryLevel(int batteryRechargeRate);
	void setBatteryLevel(int);
	void resetData(int batteryCapacity);
};

#endif