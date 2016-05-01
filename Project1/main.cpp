#include "Simulator.h"
#include "Menus.h"

int main()
{
	Simulator* simulator = new Simulator();
	Menus* menu = new Menus();
	
	simulator->setMenu(menu);
	menu->setSimulator(simulator);

	menu->firstMenuManager();

	//simulator->freeSavedParameters();
	menu->freeMenusMemory();
	delete menu;
	delete simulator;
}