#ifndef _MENUS_H_
#define _MENUS_H_

#include "Simulator.h"
#include "io_utils.h"
#include "HouseFiles.h"
#include <string>
#include <cstdlib>

class Simulator;
//class HouseFiles;

class Menus 
{
	HouseFiles files;
	Simulator * sim;
	
public:
	Menus() { files.initHouseFiles(); }
	void printFirstMenu();
	void printMidMenu();
	void executeUserChoice(); 
	void executeUserChoiceMidMenu();
	void showInstructions();
	void runGameSimulation(int houseNumber);
	HouseFiles getHouseFiles(); 
	void printSavedMidMenu();
	void executeUserChoiceSavedMenu();
	void runSavedGameSimulation(string houseSavedName);
	void chooseSavedHouse(int houseNum);
	void setSimulator(Simulator * _sim);
	string chooseSavedFromRangeMenu(list<string> & listSavedHouses);
};

#endif