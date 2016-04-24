#ifndef _MENUS_H_
#define _MENUS_H_

#include "Simulator.h"
#include "HouseFiles.h"
//#include <string>
//#include <cstdlib>

#define FIRST_ROW_MID_MENU 24
#define FULL_ROW 80

class Simulator;
//class HouseFiles;

class Menus 
{
	HouseFiles files;
	Simulator * sim;
	
public:
	bool midMenuAlive = true;
	Menus() { files.initHouseFiles(); }
	void printFirstMenu();
	void printMidMenu();
	void executeUserChoice(); 
	void executeUserChoiceMidMenu();
	void showInstructions();
	void runGameSimulation(string houseSavedName);
	HouseFiles getHouseFiles(); 
	void printSolutionMidMenu();
	int executeUserChoiceSolutionMenu();
	void runSavedGameSimulation(string houseSavedName);
	void chooseSavedHouse(int houseNum);
	void setSimulator(Simulator * _sim);
	string chooseSavedFromRangeMenu(list<string> & listSavedHouses);
	void midMenuManager();
	void runGameSolution();
};

#endif