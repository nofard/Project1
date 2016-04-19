#include <windows.h>
#include <iostream>
using namespace std;

#include "Simulator.h"
#include "Menus.h"

int main()
{
	Simulator* simulator = new Simulator();
	Menus* menu = new Menus();
	


	simulator->setMenu(menu);
	menu->setSimulator(simulator);
	menu->printFirstMenu();
	menu->executeUserChoice();
//	menu->printFirstMenu();
//	menu->executeUserChoice(simulator);
	//delete menu;
}