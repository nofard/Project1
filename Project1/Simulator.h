#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include "io_utils.h"
#include "KeyboardRobot.h"
#include "House.h"
#include "Sensor.h"
#include "Menus.h"
#include "Score.h"

class Menus;

class Simulator 
{
	House originalHouse;
	House currHouse;
	KeyboardRobot robot;
	Sensor* sensor;
	int stepNumber = 0;
	list<StepAndDirection> moves;
	Menus* menu;

public:
	bool endedSuccessfully = true;
	void init();
	void init(char** house_array, int rows, int cols);
	void run();
	void Simulator::updateDirtLevel(Point p);
	void printSimulationData();
	void resetSimulatorData();
	void chargeRobot(Point p);
	bool endGame();
	void freeSimulationMemory();
	void restartSimulation();
	void setStepNumber(int);
	void setCurrentHouseToOriginal();
	void addMoveToList(Direction currDirection);
	void printList();
	list<StepAndDirection> getMoveList();
	int getStepsNum();
	void setMenu();
	Menus* getMenu();
};

#endif
