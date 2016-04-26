#include "HouseFiles.h"

const int buff_size = 1024;

void HouseFiles::initHouseFiles()
{
	initList(initialHousefilesNames, "dir /b /O:N |findstr \"[0-9][0-9][0-9].house$\" > houseFilesNames.txt");
	initList(savedHousefilesNames, "dir /b /O:N |findstr \".house_saved\" > houseFilesNames.txt");
	initList(solutionHousefilesNames, "dir /b /O:N |findstr \"[0-9][0-9][0-9].house_solution\" > houseFilesNames.txt");

}

void HouseFiles::initList(list<string>&lst, char* regex)
{
	char buff[buff_size];
	system(regex);
	ifstream houseFilesNames("houseFilesNames.txt");

	while (!houseFilesNames.eof()) {
		houseFilesNames.getline(buff, buff_size - 1);
		if (strcmp(buff, ""))
			lst.push_back(buff);
	}

	houseFilesNames.close();
}

int HouseFiles::getMinHouseNumber()
{
	return convertHouseNameToNumber((initialHousefilesNames.begin())->data());
}

int HouseFiles::getMaxHouseNumber()
{
	return convertHouseNameToNumber(initialHousefilesNames.back());
}

void HouseFiles::setFileType(int _fileType)
{
	fileType = _fileType;
}
void HouseFiles::setHouseNumberChoice(int _houseNumChoice)
{
	houseNumberChoice = _houseNumChoice;
}

string HouseFiles::getHouseNameByIndex(list<string>&lst, int index)
{
	list<string>::iterator it = lst.begin();
	for (int i = 0; i < index; i++, it++);
	{
	}
	return it->data();
}

char** HouseFiles::getHouseFromFile(string house_name, int *rows, int *cols)
{
	char** house_array;
	int i = 0;
	int maxSteps;
	char buff[buff_size];
	ifstream in(house_name);

	in.getline(buff, buff_size - 1);//title of the house

	in.getline(buff, buff_size - 1);
	maxSteps = atoi(buff);
	config.MaxSteps = maxSteps;

	in.getline(buff, buff_size - 1);
	*rows = atoi(buff);

	in.getline(buff, buff_size - 1);
	*cols = atoi(buff);

	house_array =  new char*[*rows];
	while (!in.eof())
	{
		house_array[i] = new char[*cols]; //memory allocation for a row
		in.getline(buff, buff_size - 1);
		for (int j = 0; j < *cols; j++)
		{
			house_array[i][j] = buff[j];
		}
		i++;
	}

	in.close();
	return house_array;
}
int HouseFiles::getIntialFilesListLength() 
{
	return initialHousefilesNames.size();
}

list<string>* HouseFiles::getInitialHouseFilesList()
{
	return &initialHousefilesNames;
}

list<string>* HouseFiles::getSavedHouseFilesList()
{
	return &savedHousefilesNames;
}



int HouseFiles::convertHouseNameToNumber(string houseName) 
{
	return ((houseName[0] - '0') * 100 + (houseName[1] - '0') * 10 + (houseName[2] - '0'));
}
void HouseFiles::setCurrHouseName(string houseName) {
	currHouseName = houseName;
}

void HouseFiles::saveGameToFile(string userSelectionPartName, list<StepAndDirection>&moves, int stepsNum)
{
	string tempName;
	int userChoice;
	ofstream outputFile; 

	outputFile.open(this->currHouseName.substr(0,3) + "-" + userSelectionPartName + ".house_saved", ios::_Noreplace);

	while (!outputFile) {
		cout << "This file already exists, please choose whether to enter another name (1) or to override (2): " << endl;
		cin >> userChoice;
		if (userChoice == 1) {
			cout << "Please enter another file name:" << endl;
			cin >> tempName;
			outputFile.open(currHouseName + "-" + tempName + ".house_saved", ios::_Noreplace);
		}
		else {
			outputFile.open(currHouseName + "-" + userSelectionPartName + ".house_saved");
		}
	}
	copyListToFile(outputFile, moves, stepsNum);
	outputFile.close();
}

void HouseFiles::saveSolutionToFile(list<StepAndDirection>&moves, int stepsNum)
{
	char buff[buff_size];
	ofstream outputFile;
	string solutionFileName = this->currHouseName.substr(START_INDEX_NAME, END_INDEX_NAME) + ".house_solution";
	outputFile.open(solutionFileName, ios::_Noreplace);

	if(!outputFile) //file exist
	{
		ifstream inFile(solutionFileName);
		inFile.getline(buff, buff_size - 1);
		if (stepsNum < atoi(buff))
		{
			outputFile.open(solutionFileName);
			copyListToFile(outputFile, moves, stepsNum);
		}
		inFile.close();
	}
	else
	{
		copyListToFile(outputFile, moves, stepsNum);
	}
	outputFile.close();
}

void HouseFiles::copyListToFile(ostream& outputFile, list<StepAndDirection>&moves, int stepsNum)
{
	outputFile << stepsNum << endl;
	list<StepAndDirection>::iterator it;
	for (it = moves.begin(); it != moves.end(); ++it)
	{
		outputFile << (*it).step << ":" << convertNumToDirLetter((*it).dir) << endl;
	}
}

char HouseFiles::convertNumToDirLetter(int number)
{
	switch (number)
	{
	case (int)(Direction::UP):
		return 'w';
		break;
	case (int)(Direction::RIGHT):
		return 'd';
		break;
	case (int)(Direction::DOWN):
		return 'x';
		break;
	case (int)(Direction::LEFT):
		return 'a';
		break;
	case (int)(Direction::STAY):
		return 's';
		break;

	}
	return 's';
}

int HouseFiles::getHouseNumberChoice()
{
	return houseNumberChoice;
}

int HouseFiles::getFileType()
{
	return fileType;
}

int HouseFiles::getIndexOfHouseFromList(string houseName)
{
	int index = 0;
	list<string>::iterator it = initialHousefilesNames.begin();

	while((*it) != houseName && it != initialHousefilesNames.end())
	{
		it++;
		index++;
	}
	return index;
}
string HouseFiles::getSolutionFromList(int houseNumber)
{
	list<string>::iterator it = solutionHousefilesNames.begin();
	while (it != solutionHousefilesNames.end())
	{
		if (convertHouseNameToNumber(*it) == houseNumber)
			return (*it);
		it++;
	}
	return "";
}
string HouseFiles::getCurrHouseName()
{
	return currHouseName;
}