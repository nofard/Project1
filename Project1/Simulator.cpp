#include "Simulator.h"


//init: initilize simulator data members;
void Simulator::init()
{
	//originalHouse.setHouse(house_example, 20, 79);
	//currHouse.setHouse(house_example, 20, 79);

	Sensor* theRobotSensor = new Sensor();
	theRobotSensor->initSensor(this, &currHouse, originalHouse.getDockingPosition());
	robot.setSensor(*theRobotSensor);
	sensor = theRobotSensor;

	robot.setPosition(originalHouse.getDockingPosition());
	robot.setArrowKeys("wdxas");

	//for all house printing, for debugging
	/*for (int i = 0; i < 24; i++)
	{
	for (int j = 0; j < 80; j++)
	{
	//(j, i);
	//cout << currHouse.getValueFromPoint(j, i);
	//cout.flush();
	Point p; p.setPoint(j, i);
	p.drawToScreenWhenDockingOn(originalHouse.getDockingPosition(), currHouse.getValueFromPoint(j, i));
	}
	}*/
}

void Simulator::init(char** house_array, int rows, int cols)
{
	originalHouse.setHouse(house_array, rows, cols);
	currHouse.setHouse(house_array, rows, cols);

	Sensor* theRobotSensor = new Sensor();
	theRobotSensor->initSensor(this, &currHouse, originalHouse.getDockingPosition());
	robot.setSensor(*theRobotSensor);
	sensor = theRobotSensor;

	robot.setPosition(originalHouse.getDockingPosition());
	robot.setArrowKeys("wdxas");
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
	if (dirtLevel >= 0 && dirtLevel <= 9)
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
			robot.increaseBatteryLevel();
		}
		else if (robot.getBatteryLevel() >= 380) {
			robot.setBatteryLevel(400);
		}
	}
}

//printSimulationData: prints information about the simulation in the buttom of the screen
void Simulator::printSimulationData()
{
	gotoxy(0, 22);
	cout << "Round Number:" << stepNumber;
	gotoxy(18, 22);
	cout << "Total dust:" << currHouse.getOverallDirtLevel() << "  ";
	gotoxy(34, 22);
	cout << "Dust Collected:" << originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel();
	gotoxy(53, 22);
	cout << "Battery:" << robot.getBatteryLevel() << "  ";
	gotoxy(66, 22);
	cout << "Max Steps:" << config.MaxSteps << "  ";
	cout << endl;
}

//run: The main function to run the simulation. get the step from the algorithm until the end of the cleaning process
void Simulator::run()
{
	if (originalHouse.isValidHouse())
	{
		char gameChar = 0;
		Menus menu;
		int defDir = -1;
		do
		{
			if ((robot.step() != Direction::STAY && robot.step() != (Direction)(defDir)) ||
				(robot.isOnDirt() && robot.step() == Direction::STAY))
			{
				stepNumber++;
			}
			if (robot.wasEscPressed)
			{
				robot.wasEscPressed = false;
				menu.printMidMenu();
				menu.executeUserChoiceMidMenu(*this);
			}

			robot.move();
			robot.getPosition().drawToScreenWhenDockingOn(currHouse.getDockingPosition(), '@');
			robot.reduceBatteryLevel();
			chargeRobot(robot.getPosition());
			updateDirtLevel(robot.getPosition());
			sensor->updateSensorInfo(robot.getPosition());
			sensor->revealArea();
			printSimulationData();

			Sleep(100);

		} while (!endGame());

	}
	resetSimulatorData();

}

//endGame: Return true if one of the "end simulator situations" appears, and prints a suitable message to the screen.
bool Simulator::endGame() {

	char hold_the_screen;
	Score robotScore;
	if (currHouse.getOverallDirtLevel() == 0 && (robot.getPosition()).isSame(originalHouse.getDockingPosition()))
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
		return true;
	}
	if (stepNumber >= config.MaxSteps)
	{
		robotScore = Score(10, stepNumber, stepNumber, originalHouse.getOverallDirtLevel(), originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel(),
			(robot.getPosition()).isSame(originalHouse.getDockingPosition()));
		system("cls");
		cout << "You have passed " << config.MaxSteps << " steps, dust collected: " << originalHouse.getOverallDirtLevel() - currHouse.getOverallDirtLevel()
			<< endl;
		cout << "Your score is: " << robotScore.calculateScore() << endl;
		cin >> hold_the_screen;
		endedSuccessfully = false;
		return true;
	}
	return false;
}

void Simulator::freeSimulationMemory()
{
	originalHouse.freeHouseMemory();
	currHouse.freeHouseMemory();
	robot.resetData();
}

void Simulator::restartSimulation()
{
	setCurrentHouseToOriginal();

	robot.setPosition(originalHouse.getDockingPosition());
	robot.setDirection(Direction::STAY);
	robot.setBatteryLevel(config.BatteryCapacity);

	delete sensor;
	Sensor* theRobotSensor = new Sensor();
	theRobotSensor->initSensor(this, &currHouse, originalHouse.getDockingPosition());
	robot.setSensor(*theRobotSensor);
	sensor = theRobotSensor;

	setStepNumber(0);
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