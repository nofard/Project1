#define _CRT_SECURE_NO_WARNINGS
#include "Simulator.h"

//init: gets house array, rows and columns, and init all variables to initial state.
void Simulator::init(char** house_array, int rows, int cols)
{
		originalHouse.setHouse(house_array, rows, cols);
		currHouse.setHouse(house_array, rows, cols);

		Sensor* theRobotSensor = new Sensor();
		theRobotSensor->initSensor(this, &currHouse, originalHouse.getDockingPosition());
		robot.setSensor(*theRobotSensor);
		robot.setBatteryLevel(config.getBatteryCapacity());
		sensor = theRobotSensor;
		batteryLevel = config.getBatteryCapacity();

		robot.setPosition(originalHouse.getDockingPosition());
		robot.setArrowKeys("daxws");

		endGameParameter = false;
}

void Simulator::initForAlgorithm(House _currHouse)
{
	currHouse = _currHouse.createCopyHouse();
	originalHouse = _currHouse.createCopyHouse();
	Sensor* currSensor = new Sensor();
	currSensor->initSensor(this, &currHouse, currHouse.getDockingPosition());
	sensor = currSensor;
	batteryLevel = config.getBatteryCapacity();
	endedSuccessfully = false;

}

void Simulator::freeForAlgorithm()
{
	currHouse.freeHouseMemory();
	originalHouse.freeHouseMemory();
	free(sensor);
}


//resetSimulatorData: resets simulation data, and frees all alloacted memory in the simulation.
void Simulator::resetSimulatorData()
{
	if (currHouse.getHouse() != nullptr)  //check if memory isn't freed already
	{
		system("cls");
		stepNumber = 0;
		freeSimulationMemory();
		resetSavedParameters();
	}
}

//updateDirtLevel: Update dirtLevel at a specifiec point, and reduce overall dirt level in the house
void Simulator::updateDirtLevel(Point p)
{
	int dirtLevel = (int)(currHouse.getValueFromPoint(p) - '0');
	if (dirtLevel >= MIN_DIRT_LEVEL && dirtLevel <= MAX_DIRT_LEVEL)
	{
		currHouse.reduceValueAtPoint(p);
		currHouse.reduceOverallDirtLevel();
	}
}

//chargeRobot: Check if the robot is in the docking station and charge it respectively to configuration data.
void Simulator::chargeRobot(Point p)
{

	if (p.isSame(originalHouse.getDockingPosition())) {
		if (robot.getBatteryLevel() < config.getBatteryCapacity() - config.getBatteryRechargeRate()) {
			robot.increaseBatteryLevel(config.getBatteryRechargeRate());
		}
		else if (robot.getBatteryLevel() >= config.getBatteryCapacity() - config.getBatteryRechargeRate()) {
			robot.setBatteryLevel(config.getBatteryCapacity());
		}
	}
	batteryLevel = robot.getBatteryLevel();
}

void Simulator::updateBatteryLevel()
{
	if (currHouse.getCurrentPosition().isSame(originalHouse.getDockingPosition()))
	{
		if (batteryLevel < config.getBatteryCapacity() - config.getBatteryRechargeRate())
		{
			batteryLevel += config.getBatteryRechargeRate();
		}
		else if (batteryLevel >= config.getBatteryCapacity() - config.getBatteryRechargeRate())
		{
			batteryLevel = config.getBatteryCapacity();
		}
	}
	else
	{
		if (batteryLevel <= config.getBatteryConsumptionRate())
			batteryLevel = 0;
		else
			batteryLevel -= config.getBatteryConsumptionRate();
	}
}

//printSimulationData: prints information about the simulation in the buttom of the screen
void Simulator::printSimulationData()
{
	gotoxy(0, SIM_DATA_ROW);
	cout << "Round Number:" << stepNumber;
	gotoxy(18, SIM_DATA_ROW);
	cout << "Total dust:" << currHouse.getOverallDirtLevel() << "  ";
	gotoxy(34, SIM_DATA_ROW);
	cout << "Dust Collected:" << originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel();
	gotoxy(53, SIM_DATA_ROW);
	cout << "Battery:" << batteryLevel << "  ";
	gotoxy(66, SIM_DATA_ROW);
	cout << "Max Steps:" << config.getMaxSteps() << "  ";
	cout << endl;
}

//run: The main function to run the simulation. Runs the robot until the end of the cleaning process (successful or not)
//or if users choose to quit in ESC menu
void Simulator::run()
{
	if (originalHouse.isValidHouse())
	{
		Direction currDirection;
		do
		{
			currDirection = robot.step();
			stepNumber++;
			addMoveToList(currDirection);
			robot.getPosition().drawToScreenWhenDockingOn(currHouse.getDockingPosition(), ' ');
			robot.move();
			robot.getPosition().drawToScreenWhenDockingOn(currHouse.getDockingPosition(), ROBOT_LETTER);
			robot.reduceBatteryLevel(config.getBatteryConsumptionRate());
			chargeRobot(robot.getPosition());
			updateDirtLevel(robot.getPosition());
			currHouse.setCurrentPosition(robot.getPosition());
			sensor->updateSensorInfo(robot.getPosition());
			sensor->revealArea();
			printSimulationData();

			Sleep(100);

			if (robot.wasEscPressed)
			{
				robot.wasEscPressed = false;
				saveSimulationParameters();
				menu->midMenuAlive = true;
				menu->midMenuManager();
			}

 		} while (!endGame());
	}
}

//runSavedGame: gets the saved file object, and runs the robot according to the moves written in the saved file
void Simulator::runSavedGame(ifstream & savedFile)
{
		Direction currDirection;
		int stepNumberFromFile;
		char buff[BUFF_SIZE];

		savedFile.getline(buff, BUFF_SIZE - 1);
		int totalNumSteps = atoi(buff);

		currDirection = getDirectionFromSavedFile(savedFile, &stepNumberFromFile);
		for (int i = 0; i < totalNumSteps ; i++) 
		{
			stepNumber++;
			if (stepNumber == stepNumberFromFile)
			{
				robot.setDirection(currDirection);
				if(!savedFile.eof())
					currDirection = getDirectionFromSavedFile(savedFile, &stepNumberFromFile);
			}
			if(currDirection != (Direction)DEFAULT_DIR) //check for last row in the file
				addMoveToList(currDirection);

				robot.move();
				robot.getPosition().drawToScreenWhenDockingOn(currHouse.getDockingPosition(), ROBOT_LETTER);
				robot.reduceBatteryLevel(config.getBatteryConsumptionRate());
				chargeRobot(robot.getPosition());
				updateDirtLevel(robot.getPosition());
				currHouse.setCurrentPosition(robot.getPosition());
				sensor->updateSensorInfo(robot.getPosition());
				sensor->revealArea();
				printSimulationData();

				//Sleep(10);
		}
}
//runSolution: gets the saved solution file object, and runs the robot according to the moves written in the saved file until end of 
//file or if users choose to quit or go back to game in ESC menu.
void Simulator::runSolution(ifstream& solutionFile)
{
	Direction currDirection;
	int stepNumberFromFile;
	char buff[BUFF_SIZE];
	int solMenuUserChoice = 1;

	solutionFile.getline(buff, BUFF_SIZE - 1);
	int totalNumSteps = atoi(buff);

	currDirection = getDirectionFromSavedFile(solutionFile, &stepNumberFromFile);
	for (int i = 0; i < totalNumSteps && (solMenuUserChoice == 1 || solMenuUserChoice == 2) ; i++)
	{
		updateEscPressedStatus();
		if (robot.wasEscPressed)
		{
			robot.wasEscPressed = false;
			menu->printSolutionMidMenu();
			solMenuUserChoice = menu->executeUserChoiceSolutionMenu();
		}

		if (solMenuUserChoice == 2)
			menu->repeatSolution = true;
		else
			menu->repeatSolution = false;

		if(solMenuUserChoice == 1)
		{
			stepNumber++;
			if (stepNumber == stepNumberFromFile)
			{
				robot.setDirection(currDirection);
				if (!solutionFile.eof())
					currDirection = getDirectionFromSavedFile(solutionFile, &stepNumberFromFile);
			}

			if (currDirection != (Direction)DEFAULT_DIR) //check for last row in the file
				addMoveToList(currDirection);

			robot.move();
			robot.getPosition().drawToScreenWhenDockingOn(currHouse.getDockingPosition(), ROBOT_LETTER);
			robot.reduceBatteryLevel(config.getBatteryConsumptionRate());
			chargeRobot(robot.getPosition());
			updateDirtLevel(robot.getPosition());
			currHouse.setCurrentPosition(robot.getPosition());
			sensor->updateSensorInfo(robot.getPosition());
			sensor->revealArea(false);
			printSimulationData();

			Sleep(100);
		}
	}
}
//getDirectionFromSavedFile: gets saved file object and steps number as output variable, and parse the written format to a direction
//and returns the direction written in the file
Direction Simulator::getDirectionFromSavedFile(ifstream & savedFile, int * stepNum)
{
	//const int buff_size = 1024;
	char buff[BUFF_SIZE];
	char * token;

	savedFile.getline(buff, BUFF_SIZE - 1);
	if (strcmp(buff, ""))
	{
		token = strtok(buff, ":");
		*stepNum = atoi(token);
		token = strtok(NULL, " ");
		return convertDirLetterToDir(token);
	}
	else
	{
		return (Direction)DEFAULT_DIR;
	}

}

//endGame: Return true if one of the "end simulator situations" appears, and prints a suitable message to the screen.
bool Simulator::endGame() {

	char hold_the_screen;
	Score robotScore;

	if (currHouse.getOverallDirtLevel() == MIN_DIRT_LEVEL && (robot.getPosition()).isSame(originalHouse.getDockingPosition()) && !endGameParameter)
	{
		robotScore = Score(1, stepNumber, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
			(robot.getPosition()).isSame(originalHouse.getDockingPosition()));
		system("cls");
		cout << "Congratulations! You have cleared all dust in " << stepNumber << " steps!!!" << endl;
		cout << "Your score is: " << robotScore.calculateScore() << endl;
		endedSuccessfully = true;

		cin >> hold_the_screen;
		return true;
	}
	if (robot.getBatteryLevel() == 0 && !(robot.getPosition()).isSame(originalHouse.getDockingPosition()))
	{
		robotScore = Score(10, stepNumber, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
			(robot.getPosition()).isSame(originalHouse.getDockingPosition()));
		cout << "Robot is ran out of battery power! Ending game." << endl;
		cout << "Your score is: " << robotScore.calculateScore() << endl;
		cin >> hold_the_screen;
		endedSuccessfully = false;
		menu->firstMenuAlive = false;
		return true;
	}
	if (stepNumber >= config.getMaxSteps())
	{
		robotScore = Score(10, stepNumber, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
			(robot.getPosition()).isSame(originalHouse.getDockingPosition()));
		system("cls");
		cout << "You have reached the maximum steps allowed in this house: " << config.getMaxSteps() << endl;
		cout << "Dust collected: " << originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel() << endl;
		cout << "Your score is: " << robotScore.calculateScore() << endl;
		cin >> hold_the_screen;
		endedSuccessfully = false;
		menu->firstMenuAlive = false;
		return true;
	}

	if (endGameParameter == true) //due to '9' choice (=Quit game) in menus etc.
	{
		endedSuccessfully = false;
		return true;
	}
		
	return false;
}

//freeSimulationMemory: frees the simulation's data members - which are house arrays, reset robot's data and clears moves list.
void Simulator::freeSimulationMemory()
{
	originalHouse.freeHouseMemory();
	currHouse.freeHouseMemory();
	robot.resetData(config.getBatteryConsumptionRate());
	moves.clear();
}
//restartSimulation: restart simulation data to initial state without freeing the already allocated memory.
void Simulator::restartSimulation()
{
	setCurrentHouseToOriginal();

	robot.setPosition(originalHouse.getDockingPosition());
	robot.setDirection(Direction::Stay);
	robot.setBatteryLevel(config.getBatteryCapacity());

	delete sensor;
	Sensor* theRobotSensor = new Sensor();
	theRobotSensor->initSensor(this, &currHouse, originalHouse.getDockingPosition());
	robot.setSensor(*theRobotSensor);
	sensor = theRobotSensor;
	batteryLevel = config.getBatteryCapacity();

	setStepNumber(0);
	moves.clear();
}

void Simulator::setStepNumber(int stepNum)
{
	stepNumber = stepNum;
}
//setCurrentHouseToOriginal: sets current house data to match original house data.
void Simulator::setCurrentHouseToOriginal()
{
	currHouse.copyHouseData(originalHouse);
	currHouse.setOverallDirtLevel(originalHouse.getOverallDirtLevel());
}
//addMoveToList: gets a direction, checks if list of moves last element is different from current direction, if so, adds to the list
//this direction and the current step number.
void Simulator::addMoveToList(Direction currDirection)
{
	StepAndDirection currStepAndDir = { stepNumber, (int)currDirection };
	if (!moves.empty()) 
	{
		if ((Direction)moves.back().dir != currDirection)
		{
			moves.push_back(currStepAndDir);
		}
	}
	else 
	{
		moves.push_back(currStepAndDir);
	}
}
//getMoveList: returns the moves list.
list<StepAndDirection> Simulator::getMoveList() 
{
	return moves;
}

//getStepsNum: get stepNumber.
int Simulator::getStepsNum() {
	return stepNumber;
}

//setMenu: set menu pointer.
void Simulator::setMenu(Menus * _menu)
{
	menu = _menu;
}

//getMenu: return menu pointer.
Menus* Simulator::getMenu()
{
	return menu;
}
//convertDirLetterToDir: gets a direction letter and returns the suited direction.
Direction Simulator::convertDirLetterToDir(char* letter)
{
	switch (letter[0])
	{
	case 'w':
		return Direction::North;
		break;
	case 'd':
		return Direction::East;
		break;
	case 'x':
		return Direction::South;
		break;
	case 'a':
		return Direction::West;
		break;
	case 's':
		return Direction::Stay;
		break;

	}
	return (Direction)DEFAULT_DIR;
}
//updateEscPressedStatus: "listens" to users input and checks if it's the ESC key, if so, updates the wasEscPressed variable.
void Simulator::updateEscPressedStatus()
{
	int keyPressed = 0;

	if (_kbhit())
	{
		keyPressed = _getch();
		if (keyPressed == ESC_KEY)
		{
			robot.wasEscPressed = true;
		}
	}
}
//setSavedPrintedHouse: sets the printed house from saved parameters to contain white spaces
void Simulator::setSavedPrintedHouse()
{
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			savedParameters.printedHouse[i][j] = ' ';
		}
	}
}
//savePointToPrintedHouse: gets point and char, and saves to the suited place in the saved for later array the char given
void Simulator::savePointToPrintedHouse(Point p, char ch)
{
	savedParameters.printedHouse[p.getY()][p.getX()] = ch;
}

//saveSimulationParameters: saves all current simulation data to configured struct.
void Simulator::saveSimulationParameters()
{
	saveHouse();
	saveRobot();
	savedParameters.sensorPosition = sensor->getCurrPosition();
	savedParameters.stepNumber = stepNumber;
	saveMovesList();
}
//saveHouse: saves current house to new allocated house variable under saved for later struct.
void Simulator::saveHouse()
{
	int rows = currHouse.getRows();
	int cols = currHouse.getCols();

	//allocation:
	char** savedHouseArray = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		savedHouseArray[i] = new char[cols];
		for (int j = 0; j < cols; j++)
		{
		}
	}

	savedParameters.house.setHouseArray(savedHouseArray);
	savedParameters.house.copyHouseData(currHouse);
}
//saveRobot: saves all current robot data to robot variable under saved for later struct
void Simulator::saveRobot()
{
	savedParameters.robot.setPosition(robot.getPosition());
	savedParameters.robot.setDirection(Direction::Stay);
	savedParameters.robot.setSensor(*sensor);
	savedParameters.robot.setBatteryLevel(robot.getBatteryLevel());
}
//saveMovesList: saves moves list to a variable under saved for later struct
void Simulator::saveMovesList()
{
	list<StepAndDirection>::iterator it;
	for (it = moves.begin(); it != moves.end(); ++it)
	{
		savedParameters.moves.push_back(*it);
	}
}
//restoreSimulationParameters: restore all saved simulation parameter from the saved for later struct to the current running simulation
void Simulator::restoreSimulationParameters()
{
	printSavedHouseToScreen();
	restoreHouse();
	restoreRobot();
	sensor->setCurrPosition(savedParameters.sensorPosition);
	sensor->setHouse(&currHouse);
	stepNumber = savedParameters.stepNumber;
	restoreMovesList();

}
//printSavedHouseToScreen: prints the saved for later array to the screen
void Simulator::printSavedHouseToScreen()
{
	Point currPoint;
	system("cls");
	gotoxy(0, 0);

	for (int i = 0; i < currHouse.getRows(); i++)
	{
		for (int j = 0; j < currHouse.getCols(); j++)
		{
			currPoint.setPoint(j, i);
			if (savedParameters.printedHouse[i][j] == NULL)
				currPoint.drawToScreenWhenDockingOn(currHouse.getDockingPosition(), ' ');
			else
				currPoint.drawToScreenWhenDockingOn(currHouse.getDockingPosition(), savedParameters.printedHouse[i][j]);
				
		}
		cout << endl;
	}
}
//restoreHouse: sets the current house to be the saved for later.
void Simulator::restoreHouse()
{
	currHouse.setRows(savedParameters.house.getRows());
	currHouse.setCols(savedParameters.house.getCols());

	currHouse.setHouseArray(savedParameters.house.getHouse());
	currHouse.copyHouseData(savedParameters.house);
}
//restoreRobot: sets the current robot to be the saved for later robot. 
void Simulator::restoreRobot()
{
	robot.setPosition(savedParameters.robot.getPosition());
	robot.setDirection(Direction::Stay);
	robot.setBatteryLevel(savedParameters.robot.getBatteryLevel());
	robot.wasEscPressed = false;
}
//restoreMovesList: sets the moves list to be the saved for later moves list.
void Simulator::restoreMovesList()
{
	moves.clear();
	list<StepAndDirection>::iterator it;
	for (it = savedParameters.moves.begin(); it != savedParameters.moves.end(); ++it)
		moves.push_back(*it);

}
//savePrintedCharToSavedArray: gets row, col and char, and saves to the suited place in the saved for later array the char given
void Simulator::savePrintedCharToSavedArray(int row, int col, char ch)
{
	savedParameters.printedHouse[row][col] = ch;
}
//resetSavedParameters: reset savedParameters struct.
void Simulator::resetSavedParameters()
{
	savedParameters.moves.clear();
	for (int i = 0; i < MAX_ROWS; i++)
		for (int j = 0; j < MAX_COLS; j++)
			savedParameters.printedHouse[i][j] = ' ';
}

void Simulator::runAlgorithm(AbstractAlgorithm * algoritm)
{
	static Direction currDirection = Direction::Stay;
	int midAlgoChoice = 0;

	do
	{
		currDirection = algoritm->step(currDirection);
		stepNumber++;
		
		sensor->getCurrPosition().drawToScreenWhenDockingOn(currHouse.getDockingPosition(), ' ');
		sensor->getCurrPosition().move(currDirection);
		sensor->getCurrPosition().drawToScreenWhenDockingOn(currHouse.getDockingPosition(), ROBOT_LETTER);
		updateBatteryLevel();
		//algoritm->reduceBatteryLevel();
	//	algoritm->chargeBattery(sensor->getCurrPosition(), currHouse.getDockingPosition());
		updateDirtLevel(sensor->getCurrPosition());
		currHouse.setCurrentPosition(sensor->getCurrPosition());
		sensor->updateSensorInfo();
		sensor->revealArea(false);
		printSimulationData();


		Sleep(100);

		updateEscPressedStatus();
		if (robot.wasEscPressed)
		{
			robot.wasEscPressed = false;
			menu->printAlgoritmMidMenu();
			midAlgoChoice = menu->executeUserChoiceAlgorithmMenu();
		}


	} while ((!endGameAlgorithm()) && (midAlgoChoice != 1));
}

AbstractSensor& Simulator::getSensor()
{
	return *sensor;
}

void Simulator::makeAlgorithmMove(AbstractAlgorithm* currentAlgorithm)
{
	static Direction currDirection = Direction::Stay;
	stepNumber++;
	currDirection = currentAlgorithm->step(currDirection);
	currHouse.getCurrentPosition().move(currDirection);
	updateBatteryLevel();
	updateDirtLevel(currHouse.getCurrentPosition());

}

void Simulator::endGameSimulator()
{
	if (currHouse.getOverallDirtLevel() == MIN_DIRT_LEVEL && (currHouse.getCurrentPosition().isSame(currHouse.getDockingPosition())))
	{
		endedSuccessfully = true;
		endGameParameter = true;
	}
	if (batteryLevel == 0 && !(currHouse.getCurrentPosition().isSame(currHouse.getDockingPosition())))
	{
		endGameParameter = true;
	}
	if (stepNumber >= config.getMaxSteps())
	{
		endGameParameter = true;
	}
}


bool Simulator::endGameAlgorithm()
{
	char hold_the_screen;
	Score algoScore;

	if (currHouse.getOverallDirtLevel() == MIN_DIRT_LEVEL && (sensor->getCurrPosition()).isSame(originalHouse.getDockingPosition()) && !endGameParameter)
	{
		algoScore = Score(1, stepNumber, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
			(sensor->getCurrPosition()).isSame(originalHouse.getDockingPosition()));
		system("cls");
		cout << "Congratulations! You have cleared all dust in " << stepNumber << " steps!!!" << endl;
		cout << "Your score is: " << algoScore.calculateScore() << endl;
		endedSuccessfully = true;

		cin >> hold_the_screen;
		return true;
	} 
	if (batteryLevel == 0 && !(sensor->getCurrPosition()).isSame(originalHouse.getDockingPosition()))
	{
		algoScore = Score(10, stepNumber, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
			(sensor->getCurrPosition()).isSame(originalHouse.getDockingPosition()));
		cout << "Robot is ran out of battery power! Ending game." << endl;
		cout << "Your score is: " << algoScore.calculateScore() << endl;
		cin >> hold_the_screen;
		endedSuccessfully = false;
		menu->firstMenuAlive = false;
		return true;
	}
	if (stepNumber >= config.getMaxSteps())
	{
		algoScore = Score(10, stepNumber, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
			(sensor->getCurrPosition()).isSame(originalHouse.getDockingPosition()));
		system("cls");
		cout << "You have reached the maximum steps allowed in this house: " << config.getMaxSteps() << endl;
		cout << "Dust collected: " << originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel() << endl;
		cout << "Your score is: " << algoScore.calculateScore() << endl;
		cin >> hold_the_screen;
		endedSuccessfully = false;
		menu->firstMenuAlive = false;
		return true;
	}

	if (endGameParameter == true) //due to '9' choice (=Quit game) in menus etc.
	{
		endedSuccessfully = false;
		return true;
	}

	return false;
}
int Simulator::calcScoreFromSim(int position, int winnerSteps) {
	Score score = Score(position, winnerSteps, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
		(currHouse.getCurrentPosition()).isSame(currHouse.getDockingPosition()));

	return score.calculateScore();
}