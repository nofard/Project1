#include "Menus.h"
#include <iostream>
using namespace std;

//printFirstMenu: prints to the screen the initial menu.
void Menus::printFirstMenu() {
	system("cls");
	cout << "(1) Start game (8) Show instructions (9) Quit game" << endl;
}

//printMidMenu: prints to the screen the "middle" menu, when game is paused(esc pressed).
void Menus::printMidMenu() {
	//system("cls");
	cout << "(1) Continue game (2) Restart game (3) Quit to main menu (9) Quit game" << endl;
}

//executeUserChoice: execute the initial menu option that was chosen by the user.
void Menus::executeUserChoice(Simulator &sim) {
	int choise;
	cin >> choise;
	switch (choise)
	{
	case 1:
		system("cls");
		sim.init();
		sim.run();
		break;
	case 8:
		showInstructions(sim);
		break;
	case 9:
		exit(0);
		break;

	default:
		break;
	}
}

//executeUserChoiceMidMenu: execute the middle menu option that was chosen by the user.
void Menus::executeUserChoiceMidMenu(Simulator &sim) {
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		gotoxy(0, 23);
		cout << std::string(80, ' ');
		gotoxy(0, 24);
		cout << std::string(1, ' ');
		sim.run();
		break;
	case 2:
		system("cls");
		sim.init();
		sim.resetSimulatorData();
		sim.run();
		break;
	case 3:
		system("cls");
		sim.resetSimulatorData();
		printFirstMenu();
		executeUserChoice(sim); //?
	case 9:
		exit(0);
		break;
	default:
		break;
	}

}

//showInstructions: prints the instructions of the simulation.
void Menus::showInstructions(Simulator &sim) {
	int choise;
	system("cls");
	cout << "Please use the following key \"waxds\" arrows to move the robot around the house" << endl;
	cout << "(0) To go back (9) To Quit game" << endl;

	cin >> choise;
	switch (choise)
	{
	case 0:
		system("cls");
		printFirstMenu();
		executeUserChoice(sim);
		break;
	case 9:
		exit(0);
		break;
	default:
		break;
	}
}