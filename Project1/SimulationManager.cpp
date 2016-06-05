#include "SimulationManager.h"
#include <iomanip>


using namespace std;

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

void SimulationManager::addHouseNumber(string houseNumber)
{
	housesNumbers.push_back(houseNumber);
}

void SimulationManager::addNoteToErrorsList(string note)
{
	errors.push_back(note);
}

void SimulationManager::printSimulationResults(list<string>algorithmNames)
{
	system("cls");

	list<int> currScoresList;
	int currScoresListSize;
	
	auto maxScoreAlgorithmName = getMaxScoreAlgorithmName();
	if (!scoreTableData.empty()) 
	{
		currScoresList = scoreTableData[maxScoreAlgorithmName].getScoresList();
		currScoresListSize = currScoresList.size();
		cout << " ";
		for (int i = 0; i < currScoresListSize; i++)
		{
			cout << "----------------------";
		}
		cout << endl;
	}
	printHousesNumbers();

	while (!scoreTableData.empty())
	{
		auto maxScoreAlgorithmName = getMaxScoreAlgorithmName();
		cout << "| " << maxScoreAlgorithmName;

		currScoresList = scoreTableData[maxScoreAlgorithmName].getScoresList();
		currScoresListSize = currScoresList.size();
		for (int i = 0; i < currScoresListSize; i++)
		{
			cout << " | "  << setw(10) << currScoresList.front();
			currScoresList.pop_front();
		}

		cout << " | " << setw(10) << scoreTableData[maxScoreAlgorithmName].getAverage() << " | " << endl;
		cout << " ";
		for (int i = 0; i < currScoresListSize ; i++)
		{
			cout << "----------------------";
		}
		scoreTableData.erase(maxScoreAlgorithmName);
		cout << endl;
	}
	cout << endl << endl;

	printErrors();
}

void SimulationManager::printHousesNumbers()
{	
	cout << "|";
	cout << setw(16);
	cout <<  "| "; //setw
	//cout << setw(10);
	while (!housesNumbers.empty())
	{	
		cout << housesNumbers.front() << setw(10) << "| ";
		housesNumbers.pop_front();
	}
	
	cout << "AVG" << setw(10) << "| " << endl;
}

void SimulationManager::printErrors()
{
	char hold_the_screen;
	//int i = 0;
	cout << "Errors:"<<endl;
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
	auto currAlgoScore = scoreTableData.find(algoName);
	if (currAlgoScore == scoreTableData.end())
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

string SimulationManager::getMaxScoreAlgorithmName()
{
	string MaxScoreAlgorithmName = (*scoreTableData.begin()).first;

	for (auto currPair : scoreTableData)
	{
		if (currPair.second.getAverage() > scoreTableData[MaxScoreAlgorithmName].getAverage())
			MaxScoreAlgorithmName = currPair.first;
	}
	return MaxScoreAlgorithmName;
}