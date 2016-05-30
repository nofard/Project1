#ifndef _SIMULATION_MANAGER_H_
#define _SIMULATION_MANAGER_H_

#include "Simulator.h"

class SimulationManager
{
	int numOfSimulators;
	Simulator* simulators;
	int stepNumber = 0;
	int winnerStepsNumber = 0;
	list<string> errors;
	
public:
	Configuration config;
	SimulationManager(Configuration _config, int _numOfSimulators) : config(_config), numOfSimulators(_numOfSimulators) {}
	
	void initSimulators(House currHouse);
	Simulator* simulatorNumber(int num);
	bool endSimulation();
	void increaseStepNumber();
	void setWinnerStepNumber();
	void addNoteToErrorsList(string note);
	void printSimulationResults();

};


#endif