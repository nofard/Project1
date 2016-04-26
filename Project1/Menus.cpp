#include "Menus.h"

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

void Menus::printSolutionMidMenu() {
	cout << "(1) Continue showing sol (2) Restart solution (3) Continue game (4) Restart game (8) Quit to main menu" << endl;
}

//executeUserChoice: execute the initial menu option that was chosen by the user.
void Menus::executeUserChoice() {
	int choice;
	
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		files.setFileType(NEW_HOUSE);
		runGameSimulation("dummy");
		break;
	case 2:
		cout << "There are now houses from " << files.getMinHouseNumber() << "to " << files.getMaxHouseNumber() << " Please choose or enter 0 to go back" << endl;
		cin >> choice;
		if (choice != 0)
		{
			files.setFileType(NEW_HOUSE);
			files.setHouseNumberChoice(choice);
			system("cls");
			runGameSimulation("dummy");
		}
		else {
			printFirstMenu();
			executeUserChoice();
		}
		break;
	case 3:
		cout << "There are saved houses from " << files.getMinHouseNumber() << "to " << files.getMaxHouseNumber() << " Please choose or enter 0 to go back" << endl;
		cin >> choice;
		if (choice != 0)
		{
			files.setFileType(SAVED_HOUSE);
			files.setHouseNumberChoice(choice);
			system("cls");
			chooseSavedHouse(choice);
			//runSavedGameSimulation(sim, choice);
		}
		else {
			printFirstMenu();
			executeUserChoice();
		}

		break;
	case 8:
		showInstructions();
		break;
	case 9:
		exit(0);
		break;

	default:
		break;
	}
}

//executeUserChoiceMidMenu: execute the middle menu option that was chosen by the user.
//"(1) Continue game (2) Restart game (3) Save this game (4) Show solution (8) Quit to main menu (9) Quit game" 
void Menus::executeUserChoiceMidMenu() {
	int choice;
	string fileName;
	cin >> choice;
	switch (choice)
	{
	case 1: 
		gotoxy(0, FIRST_ROW_MID_MENU);
		cout << string(FULL_ROW, ' ');
		gotoxy(0, FIRST_ROW_MID_MENU + 1);
		cout << string(FULL_ROW, ' ');
		gotoxy(0, FIRST_ROW_MID_MENU + 2);
		cout << string(FULL_ROW, ' ');
		midMenuAlive = false;
		break;
	case 2:
		system("cls");
		sim->restartSimulation();
		runGameSimulation("dummy");
		break;
	case 3:
		cout << "Please enter file name" << endl;
		cin >> fileName;
		files.saveGameToFile(fileName, sim->getMoveList(), sim->getStepsNum());
		
		for (int i = FIRST_ROW_MID_MENU; i <= FIRST_ROW_MID_MENU + 7; i++) {
			gotoxy(0, i);
			cout << string(FULL_ROW, ' ');
		}
		
		gotoxy(0, FIRST_ROW_MID_MENU);
		printMidMenu();
		executeUserChoiceMidMenu();
		break;
	case 4:
		system("cls");
		sim->restartSimulation();
		runGameSolution();
		

		break;
	case 8:
		system("cls");
		sim->resetSimulatorData();
		printFirstMenu();
		executeUserChoice(); 
	case 9:
		exit(0);
		break;
	default:
		break;
	}

}

//executeUserChoiceSolutionMenu: execute the solution menu option that was chosen by the user.
//"(1) Continue showing sol (2) Restart solution (3) Continue game (4) Restart game (8) Quit to main menu" 
int Menus::executeUserChoiceSolutionMenu() 
{
	string currHouseName;
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		gotoxy(0, FIRST_ROW_MID_MENU);
		cout << string(FULL_ROW, ' ');
		gotoxy(0, FIRST_ROW_MID_MENU + 1);
		cout << string(FULL_ROW, ' ');
		gotoxy(0, FIRST_ROW_MID_MENU + 2);
		cout << string(FULL_ROW, ' ');

		break;
	case 2:
		system("cls");
		sim->restartSimulation();
		runGameSolution();
		break;
	case 3:
		sim->restoreSimulationParameters();
		midMenuAlive = false;
		//runGameSimulation(files.getCurrHouseName());
		break;
	case 4:
		system("cls");
		currHouseName = files.getCurrHouseName();
		sim->restartSimulation();
		runGameSimulation(currHouseName);
		break;
	case 8:
		//aviv will change his beloved flag
		break;
	}
	return choice;
}

//showInstructions: prints the instructions of the simulation.
void Menus::showInstructions() {
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
		executeUserChoice();
		break;
	case 9:
		exit(0);
		break;
	default:
		break;
	}
}

void Menus::runGameSimulation(string houseSavedName)
{
	int rows = 0, cols = 0;
	char ** temp_house;
	string houseName;

	for (int i = 0; i < files.getIntialFilesListLength() && sim->endedSuccessfully; i++) 
	{
		if (files.getFileType() == SAVED_HOUSE)
		{
			houseName = houseSavedName.substr(START_INDEX_NAME, END_INDEX_NAME) + ".house";
			files.setCurrHouseName(houseName);
			temp_house = files.getHouseFromFile(houseName, &rows, &cols);
			sim->init(temp_house, rows, cols);

			ifstream savedMoves(houseSavedName);
			sim->runSavedGame(savedMoves);
			savedMoves.close();

			i = files.getIndexOfHouseFromList(houseName) + 1;
			files.setFileType(NEW_HOUSE);
			sim->run();
		}
		else
		{
			houseName = files.getHouseNameByIndex(*(files.getInitialHouseFilesList()), i);
			if (files.convertHouseNameToNumber(houseName) >= files.getHouseNumberChoice())
			{
				files.setCurrHouseName(houseName);
				files.setHouseNumberChoice((files.getHouseNumberChoice()) + 1);
				//files.setHouseNumberChoice((files.getHouseNumberChoice()));
				temp_house = files.getHouseFromFile(houseName, &rows, &cols);
				sim->init(temp_house, rows, cols);
				sim->run();
				if (sim->endedSuccessfully)
				{
					files.saveSolutionToFile(sim->getMoveList(), sim->getStepsNum());
				}
			}
		}

		sim->resetSimulatorData();
	}
	if (!sim->endedSuccessfully) {
		sim->endedSuccessfully = true;
		printFirstMenu();
		executeUserChoice();
	}
}
/*
void Menus::runSavedGameSimulation(string houseSavedName)
{
	int rows = 0, cols = 0;
	char ** temp_house;
	string houseName;

	houseName = houseSavedName.substr(0, 3) + ".house";

	files.setCurrHouseName(houseName);
	temp_house = files.getHouseFromFile(houseName, &rows, &cols);
	sim->init(temp_house, rows, cols);

	ifstream savedMoves(houseSavedName);
	sim->runSavedGame(savedMoves);

	savedMoves.close();
}
*/

void Menus::chooseSavedHouse(int houseNum)
{
	list<string> currSavedHouses;
	list<string> *savedHousesList = files.getSavedHouseFilesList();
	list<string>::iterator it;
	char hold_the_screen;
	string chosenSaveHouse;
	//string tempStr;
	int tempNum;

	for (it = (*savedHousesList).begin(); it != (*savedHousesList).end(); ++it)
	{
		tempNum = ((*it)[0] - '0') * 100 + ((*it)[1] - '0') * 10 + ((*it)[2] - '0');
		if (tempNum == houseNum)
		{
			currSavedHouses.push_back((*it));
		}
	}

	if (currSavedHouses.size() > 1)
	{
		chosenSaveHouse = chooseSavedFromRangeMenu(currSavedHouses);
		//runSavedGameSimulation(chosenSaveHouse);
		runGameSimulation(chosenSaveHouse);
	} 
	else if (currSavedHouses.size() == 1)
	{
		//runSavedGameSimulation(currSavedHouses.begin()->data());
		runGameSimulation(currSavedHouses.begin()->data());
	}
	else
	{
		cout << "There is no saved game for this house" << endl;
		cin >> hold_the_screen;
		printFirstMenu();
		executeUserChoice();
	}
}
void Menus::setSimulator(Simulator * _sim)
{
	sim = _sim;
}
string Menus::chooseSavedFromRangeMenu(list<string> & currSavedHouses)
{
	list<string>::iterator it;
	int index = 1;
	int choice;

	cout << "Please select a game from the following list:" << endl;
	for (it = currSavedHouses.begin(); it != currSavedHouses.end(); it++)
	{
		cout << "(" << index << ") " << (*it) << endl;
		index++;
	}
	cin >> choice;
	system("cls");
	int i;
	for (i = 0, it = currSavedHouses.begin(); i < choice - 1; i++, it++)
	{
	}
	return (*it);
}

void Menus::midMenuManager()
{

	while (midMenuAlive)
	{
		printMidMenu();
		executeUserChoiceMidMenu();
	}


}

void Menus::runGameSolution()
{
	int rows = 0, cols = 0;
	char ** temp_house;
	string houseName;
	string solutionName;

	solutionName = files.getSolutionFromList(files.getHouseNumberChoice());
	if (solutionName == "")
	{
		cout << "Sorry, there isn't a solution for this house" << endl;
	}
	else
	{
		houseName = solutionName.substr(START_INDEX_NAME, END_INDEX_NAME) + ".house";
		files.setCurrHouseName(houseName);
		temp_house = files.getHouseFromFile(houseName, &rows, &cols);
		sim->init(temp_house, rows, cols);


		ifstream solutionFile(solutionName);
		sim->runSolution(solutionFile);
		solutionFile.close();

	}
}