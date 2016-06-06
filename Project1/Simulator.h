#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include "KeyboardRobot.h"
#include "Menus.h"
#include "Score.h"
#include "AbstractAlgorithm.h"
//#include "_204032031_firstAlgorithm.h"

#define ROBOT_LETTER '@'
#define DEFAULT_DIR -1
#define SIM_DATA_ROW 22

struct savedForLater
{
	char printedHouse[MAX_ROWS][MAX_COLS];
	House house;
	KeyboardRobot robot;
	_204032031_Point sensorPosition;
	int stepNumber;
	list<StepAndDirection> moves;
};

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
	savedForLater savedParameters;
	int batteryLevel;
	Score simScore;
	Direction lastStep = Direction::Stay;

public:
	Configuration config;
	bool endedSuccessfully = true;
	bool endGameParameter = false;
	void init(char** house_array, int rows, int cols);
	void initForAlgorithm(House _currHouse);
	void freeForAlgorithm();
	void run();
	void updateDirtLevel(_204032031_Point p);
	void printSimulationData();
	void resetSimulatorData();
	void chargeRobot(_204032031_Point p);
	bool endGame();
	void freeSimulationMemory();
	void restartSimulation();
	void setStepNumber(int);
	void setCurrentHouseToOriginal();
	void addMoveToList(Direction currDirection);
	list<StepAndDirection> getMoveList();
	int getStepsNum();
	void setMenu(Menus * _menu);
	Menus* getMenu();
	void runSavedGame(ifstream & savedFile);
	Direction getDirectionFromSavedFile(ifstream &, int *fileStepNumer);
	Direction convertDirLetterToDir(char* letter);
	void runSolution(ifstream& solutionFile);
	void updateEscPressedStatus();
	void setSavedPrintedHouse();
	void savePointToPrintedHouse(_204032031_Point p, char ch);
	void savePrintedCharToSavedArray(int row, int col, char ch);
	void restoreSimulationParameters();
	void resetSavedParameters();
	void runAlgorithm(AbstractAlgorithm * algoritm);
	AbstractSensor& getSensor();
	void makeAlgorithmMove(AbstractAlgorithm*);
	void updateBatteryLevel();
	bool endGameAlgorithm();
	void endGameSimulator(bool someoneWinAlready, int winnerStepNumber);
	int calcScoreFromSim(int position, int winnerSteps);
private:
	void saveSimulationParameters();
	void saveHouse();
	void saveRobot();
	void saveMovesList();
	void printSavedHouseToScreen();
	void restoreHouse();
	void restoreRobot();
	void restoreMovesList();
};

#endif
