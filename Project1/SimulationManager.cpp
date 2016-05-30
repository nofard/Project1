#include "SimulationManager.h"

void SimulationManager::initSimulators(House currHouse)
{
	simulators = new Simulator[numOfSimulators];
	for (int i = 0; i < numOfSimulators; i++)
	{
		simulators[i].initForAlgorithm(currHouse, config.getBatteryCapacity());
	}
}

Simulator* SimulationManager::simulatorNumber(int num)
{
	return &simulators[num];
}

bool SimulationManager::endSimulation()
{
	if (stepNumber == config.getMaxSteps())
		return true;

	if (winnerStepsNumber != 0)
	{
		if (stepNumber == winnerStepsNumber + config.getMaxStepsAfterWinner())
			return true;;
	}

	return false;
}

void SimulationManager::increaseStepNumber()
{
	stepNumber++;
}
//setWinnerStepNumber: called only when some1 wins, and set only if didnt set already.
void SimulationManager::setWinnerStepNumber()
{
	if (winnerStepsNumber == 0)
	{
		winnerStepsNumber = stepNumber;
	}
		
}

void SimulationManager::addNoteToErrorsList(string note)
{
	errors.push_back(note);
}

void SimulationManager::printSimulationResults()
{
	char hold_the_screen;
	system("cls");

//	for (int i = 0; i < numOfSimulators;)
	int i = 0;
	while (!errors.empty())
	{	
		cout << i << endl;
		cout << errors.front() << endl;
		errors.pop_front();
	}
	cout << "Press any key to go back to main menu" << endl;
	cin >> hold_the_screen;
}