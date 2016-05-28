#ifndef __204032031_A_H
#define __204032031_A_H

#include "DirectionExt.h"
#include "Point.h"
#include "AlgorithmRegistration.h"

struct CellInfo {
	int dirt = -1; // -1 represents "unknown"
	int stepsToDocking = -1; // -1 represents "unknown"
	bool isWall;
	CellInfo() {}
	CellInfo(int dirt, int stepToDock, bool isWall = false) : dirt(dirt), stepsToDocking(stepToDock), isWall(isWall) {}
};

class _204032031_A_ : public AbstractAlgorithm 
{	
	const AbstractSensor* sensor;

	map<Point, CellInfo> houseMapping;
	Direction currDir = Direction::East;
	Point position = { 0, 0 };
	SensorInformation s;
	int stepsFromDocking = -1;
	int totalSteps = 0;
	int phase = -1; // phases 0-7: explore surrounding, phase 8: select new direction
	const static Direction dir_by_phase[8];
	Direction requestedStep = Direction::Stay;
public:
	// setSensor is called once when the Algorithm is initialized 
	virtual void setSensor(const AbstractSensor& _sensor) override {
		sensor = &_sensor;
	}

	// setConfiguration is called once when the Algorithm is initialized - see below 
	virtual void setConfiguration(map<string, int> config) {
		// this algorithm ignores the configuration
		// (this is of course BAD, as we ignore crucial information on the battery
		//  and the need to get back to the docking on time for recharging)
	}

	// step is called by the simulation for each time unit 
	virtual Direction step(Direction lastStep);

	// this method is called by the simulation either when there is a winner or 
	// when steps == MaxSteps - MaxStepsAfterWinner 
	// parameter stepsTillFinishing == MaxStepsAfterWinner 
	virtual void aboutToFinish(int stepsTillFinishing) {
		// this algorithm ignores the aboutToFinish call
		// (this is of course BAD, as we ignore the need to get back to the docking on time)
	}
private:
	void updateAlgorithmInfo(Direction lastStep);

	Direction handlePhase();
	Direction handlePhase8();

	int calcStepsToDocking(int stepsFromDocking, const Point& position);

	void updateStepsToDocking(int stepsToDocking, const Point& position);

};


#endif