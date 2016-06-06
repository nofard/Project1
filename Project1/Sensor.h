#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "House.h"
#include "AbstractSensor.h"

#define DIR_AMOUNT 4

class Simulator;

/*
struct SensorInformation 
{
	int dirtLevel;
	bool isWall[4];
};
*/
class Sensor : public AbstractSensor
{
	Simulator* sim;
	House *house;
	SensorInformation sensorInfo;
	_204032031_Point robotPosition;

public:
	Sensor() {}
	Sensor(Sensor & sensor) 
	{
		House *newHouse = new House();
		newHouse = &(sensor.house->createCopyHouse());
		sensor.sim = sim;
		sensor.sensorInfo = sensorInfo;
		sensor.robotPosition = robotPosition;
	}
	void initSensor(Simulator * _sim, House *_house, _204032031_Point _robotPosition);
	void setHouse(House *_house){house = _house;}
	SensorInformation sense()const;
	void updateSensorInfo(_204032031_Point currPosition);
	void updateSensorInfo();
	void setCurrPosition(_204032031_Point currPosition);
	_204032031_Point& getCurrPosition();
	void updateWallsInfo();
	void updateDirtLevel();
	void revealArea();
	void revealArea(bool saveToArray);
};

#endif