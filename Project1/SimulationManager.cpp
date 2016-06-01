#include "SimulationManager.h"

void SimulationManager::initSimulators(House currHouse)
{
	simulators = new Simulator[numOfSimulators];
	for (int i = 0; i < numOfSimulators; i++)
	{
		simulators[i].config = config;
		simulators[i].initForAlgorithm(currHouse);
	}
}

void SimulationManager::freeSimulators()
{
	for (int i = 0; i < numOfSimulators; i++)
	{
		
		simulators[i].freeForAlgorithm();
	}
}
Simulator* SimulationManager::simulatorNumber(int num)
{
	return &simulators[num];
}

bool SimulationManager::endSimulation()
{
//	if (winnerStepsNumber != 0)
//	{
//		if (stepNumber == winnerStepsNumber + config.getMaxStepsAfterWinner())
//			return true;;
//	}

	bool allAlgorithmsFinished = true;
	for (int i = 0; i < numOfSimulators; i++)
		if (simulators[i].endGameParameter == false)
			allAlgorithmsFinished = false;

	return allAlgorithmsFinished;

	//if (stepNumber == config.getMaxSteps())
	//	return true;

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

void SimulationManager::printSimulationResults(list<string>algorithmNames)
{
	system("cls");
/*	auto minimumAvgAlgoScore = scoreTableData.cbegin();
	for (auto element : scoreTableData)
	{
		if (element.second.getAverage() < (minimumAvgAlgoScore->second).getAverage())
			minimumAvgAlgoScore = &element;
	}
*/
	list<int> currScoresList;
	int currScoresListSize;
	
	/*
	for (auto currPair : scoreTableData)
	{
		auto currPair = getMinAlgorithmScore();
		cout << "| " << currPair.first;
		
		currScoresList = currPair.second.getScoresList();
		currScoresListSize = currScoresList.size();
		for (int i = 0; i < currScoresListSize; i++)
		{
			cout << "| " << currScoresList.front();
			currScoresList.pop_front();
		}
		cout << "| " << currPair.second.getAverage() << " | ";
		
		cout << endl;
		for (int i = 0; i < currScoresList.size() + 2; i++)
		{
			cout << "---------------------------------";
		}
		cout << endl;
	}
	*/

	while (!scoreTableData.empty())
	{
		auto minScoreAlgorithmName = getMinScoreAlgorithmName();
		cout << "| " << minScoreAlgorithmName;

		currScoresList = scoreTableData[minScoreAlgorithmName].getScoresList();
		currScoresListSize = currScoresList.size();
		for (int i = 0; i < currScoresListSize; i++)
		{
			cout << "| " << currScoresList.front();
			currScoresList.pop_front();
		}
		cout << "| " << scoreTableData[minScoreAlgorithmName].getAverage() << " | ";
		scoreTableData.erase(minScoreAlgorithmName);
		cout << endl << endl;
	}
	cout << endl << endl;

}

void SimulationManager::printErrors()
{
	char hold_the_screen;
	//int i = 0;
	while (!errors.empty())
	{
		//cout << i << endl;
		cout << errors.front() << endl;
		errors.pop_front();
	}
	cout << "Press any key to go back to main menu" << endl;
	cin >> hold_the_screen;
}
void SimulationManager::saveScore(string algoName, int score)
{
	auto a = scoreTableData.find(algoName);
	if (a == scoreTableData.end())
	{
		AlgorithmScore algoScore(score);
		scoreTableData[algoName] = algoScore;
	}
	else
		scoreTableData[algoName].addScore(score);
		
}

void SimulationManager::saveAlgoNameToTable(list<string> algoName)
{
	list<string>::iterator it;
	it = algoName.begin();
	for (int i = 0; i < algoName.size(); i++)
	{
		scoreTableData[it->data()] = AlgorithmScore();
		it++;
	}
}
int SimulationManager::getWinnerStepNumber() {
	return winnerStepsNumber;
}
void SimulationManager::deleteSimFromArray(int indexOfSim) {
	_memccpy(&simulators[indexOfSim], &simulators[indexOfSim + 1], numOfSimulators - indexOfSim, sizeof(Simulator));
}

void SimulationManager::calcScoreTableDataAvgs()
{
	for (auto& element : scoreTableData)
	{
		element.second.calculateAvg();
	}
}

void SimulationManager::resetParametersForNextHouse()
{
	freeSimulators();
	stepNumber = 0;
	winnerStepsNumber = 0;
}

string SimulationManager::getMinScoreAlgorithmName()
{
	string MinScoreAlgorithmName = (*scoreTableData.begin()).first;

	for (auto currPair : scoreTableData)
	{
		if (currPair.second.getAverage() < scoreTableData[MinScoreAlgorithmName].getAverage())
			MinScoreAlgorithmName = currPair.first;
	}
	return MinScoreAlgorithmName;
}