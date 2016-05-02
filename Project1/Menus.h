#ifndef _MENUS_H_
#define _MENUS_H_

#include "Simulator.h"
#include "HouseFiles.h"

#define FIRST_ROW_MID_MENU 24
#define FULL_ROW 80

class Menus 
{
	HouseFiles files;
	Simulator * sim;
	
public:
	bool firstMenuAlive = true;
	bool midMenuAlive = true;
	bool repeatSolution = false;
	bool restartHouseFromSolution = false;
	Menus() { files.initHouseFiles(); }
	void printFirstMenu();
	void printMidMenu();
	void executeUserChoice(); 
	void executeUserChoiceMidMenu();
	void showInstructions();
	void runGameSimulation(string houseSavedName);
	void printSolutionMidMenu();
	int executeUserChoiceSolutionMenu();
	void chooseSavedHouse(int houseNum);
	void setSimulator(Simulator * _sim);
	string chooseSavedFromRangeMenu(list<string> & listSavedHouses);
	void midMenuManager();
	void firstMenuManager();
	void runGameSolution();
	void freeMenusMemory();
};

#endif