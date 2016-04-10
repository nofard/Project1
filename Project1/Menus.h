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
public:
	Menus() { files.initHouseFiles(); }
	void printFirstMenu();
	void printMidMenu();
	void executeUserChoice(Simulator &); 
	void executeUserChoiceMidMenu(Simulator &);
	void showInstructions(Simulator &);
};

#endif