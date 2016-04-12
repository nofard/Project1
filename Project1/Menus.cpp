#include "Menus.h"
#include <iostream>
using namespace std;

//printFirstMenu: prints to the screen the initial menu.
void Menus::printFirstMenu() {
	system("cls");
	cout << "(1) Start game (2) Start game from specific house (3) Continue from saved game (8) Show instructions (9) Quit game" << endl;


}

//printMidMenu: prints to the screen the "middle" menu, when game is paused(esc pressed).
void Menus::printMidMenu() {
	//system("cls");
	cout << "(1) Continue game (2) Restart game (3) Save this game (4) Show solution (8) Quit to main menu (9) Quit game" << endl;
}

//executeUserChoice: execute the initial menu option that was chosen by the user.
void Menus::executeUserChoice(Simulator &sim) {
	int choice;
	
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		runGameSimulation(sim, 0);
		break;
	case 2:
		cout << "There are now houses from " << files.getMinHouseNumber() << "to " << files.getMaxHouseNumber() << " Please choose or enter 0 to go back" << endl;
		cin >> choice;
		if (choice != 0)
		{
			files.setFileType(0);
			files.setHouseNumberChoice(choice);
			system("cls");
			runGameSimulation(sim, choice);
		}
		else {
			printFirstMenu();
			executeUserChoice(sim);
		}
		break;
	case 3:


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
		//files.saveGameToFile("", "");
		break;
	case 4:

		break;
	case 8:
		system("cls");
		sim.resetSimulatorData();
		printFirstMenu();
		executeUserChoice(sim); 
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

void Menus::runGameSimulation(Simulator &sim, int houseNumber)
{
	int rows = 0, cols = 0;
	char ** temp_house;
	for (int i = 0; i < files.getIntialFilesListLength() && sim.endedSuccessfully; i++) {
		string houseName = files.getHouseNameByIndex(i);
		if (files.convertHouseNameToNumber(houseName) >= houseNumber) 
		{
			temp_house = files.getHouseFromFile(files.getHouseNameByIndex(i), &rows, &cols);
			sim.init(temp_house, rows, cols);
			sim.run();

		}
	}
	if (!sim.endedSuccessfully) {
		printFirstMenu();
		executeUserChoice(sim);
	}
	

}