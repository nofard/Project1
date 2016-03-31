#include <windows.h>
#include <iostream>
using namespace std;

#include "Simulator.h"
#include "Menus.h"

int main()
{
	Simulator simulator;
	Menus menu;

	menu.printFirstMenu();
	menu.executeUserChoice(simulator);
}