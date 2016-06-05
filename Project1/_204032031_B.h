#ifndef __SECOND_ALGORITHM_H_
#define __SECOND_ALGORITHM_H_

#include "DirectionExt.h"
#include "Point.h"
#include "AlgorithmRegistration.h"



#include <iostream>
#include <list>
#include <map>
#include <cstring>
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
	CellInfo(int dirt, int stepsTodock, bool isWall = false) :
		dirt(dirt),
		stepsToDocking(stepsTodock),
		isWall(isWall) {}
};

class _204032031_B : public AbstractAlgorithm
{
	const AbstractSensor* sensor;
	map<string, int> configuration;
	Direction direction = Direction::East;
	Point currPosition = { 0, 0 };
	Point dockingPoint = { 0, 0 };
	SensorInformation sensorInfo;
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

	int calcStepsToDocking(int stepsFromDocking, const Point& position);
	void updateStepsToDocking(int stepsToDocking, const Point& position);

private:
	Direction getDirection();
	Direction getDirectionFromRoute();
	void updateAlgorithmInfo(Direction lastStep);
	void determineMode();
	void updateBattery();
	int getBatteryLevel();
};

#endif