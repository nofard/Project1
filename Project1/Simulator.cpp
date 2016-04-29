#define _CRT_SECURE_NO_WARNINGS
#include "Simulator.h"


void Simulator::init(char** house_array, int rows, int cols)
{
	config.initDefaultConfiguration();

	originalHouse.setHouse(house_array, rows, cols);
	currHouse.setHouse(house_array, rows, cols);

	Sensor* theRobotSensor = new Sensor();
	theRobotSensor->initSensor(this, &currHouse, originalHouse.getDockingPosition());
	robot.setSensor(*theRobotSensor);
	robot.setBatteryLevel(config.getBatteryCapacity());
	sensor = theRobotSensor;

	robot.setPosition(originalHouse.getDockingPosition());
	robot.setArrowKeys("wdxas");

	endGameParameter = false;
}

void Simulator::resetSimulatorData()
{
	system("cls");
	stepNumber = 0;
	freeSimulationMemory();
	
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
		if (robot.getBatteryLevel() < 380) {
			robot.increaseBatteryLevel(config.getBatteryRachargeRate());
		}
		else if (robot.getBatteryLevel() >= 380) {
			robot.setBatteryLevel(400);
		}
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
	cout << "Battery:" << robot.getBatteryLevel() << "  ";
	gotoxy(66, SIM_DATA_ROW);
	cout << "Max Steps:" << config.getMaxSteps() << "  ";
	cout << endl;
}

//run: The main function to run the simulation. get the step from the algorithm until the end of the cleaning process
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
				sensor->updateSensorInfo(robot.getPosition());
				sensor->revealArea();
				printSimulationData();

				//Sleep(10);
		}
}

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
			sensor->updateSensorInfo(robot.getPosition());
			sensor->revealArea(false);
			printSimulationData();

			Sleep(100);
		}
	}
}

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
	if (currHouse.getOverallDirtLevel() == MIN_DIRT_LEVEL && (robot.getPosition()).isSame(originalHouse.getDockingPosition()))
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

	if (endGameParameter == true)
	{
		endedSuccessfully = false;
		return true;
	}
		
	return false;
}

void Simulator::freeSimulationMemory()
{
	originalHouse.freeHouseMemory();
	currHouse.freeHouseMemory();
	robot.resetData(config.getBatteryConsumptionRate());
	moves.clear();
}

void Simulator::restartSimulation()
{
	setCurrentHouseToOriginal();

	robot.setPosition(originalHouse.getDockingPosition());
	robot.setDirection(Direction::STAY);
	robot.setBatteryLevel(config.getBatteryCapacity());

	delete sensor;
	Sensor* theRobotSensor = new Sensor();
	theRobotSensor->initSensor(this, &currHouse, originalHouse.getDockingPosition());
	robot.setSensor(*theRobotSensor);
	sensor = theRobotSensor;

	setStepNumber(0);
	moves.clear();
}

void Simulator::setStepNumber(int stepNum)
{
	stepNumber = stepNum;
}

void Simulator::setCurrentHouseToOriginal()
{
	currHouse.copyHouseData(originalHouse);
	currHouse.setOverallDirtLevel(originalHouse.getOverallDirtLevel());
}
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
list<StepAndDirection> Simulator::getMoveList() 
{
	return moves;
}

int Simulator::getStepsNum() {
	return stepNumber;
}
void Simulator::printList()
{
	list<StepAndDirection>::iterator it;
	for (it = moves.begin(); it != moves.end(); ++it)
	{
		cout << (*it).dir << " : " << (*it).step << endl;
	}

}

void Simulator::setMenu(Menus * _menu)
{
	menu = _menu;
}

Menus* Simulator::getMenu()
{
	return menu;
}
Direction Simulator::convertDirLetterToDir(char* letter)
{
	switch (letter[0])
	{
	case 'w':
		return Direction::UP;
		break;
	case 'd':
		return Direction::RIGHT;
		break;
	case 'x':
		return Direction::DOWN;
		break;
	case 'a':
		return Direction::LEFT;
		break;
	case 's':
		return Direction::STAY;
		break;

	}
	return (Direction)DEFAULT_DIR;
}

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


void Simulator::savePointToPrintedHouse(Point p, char ch)
{
	savedParameters.printedHouse[p.getY()][p.getX()] = ch;
}

void Simulator::saveSimulationParameters()
{
	saveHouse();
	saveRobot();
	savedParameters.sensorPosition = sensor->getCurrPosition();
	savedParameters.stepNumber = stepNumber;
	saveMovesList();
}


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

void Simulator::saveRobot()
{
	savedParameters.robot.setPosition(robot.getPosition());
	savedParameters.robot.setDirection(Direction::STAY);
	savedParameters.robot.setSensor(*sensor);
	savedParameters.robot.setBatteryLevel(robot.getBatteryLevel());
}

void Simulator::saveMovesList()
{
	list<StepAndDirection>::iterator it;
	for (it = moves.begin(); it != moves.end(); ++it)
	{
		savedParameters.moves.push_back(*it);
	}
}

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

void Simulator::restoreHouse()
{
	currHouse.setRows(savedParameters.house.getRows());
	currHouse.setCols(savedParameters.house.getCols());

	currHouse.setHouseArray(savedParameters.house.getHouse());
	currHouse.copyHouseData(savedParameters.house);
}

void Simulator::restoreRobot()
{
	robot.setPosition(savedParameters.robot.getPosition());
	robot.setDirection(Direction::STAY);
	robot.setBatteryLevel(savedParameters.robot.getBatteryLevel());
	robot.wasEscPressed = false;
}

void Simulator::restoreMovesList()
{
	moves.clear();
	list<StepAndDirection>::iterator it;
	for (it = savedParameters.moves.begin(); it != savedParameters.moves.end(); ++it)
		moves.push_back(*it);

}

void Simulator::savePrintedCharToSavedArray(int row, int col, char ch)
{
	savedParameters.printedHouse[row][col] = ch;
}

void Simulator::freeSavedParameters()
{
	savedParameters.house.freeHouseMemory();
	savedParameters.moves.clear();
}
