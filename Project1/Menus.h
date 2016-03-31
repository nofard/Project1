#ifndef _MENUS_H_
#define _MENUS_H_

#include "Simulator.h"
#include "io_utils.h"
#include <string>
#include <cstdlib>

class Simulator;

class Menus 
{
	
public:
	void printFirstMenu();
	void printMidMenu();
	void executeUserChoice(Simulator &); 
	void executeUserChoiceMidMenu(Simulator &);
	void showInstructions(Simulator &);
};

#endif