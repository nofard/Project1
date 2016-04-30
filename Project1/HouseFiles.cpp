#include "HouseFiles.h"

const int buff_size = 1024;

//initHouseFiles: init each file type list with a suited command line.
void HouseFiles::initHouseFiles()
{
	initList(initialHousefilesNames, "dir /b /O:N |findstr \"[0-9][0-9][0-9].house$\" > houseFilesNames.txt");
	initList(savedHousefilesNames, "dir /b /O:N |findstr \".house_saved\" > houseFilesNames.txt");
	initList(solutionHousefilesNames, "dir /b /O:N |findstr \"[0-9][0-9][0-9].house_solution\" > houseFilesNames.txt");

}
//initList: gets file type list and a command to run, runs the command that outputs to a file, and copy all the houses 
//names from the result file to the given list.
void HouseFiles::initList(list<string>&lst, char* command)
{
	char buff[buff_size];
	system(command);
	ifstream houseFilesNames("houseFilesNames.txt");

	while (!houseFilesNames.eof()) {
		houseFilesNames.getline(buff, buff_size - 1);
		if (strcmp(buff, ""))
			lst.push_back(buff);
	}

	houseFilesNames.close();
}
//getMinHouseNumber: returns the minimal house number found in houses list (the list that contains the .house files)
int HouseFiles::getMinHouseNumber()
{
	return convertHouseNameToNumber((initialHousefilesNames.begin())->data());
}
//getMaxHouseNumber: returns the maximal house number found in houses list (the list that contains the .house files)
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
//getHouseNameByIndex: recieves a list of house names and an index, and returns the name of the house name in the given index on the list.
string HouseFiles::getHouseNameByIndex(list<string>&lst, int index)
{
	list<string>::iterator it = lst.begin();
	for (int i = 0; i < index; i++, it++);
	{
	}
	return it->data();
}
//getHouseFromFile: gets name of file, and rows, cols and maxs steps (as output variables) and reads from the file the output information
//and also the house array itself, and return the array.
char** HouseFiles::getHouseFromFile(string house_name, int *rows, int *cols, int *maxStepsFromFile)
{
	char** house_array;
	int rowIndex = 0;
	int colIndex = 0;
	char buff[buff_size];
	ifstream in(house_name);

	in.getline(buff, buff_size - 1);//title of the house

	in.getline(buff, buff_size - 1);
	*maxStepsFromFile = atoi(buff);

	in.getline(buff, buff_size - 1);
	*rows = atoi(buff);

	in.getline(buff, buff_size - 1);
	*cols = atoi(buff);

	house_array =  new char*[*rows];

	for (int i = 0; i < *rows; i++)
	{
		house_array[i] = new char[*cols]; //memory allocation for a row
		for (int j = 0; j < *cols; j++)
		{
			house_array[i][j] = ' ';
		}
	}
	while (!in.eof())
	{	
		in.getline(buff, buff_size - 1);
		colIndex = 0;
		while(colIndex < strlen(buff))
		{
			house_array[rowIndex][colIndex] = buff[colIndex];
			colIndex++;
		}
		rowIndex++;
	}

	in.close();
	return house_array;
}
//getIntialFilesListLength: returns the size of list that contains files names with .house suffix
int HouseFiles::getIntialFilesListLength() 
{
	return initialHousefilesNames.size();
}
//getInitialHouseFilesList: returns the list that contains files names with .house suffix
list<string>* HouseFiles::getInitialHouseFilesList()
{
	return &initialHousefilesNames;
}
//getSavedHouseFilesList: returns the list that contains files names with .house_saved suffix
list<string>* HouseFiles::getSavedHouseFilesList()
{
	return &savedHousefilesNames;
}
//convertHouseNameToNumber: gets full house name and returns it number as an integer
int HouseFiles::convertHouseNameToNumber(string houseName) 
{
	return ((houseName[0] - '0') * 100 + (houseName[1] - '0') * 10 + (houseName[2] - '0'));
}
void HouseFiles::setCurrHouseName(string houseName) 
{
	currHouseName = houseName;
}
//saveGameToFile: gets part of house name to save, list of moves were made in the game and the number of steps,
//and checks if this file already exists, if so, asks the user whether to override or save in different name
//and saves the moves and steps number to a file.
void HouseFiles::saveGameToFile(string userSelectionPartName, list<StepAndDirection>&moves, int stepsNum)
{
	string tempName;
	int userChoice;
	ofstream outputFile; 

	outputFile.open(currHouseName.substr(0,3) + "-"	+ userSelectionPartName + ".house_saved", ios::_Noreplace);
	while (!outputFile) {
		cout << "This file already exists, please choose whether to enter another name (1) or to override (2): " << endl;
		cin >> userChoice;
		if (userChoice == 1) {
			cout << "Please enter another file name:" << endl;
			cin >> tempName;
			outputFile.open(currHouseName.substr(0, 3) + "-" + tempName + ".house_saved", ios::_Noreplace);
		}
		else {
			outputFile.open(currHouseName.substr(0, 3) + "-" + userSelectionPartName + ".house_saved");
		}
	}
	copyListToFile(outputFile, moves, stepsNum);
	outputFile.close();
}
//saveSolutionToFile: gets list of moves were made in the game and the number of steps,
//and checks if this file already exists, if so, checks if number of steps in current is lower than in existing file, if so,
//saves the moves and steps number to a file.
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
//copyListToFile: gets file object, list of moves made in the game and number of steps, and saved to the file this information
//in a specific format.
void HouseFiles::copyListToFile(ostream& outputFile, list<StepAndDirection>&moves, int stepsNum)
{
	outputFile << stepsNum << endl;
	list<StepAndDirection>::iterator it;
	for (it = moves.begin(); it != moves.end(); ++it)
	{
		outputFile << (*it).step << ":" << convertNumToDirLetter((*it).dir) << endl;
	}
}
//convertNumToDirLetter: gets a number and returns the suited direction letter.
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
//getIndexOfHouseFromList: gets name of house, and search for this name in the list of house name, and returns the index of this name
//in the list.
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
//getSolutionFromList: gets house number, and search for it in solution files list, and returns it name (if wasn't found return "").
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
//freeHouseFilesMemory: clears all list filled in house files.
void HouseFiles::freeHouseFilesMemory()
{
	initialHousefilesNames.clear();
	savedHousefilesNames.clear();
	solutionHousefilesNames.clear();
}