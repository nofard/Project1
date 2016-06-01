#include "Menus.h"

//printFirstMenu: prints to the screen the initial menu.
void Menus::printFirstMenu() {
	system("cls");
	cout << "(1) Start game (2) Start game from specific house (3) Continue from saved game (5) Run simulation of all algorithms (8) Show instructions (9) Quit game" << endl;
}

//printMidMenu: prints to the screen the "middle" menu, when game is paused (esc pressed).
void Menus::printMidMenu() {
	//system("cls");
	gotoxy(0, FIRST_ROW_MID_MENU);
	cout << "(1) Continue game (2) Restart game (3) Save this game (4) Show solution (5) Show run of algorithm (8) Quit to main menu (9) Quit game" << endl;
}

//printSolutionMidMenu: prints to the screen the "middle" menu, when solution is paused (esc pressed).
void Menus::printSolutionMidMenu() {
	cout << "(1) Continue showing sol (2) Restart solution (3) Continue game (4) Restart game (8) Quit to main menu" << endl;
}

//executeUserChoice: execute the initial menu option that was chosen by the user.
//(1) Start game (2) Start game from specific house (3) Continue from saved game (8) Show instructions (9) Quit game
void Menus::executeUserChoice() {
	int choice;
	
	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
		files.setFileType(NEW_HOUSE);
		files.setHouseNumberChoice(1);
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
		files.initList(*(files.getSavedHouseFilesList()), "dir / b / O:N | findstr \".house_saved\" > houseFilesNames.txt");
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
	case 5:
		runAllAlgorithms();
		//run all simulations on all houses
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
//(1) Continue game (2) Restart game (3) Save this game (4) Show solution (8) Quit to main menu (9) Quit game 
void Menus::executeUserChoiceMidMenu() {
	int choice;
	string fileName;

//	AbstractAlgorithm* chosenAlgorithm;

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
		
		for (int i = FIRST_ROW_MID_MENU; i <= FIRST_ROW_MID_MENU + 10; i++) {
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
	case 5:
		system("cls");
		sim->restartSimulation();
		chooseAndRunAlgorithm();
		system("cls");
		sim->restoreSimulationParameters();

		break;
	case 8:
		system("cls");
		sim->resetSimulatorData();
		sim->endGameParameter = true;
		midMenuAlive = false;
		break; 
	case 9:
		sim->resetSimulatorData();
		sim->endGameParameter = true;
		midMenuAlive = false;
		firstMenuAlive = false;
		break;
	default:
		break;
	}

}

//executeUserChoiceSolutionMenu: execute the solution menu option that was chosen by the user.
//(1) Continue showing sol (2) Restart solution (3) Continue game (4) Restart game (8) Quit to main menu
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
		//sim->resetSimulatorData();
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
//runGameSimulation: gets house name and run the simulation starting from the given house (new or saved game) until all houses followed
//were completed successfully or one of the houses were failed to be cleaned entirely. 
void Menus::runGameSimulation(string houseSavedName)
{
	int rows = 0, cols = 0;
	char ** temp_house;
	string houseName;
	int maxStepsFromFile;
	char hold_the_screen;

	for (int i = 0; i < files.getIntialFilesListLength() && sim->endedSuccessfully; i++) 
	{
		if (files.getFileType() == SAVED_HOUSE)
		{
			houseName = houseSavedName.substr(START_INDEX_NAME, END_INDEX_NAME) + ".house";
			files.setCurrHouseName(houseName);
			temp_house = files.getHouseFromFile(houseName, &rows, &cols, &maxStepsFromFile);
			sim->config.setMaxSteps(maxStepsFromFile);
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
				temp_house = files.getHouseFromFile(houseName, &rows, &cols, &maxStepsFromFile);
				if (temp_house != nullptr)
				{
					sim->config.setMaxSteps(maxStepsFromFile);
					sim->init(temp_house, rows, cols);
					sim->run();
					if (sim->endedSuccessfully)
					{
						files.saveSolutionToFile(sim->getMoveList(), sim->getStepsNum());
					}
				}

			}
		}
		if (sim->endedSuccessfully)
			sim->resetSimulatorData();
	}
	if (sim->endedSuccessfully)//done all houses and finished succuessfully
	{
		cout << "Well done, you have finished cleaning the last house." << endl;
		cin >> hold_the_screen;
	}
}
//chooseSavedHouse: gets house number chosen by the user from range, check if saved house exists for this user
//and if exists run the simulation from the chosen saved house.
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
		if(chosenSaveHouse != "")
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

//setSimulator: sets the simulator variable.
void Menus::setSimulator(Simulator * _sim)
{
	sim = _sim;
}

//chooseSavedFromRangeMenu: gets a list of specific house saved games, prints a numbered menu of those houses, gets from the user 
//his choice and returns the chosen house.
string Menus::chooseSavedFromRangeMenu(list<string> & currSavedHouses)
{
	list<string>::iterator it;
	int index = 1;
	int choice;

	cout << "Please select a game from the following list or enter 0 to main menu." << endl;
	for (it = currSavedHouses.begin(); it != currSavedHouses.end(); it++)
	{
		cout << "(" << index << ") " << (*it) << endl;
		index++;
	}
	cin >> choice;
	system("cls");
	if (choice == 0)
	{
		sim->resetSimulatorData();
		return "";
	}
	else
	{ 
		
		int i;
		for (i = 0, it = currSavedHouses.begin(); i < choice - 1; i++, it++)
		{
		}
		return (*it);
	}
}
//firstMenuManager: checks if main menu is alive.
void Menus::firstMenuManager()
{
	while (firstMenuAlive)
	{
		sim->endedSuccessfully = true;
		sim->endGameParameter = false;

		if (!restartHouseFromSolution)
		{
		//	sim->resetSimulatorData();
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
//midMenuManager: checks if middle menu needs to be printes and executed
void Menus::midMenuManager()
{

	while (midMenuAlive)
	{
		printMidMenu();
		executeUserChoiceMidMenu();
	}
}
//runGameSolution: run solution of the current house the user is running the game on, if there is no saved solution for this 
//house. a message will be displayed.
void Menus::runGameSolution()
{
	int rows = 0, cols = 0;
	char ** temp_house;
	string houseName;
	int maxStepsFromFile;
	string solutionName;
	char hold_the_screen;

	solutionName = files.getSolutionFromList(files.getHouseNumberChoice());
	if (solutionName == "")
	{
		cout << "Sorry, there isn't a solution for this house" << endl;
		cout << "Press any key to continue" << endl;
		cin >> hold_the_screen;
		system("cls");
	}
	else
	{
		houseName = solutionName.substr(START_INDEX_NAME, END_INDEX_NAME) + ".house";
		files.setCurrHouseName(houseName);
		temp_house = files.getHouseFromFile(houseName, &rows, &cols, &maxStepsFromFile);
		sim->config.setMaxSteps(maxStepsFromFile);
		sim->init(temp_house, rows, cols);


		ifstream solutionFile(solutionName);
		sim->runSolution(solutionFile);
		solutionFile.close();

	}
}
//freeMenusMemory: frees the menus' data members - which is house files object.
void Menus::freeMenusMemory()
{
	files.freeHouseFilesMemory();
}

void Menus::chooseAndRunAlgorithm()
{
	int chosenIndex;
	int i = 0;
	AbstractAlgorithm* chosenAlgorithm;
	AlgorithmRegistrar& registrar = AlgorithmRegistrar::getInstance();


	if (registrar.size() == 0) 
	{
		cout << "Sorry, There are no registred algorithms." << endl;
		sim->endGameParameter = true;
	}
	else
	{
		auto algorithms = registrar.getAlgorithms();
		auto& algorithmNames = registrar.getAlgorithmNames();

		registrar.printAlgorithmsNames();
		cin >> chosenIndex;

		auto algo = algorithms.begin();
		while (i < chosenIndex)
		{
			algo++;
			i++;
		}

		chosenAlgorithm = (*algo).get();
		
		chosenAlgorithm->setSensor(sim->getSensor());
		chosenAlgorithm->setConfiguration(sim->config.convertDataToMap());
		system("cls");
		sim->runAlgorithm(chosenAlgorithm);
	}
}

void Menus::printAlgoritmMidMenu()
{
	gotoxy(0, FIRST_ROW_MID_MENU);
	cout << "(1) Continue game (2) Continue algorithm run" << endl;

}
int Menus::executeUserChoiceAlgorithmMenu()
{
	int choice;

	cin >> choice;
	switch (choice)
	{
	case 1:
		system("cls");
			
		sim->restoreSimulationParameters();
		midMenuAlive = false;
		break;
	case 2:

		break;
	}
	return choice;
}

void Menus::runAllAlgorithms()
{
	AlgorithmRegistrar& registrar = AlgorithmRegistrar::getInstance();
	auto algorithms = registrar.getAlgorithms();
	//registrar.getAlgorithmNames
	int numOfAlgorithms = algorithms.size();
	auto housesNamesList = files.getInitialHouseFilesList();
	House currentHouse;
	AbstractAlgorithm* currentAlgorithm;
	int j;
	
	SimulationManager* simManager = new SimulationManager(sim->config, numOfAlgorithms);
	//Simulator* simulators = new Simulator[algorithms.size()];
	//simManager->saveAlgoNameToTable(registrar.getAlgorithmNames());

	for (int i = 0; i < files.getIntialFilesListLength(); i++)// run on all houses
	{
		currentHouse = files.getHouseFromFile(files.getHouseNameByIndex(*housesNamesList, i));
			
		if (currentHouse.isValidHouse())
		{
			simManager->config.setMaxSteps(currentHouse.getMaxSteps()); //update maxSteps per house
			//init simulators, and connect eash algo to his sensor-->simulator-->house (copy for each algo)
			simManager->initSimulators(currentHouse);
			

			int index = 0;
			
			for (auto& algo : algorithms)
			{
				algo->setSensor(simManager->simulatorNumber(index)->getSensor());
				algo->setConfiguration(sim->config.convertDataToMap());
				index++;
			}
			//-------------------------------------------------------------------------

			//loop of steps
			int position = 1;
			int numOfWinners = 0;
			while(!(simManager->endSimulation()))
			{

				simManager->increaseStepNumber();
				//auto algo = algorithms.begin();
				j = 0;
				//while (j < algorithms.size()) //loop on algorithms
				for(auto& algo : algorithms)
				{
					if (simManager->simulatorNumber(j)->endGameParameter == false) //if currentSimulator didn't finish already
					{
						currentAlgorithm = (algo).get();
						simManager->simulatorNumber(j)->makeAlgorithmMove(currentAlgorithm);
						simManager->simulatorNumber(j)->endGameSimulator(numOfWinners == 0 ? false:true );
						if (simManager->simulatorNumber(j)->endGameParameter == true) //finished
						{
							if (simManager->simulatorNumber(j)->endedSuccessfully == true)// winner
							{
								if(numOfWinners == 0) //first winner
									simManager->setWinnerStepNumber();
								numOfWinners++;
							}

							simManager->saveScore(registrar.getAlgorithmNameByIndex(j),
							simManager->simulatorNumber(j)->calcScoreFromSim(position, simManager->getWinnerStepNumber()));
							//	algorithms.remove(*algo);
							//	simManager->deleteSimFromArray(j);
							//remove simulator and push left others
							//remove algo from list
						}
					}
					//algo++;
					j++;
				}
				position += numOfWinners;
				//numOfAlgorithms = algorithms.size();
			}
			//
			simManager->resetParametersForNextHouse();
			algorithms = registrar.getAlgorithms();
		}		
		else
		{ 
			simManager->addNoteToErrorsList(currentHouse.getHouseName() + ": " + currentHouse.getNote());
		}
	//	simManager->freeSimulatorsMemory();

	}
	auto& algorithmNames = registrar.getAlgorithmNames();
	simManager->calcScoreTableDataAvgs();
	simManager->printSimulationResults(algorithmNames);
	simManager->printErrors();
	
}

void Menus::createHouseCopies(House* houseCopies, House currentHouse, int numOfCopies)
{
	for (int i = 0; i < numOfCopies; i++)
	{
		houseCopies[i] = (currentHouse.createCopyHouse());
	}
}