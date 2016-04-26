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
//"(1) Start game (2) Start game from specific house (3) Continue from saved game (8) Show instructions (9) Quit game"
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
		cout << "There are now houses from " << files.getMinHouseNumber() << " to " << files.getMaxHouseNumber() << " Please choose or enter 0 to go back" << endl;
		cin >> choice;
		if (choice != 0)
		{
			files.setFileType(NEW_HOUSE);
			files.setHouseNumberChoice(choice);
			system("cls");
			runGameSimulation("dummy");
		}
		break;
	case 3:
		cout << "There are saved houses from " << files.getMinHouseNumber() << " to " << files.getMaxHouseNumber() << " Please choose or enter 0 to go back" << endl;
		cin >> choice;
		if (choice != 0)
		{
			files.setFileType(SAVED_HOUSE);
			files.setHouseNumberChoice(choice);
			system("cls");
			chooseSavedHouse(choice);
		}
		break;
	case 8:
		showInstructions();
		break;
	case 9:
		firstMenuAlive = false;
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
		system("cls");
		sim->restoreSimulationParameters();
		midMenuAlive = false;
		break;
	case 2:
		system("cls");
		sim->restartSimulation();
		midMenuAlive = false;
		//runGameSimulation("dummy");
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
		break;
	case 4:
		do // do 1 time and repeat if user choose 2 in solution menu
		{ 
			system("cls");
			sim->restartSimulation();
			runGameSolution();
		} while (repeatSolution);

		break;
	case 8:
		system("cls");
		sim->endGameParameter = true;
		midMenuAlive = false;
		break; 
	case 9:
		sim->endGameParameter = true;
		midMenuAlive = false;
		firstMenuAlive = false;
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
		break;
	case 3:
		sim->restoreSimulationParameters();
		midMenuAlive = false;
		break;
	case 4:
		system("cls");
		midMenuAlive = false;
		sim->endGameParameter = true;
		restartHouseFromSolution = true;
		break;
	case 8:
		midMenuAlive = false;
		sim->endGameParameter = true;
		break;
	}
	return choice;
}

//showInstructions: prints the instructions of the simulation.
void Menus::showInstructions() {
	int choice;
	system("cls");
	cout << "Welcome to Vacuum Cleaner Robot Simulator" << endl;
	cout << "In order to move the robot use the following keys:" << endl;
	cout << "w - move up" << endl;
	cout << "d - move right" << endl;
	cout << "x - move down" << endl;
	cout << "a - move left" << endl;
	cout << "s - stay" << endl;
	cout << "In any situation the game is freezed, please press any key to continue." << endl << endl;
	cout << "(0) To go back (9) To Quit game" << endl;

	cin >> choice;
	switch (choice)
	{
	case 0:
		system("cls");
		//printFirstMenu();
		//executeUserChoice();
		break;
	case 9:
		firstMenuAlive = false;
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

			i = files.getIndexOfHouseFromList(houseName);
			files.setFileType(NEW_HOUSE);
			sim->run();
		}
		else
		{
			houseName = files.getHouseNameByIndex(*(files.getInitialHouseFilesList()), i);
			if (files.convertHouseNameToNumber(houseName) >= files.getHouseNumberChoice())
			{
				files.setCurrHouseName(houseName);
				files.setHouseNumberChoice(files.convertHouseNameToNumber(houseName));
				temp_house = files.getHouseFromFile(houseName, &rows, &cols);
				sim->init(temp_house, rows, cols);
				sim->run();
				if (sim->endedSuccessfully)
				{
					files.saveSolutionToFile(sim->getMoveList(), sim->getStepsNum());
				}
			}
		}
		//if(sim->endedSuccessfully && i != files.getIntialFilesListLength() -1)//for the last one no reset, its resets in the main
		if (sim->endedSuccessfully)
			sim->resetSimulatorData();
	}
	if (sim->endedSuccessfully)//done all houses and finished succuessfully
	{
		firstMenuAlive = false;
	}
}

void Menus::chooseSavedHouse(int houseNum)
{
	list<string> currSavedHouses;
	list<string> *savedHousesList = files.getSavedHouseFilesList();
	list<string>::iterator it;
	char hold_the_screen;
	string chosenSaveHouse;

	int tempHouseNum;

	for (it = (*savedHousesList).begin(); it != (*savedHousesList).end(); ++it)
	{
		tempHouseNum = ((*it)[0] - '0') * 100 + ((*it)[1] - '0') * 10 + ((*it)[2] - '0');
		if (tempHouseNum == houseNum)
		{
			currSavedHouses.push_back((*it));
		}
	}

	if (currSavedHouses.size() > 1)
	{
		chosenSaveHouse = chooseSavedFromRangeMenu(currSavedHouses);
		runGameSimulation(chosenSaveHouse);
	} 
	else if (currSavedHouses.size() == 1)
	{
		runGameSimulation(currSavedHouses.begin()->data());
	}
	else
	{
		cout << "There is no saved game for this house" << endl;
		cin >> hold_the_screen;
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

void Menus::firstMenuManager()
{
	while (firstMenuAlive)
	{
		sim->endedSuccessfully = true;
		sim->endGameParameter = false;

		if (!restartHouseFromSolution)
		{
			sim->resetSimulatorData();
			printFirstMenu();
			executeUserChoice();
		}
		else
		{
			restartHouseFromSolution = false;
			sim->restartSimulation();
			runGameSimulation("dummy");
		}
	}
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