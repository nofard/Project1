#include <windows.h>
#include <iostream>
using namespace std;

#include "Simulator.h"
#include "Menus.h"

int main()
{
	Simulator simulator;
	Menus* menu = new Menus();
	
	
	menu->printFirstMenu();
	menu->executeUserChoice(simulator);

	delete menu;
}