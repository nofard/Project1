#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include "io_utils.h"
#include "KeyboardRobot.h"
#include "House.h"
#include "exampleHouse.h"
#include "Sensor.h"
#include "Menus.h"
#include "Score.h"

class Simulator 
{
	House originalHouse;
	House currHouse;
	KeyboardRobot robot;
	Sensor* sensor;
	int stepNumber = 0;

public:
	void init();
	void init(char** house_array, int rows, int cols);
	void run();
	void Simulator::updateDirtLevel(Point p);
	void printSimulationData();
	void resetSimulatorData();
	void chargeRobot(Point p);
	bool endGame();
};

#endif
