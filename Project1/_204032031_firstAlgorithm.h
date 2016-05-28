#ifndef __FIRST_ALGORITHM_H_
#define __FIRST_ALGORITHM_H_

#include "DirectionExt.h"
#include "Point.h"
#include "AlgorithmRegistration.h"
#include <map>
#include <list>
#include <cctype>
#include <algorithm>

using namespace std;

#define GOING 0
#define BACKING 1
#define CHARGING 2

struct CellInfo {
	int dirt = -1; // -1 represents "unknown"
	int stepsToDocking = -1; // -1 represents "unknown"
	bool isWall;
	CellInfo() {}
	CellInfo(int dirt, int stepToDock = 0, bool isWall = false) : dirt(dirt), stepsToDocking(stepToDock), isWall(isWall) {}
};

class _204032031_firstAlgorithm : public AbstractAlgorithm 
{
	const AbstractSensor* sensor;
	map<string, int> config;
	Direction direction = Direction::East;
	Point currPosition = { 0, 0 };
	Point dockingPoint = Point(0, 0);
	SensorInformation sensorInfo;
	map<string, int> configuration;
	int batteryLevel;
	list<Direction>route;
	map<Point, CellInfo> houseMapping;
	int mode = GOING; //GOING/BACKING

public:
	// setSensor is called once when the Algorithm is initialized 
	virtual void setSensor(const AbstractSensor& _sensor) override;

	// setConfiguration is called once when the Algorithm is initialized - see below 
	virtual void setConfiguration(map<string, int> config);
	// step is called by the simulation for each time unit 
	virtual Direction step(Direction previousStep);

	// this method is called by the simulation either when there is a winner or 
	// when steps == MaxSteps - MaxStepsAfterWinner 
	// parameter stepsTillFinishing == MaxStepsAfterWinner 
	virtual void aboutToFinish(int stepsTillFinishing);

private:
	Direction getDirection();
	Direction getDirectionFromRoute();
	void updateAlgorithmInfo(Direction lastStep);
	void determineMode();
	void updateBattery();
	int getBatteryLevel();
};

#endif