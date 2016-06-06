#include "SimulationManager.h"
#include <iomanip>


using namespace std;

//initSimulators: gets the current house and initialize the simulators array with house and configuration
void SimulationManager::initSimulators(House currHouse)
{
	simulators = new Simulator[numOfSimulators];
	for (int i = 0; i < numOfSimulators; i++)
	{
		simulators[i].config = config;
		simulators[i].initForAlgorithm(currHouse);
	}
}
//freeSimulators: frees all simulators from simulators array
void SimulationManager::freeSimulators()
{
	for (int i = 0; i < numOfSimulators; i++)
	{
		
		simulators[i].freeForAlgorithm();
	}
}
//getSimulatorByInd: gets index and returns simulator by index
Simulator* SimulationManager::getSimulatorByInd(int index)
{
	return &simulators[index];
}
//endSimulation: checks if all algorithms were finished, if so, returns true
bool SimulationManager::endSimulation()
{
	bool allAlgorithmsFinished = true;
	for (int i = 0; i < numOfSimulators; i++)
		if (simulators[i].endGameParameter == false)
			allAlgorithmsFinished = false;

	return allAlgorithmsFinished;
}
//increaseStepNumber: increase step number variable
void SimulationManager::increaseStepNumber()
{
	stepNumber++;
}
//setWinnerStepNumber: called only when someone wins, and set only if didnt set already.
void SimulationManager::setWinnerStepNumber()
{
	if (winnerStepsNumber == 0)
	{
		winnerStepsNumber = stepNumber;
	}
		
}
//addHouseNumber: gets house number and adds it to list of house numbers
void SimulationManager::addHouseNumber(string houseNumber)
{
	housesNumbers.push_back(houseNumber);
}
//addNoteToErrorsList: gets note and adds it to nodes list
void SimulationManager::addNoteToErrorsList(string note)
{
	errors.push_back(note);
}
//printSimulationResults: gets list of algorithms names and prints algorithms results table
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
//printHousesNumbers: prints houses numbers in a table format
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
//printErrors: prints the errors from the errors list
void SimulationManager::printErrors()
{
	char hold_the_screen;
	cout << "Errors:"<<endl;
	while (!errors.empty())
	{
		cout << errors.front() << endl;
		errors.pop_front();
	}
	cout << "Press any key to go back to main menu" << endl;
	cin >> hold_the_screen;
}
//saveScore: gets algorithm name and its score and saves it to the map of algorithms names and scores
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
//saveAlgoNameToTable: gets list of algorithms names and initialize the map of names and scores with the names
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
//getWinnerStepNumber: return the winner steps number
int SimulationManager::getWinnerStepNumber() {
	return winnerStepsNumber;
}
//deleteSimFromArray: gets index of a simulator to delete and move all the simulators that comes afterwards to override this simulator's place
void SimulationManager::deleteSimFromArray(int indexOfSim) {
	_memccpy(&simulators[indexOfSim], &simulators[indexOfSim + 1], numOfSimulators - indexOfSim, sizeof(Simulator));
}
//calcScoreTableDataAvgs: goes over scores of all algorithm and calculate it averages
void SimulationManager::calcScoreTableDataAvgs()
{
	for (auto& element : scoreTableData)
	{
		element.second.calculateAvg();
	}
}
//resetParametersForNextHouse: resets parameters to prepare for the run of the next house - frees simulation data, and reset steps number and winner steps number
void SimulationManager::resetParametersForNextHouse()
{
	freeSimulators();
	stepNumber = 0;
	winnerStepsNumber = 0;
}
//getMaxScoreAlgorithmName: goes over map of algorithm names and scores and return the algorithm's name with the max result
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