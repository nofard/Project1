#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include "KeyboardRobot.h"
#include "Menus.h"
#include "Score.h"


#define ROBOT_LETTER '@'
#define BUFF_SIZE 1024

struct savedForLater
{
	char printedHouse[MAX_ROWS][MAX_COLS];
	House house;
	KeyboardRobot robot;
	Point sensorPosition;
	int stepNumber;
	list<StepAndDirection> moves;
};

class Menus;
class Sensor;

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
	void setSavedPrintedHouse();
	void savePointToPrintedHouse(Point p, char ch);

	void savePrintedCharToSavedArray(int row, int col, char ch);
	void restoreSimulationParameters();
private:
	void saveSimulationParameters();
	void savePrintedHouseFromScreen();
	void saveHouse();
	void saveRobot();
	void saveMovesList();
	
	void printSavedHouseToScreen();
	void restoreHouse();
	void restoreRobot();
	void restoreMovesList();
};

#endif
