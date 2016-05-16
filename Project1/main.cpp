#include "Simulator.h"
#include "Menus.h"

int main()
{
	Simulator* simulator = new Simulator();
	Menus* menu = new Menus();
	
	simulator->setMenu(menu);
	menu->setSimulator(simulator);

	if (simulator->config.initConfiguration())
		menu->firstMenuManager();


	menu->freeMenusMemory();
	delete menu;
	delete simulator;
}