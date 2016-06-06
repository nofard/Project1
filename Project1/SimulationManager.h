#ifndef _SIMULATION_MANAGER_H_
#define _SIMULATION_MANAGER_H_


#include "Simulator.h"
#include "AlgorithmScore.h"



class SimulationManager
{
	int numOfSimulators;
	Simulator* simulators;
	int stepNumber = 0;
	int winnerStepsNumber;
	list<string> housesNumbers;
	list<string> errors;
	map<string, AlgorithmScore> scoreTableData;
	
public:
	Configuration config;
	SimulationManager(Configuration _config, int _numOfSimulators) : config(_config), numOfSimulators(_numOfSimulators) { winnerStepsNumber = _config.getMaxSteps(); }
	
	void initSimulators(House currHouse);
	void freeSimulators();
	Simulator* simulatorNumber(int num);
	bool endSimulation();
	void increaseStepNumber();
	void setWinnerStepNumber();
	void addHouseNumber(string houseNumber);
	void addNoteToErrorsList(string note);
	void saveAlgoNameToTable(list<string>);
	void saveScore(string algoName, int score);
	map<string, AlgorithmScore> getAlgoScore();
	int getWinnerStepNumber();
	void deleteSimFromArray(int indexOfSim);
	void printSimulationResults(list<string> algorithmNames);
	void printHousesNumbers();
	void printErrors();
	void calcScoreTableDataAvgs();
	void resetParametersForNextHouse();
	string getMaxScoreAlgorithmName();

};


#endif