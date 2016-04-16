#include <windows.h>
#include <iostream>
using namespace std;

#include "Simulator.h"
#include "Menus.h"

int main()
{
	Simulator simulator;
	//Menus* menu = new Menus();
	
	simulator.setMenu();
	simulator.getMenu()->printFirstMenu();
	simulator.getMenu()->executeUserChoice(simulator);
//	menu->printFirstMenu();
//	menu->executeUserChoice(simulator);
	//delete menu;
}