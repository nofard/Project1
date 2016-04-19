#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "io_utils.h"
#include "House.h"

#define DIR_AMOUNT 4

class Simulator;

struct SensorInformation 
{
	int dirtLevel;
	bool isWall[4];
};

class Sensor
{
	Simulator * sim;
	House *house;
	SensorInformation sensorInfo;
	Point robotPosition;

public:
	Sensor() {}
	void initSensor(Simulator * _sim, House *_house, Point _robotPosition);
	void setHouse(House *_house){house = _house;}
	SensorInformation sense()const;
	void Sensor::updateSensorInfo(Point currPosition);
	void setCurrPosition(Point currPosition);
	void updateWallsInfo();
	void updateDirtLevel();
	void revealArea();
};

#endif