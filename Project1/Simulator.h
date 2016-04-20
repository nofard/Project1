#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include "io_utils.h"
#include "KeyboardRobot.h"
#include "House.h"
#include "Sensor.h"
#include "Menus.h"
#include "Score.h"


#define ROBOT_LETTER '@'
#define BUFF_SIZE 1024

struct savedForLater
{
	char** printedHouse;
	House house;
	KeyboardRobot robot;
	Point sensorPosition;
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

public:
	bool endedSuccessfully = true;
	void init();
	void init(char** house_array, int rows, int cols);
	void run();
	void updateDirtLevel(Point p);
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
	void setMenu(Menus * _menu);
	Menus* getMenu();
	void runSavedGame(ifstream & savedFile);
	Direction getDirectionFromSavedFile(ifstream &, int *fileStepNumer);
	Direction convertDirLetterToDir(char* letter);
	void runSolution(ifstream& solutionFile);
	void updateEscPressedStatus();
	void setSavedPrintedHouse(int rows, int cols);
	void savePointToPrintedHouse(Point p, char ch);
private:
	void saveSimulationParameters();
	void savePrintedHouseFromScreen();
	void saveHouse();
	void saveRobot();
	void saveMovesList();

};

#endif
