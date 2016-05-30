#ifndef _SIMULATION_MANAGER_H_
#define _SIMULATION_MANAGER_H_


#include "Simulator.h"
#include "AlgorithmScore.h"


class SimulationManager
{
	int numOfSimulators;
	Simulator* simulators;
	int stepNumber = 0;
	int winnerStepsNumber = 0;
	list<string> errors;
	map<string, AlgorithmScore> scoreTableData;
	
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
	void saveAlgoNameToTable(list<string>);
	void saveScore(string algoName, int score);
	map<string, AlgorithmScore> getAlgoScore();
	void setPosition(string algoName, int position);
	int getWinnerStepNumber();
	void deleteSimFromArray(int indexOfSim);

};


#endif