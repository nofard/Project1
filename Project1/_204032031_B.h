#ifndef __SECOND_ALGORITHM_H_
#define __SECOND_ALGORITHM_H_

#include "DirectionExt.h"
#include "_204032031_Point.h"
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
#define MAX_STEPS_TO_DOCK 999

struct CellInfo {
	int dirt = -1; // -1 represents "unknown"
	int stepsToDocking = -1; // -1 represents "unknown"
	bool isWall;
	bool visited;
	CellInfo() {}
	CellInfo(int dirt, int stepsTodock, bool isWall = false, bool visited = false) :
		dirt(dirt),
		stepsToDocking(stepsTodock),
		isWall(isWall),
		visited(visited) {}
};

class _204032031_B : public AbstractAlgorithm
{
	const AbstractSensor* sensor;
	map<string, int> configuration;
	Direction direction = Direction::East;
	_204032031_Point currPosition = { 0, 0 };
	_204032031_Point dockingPoint = { 0, 0 };
	SensorInformation sensorInfo;
	int stepsFromDocking = -1;
	int batteryLevel;
	map<_204032031_Point, CellInfo> houseMapping;
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
	Direction getDirectionToDocking();
	void updateAlgorithmInfo(Direction lastStep);
	void determineMode();
	void updateBattery();
	int getBatteryLevel();
	int calcStepsToDocking(int stepsFromDocking, const _204032031_Point& position);
	void updateStepsToDocking(int stepsToDocking, const _204032031_Point& position);
	Direction getNeighborDirection(_204032031_Point neighbor);

};

#endif
