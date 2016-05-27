#include "HouseFiles.h"

//const int buff_size = 1024;

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
	char buff[BUFF_SIZE];
	system(command);
	ifstream houseFilesNames("houseFilesNames.txt");

	lst.clear();
	while (!houseFilesNames.eof()) {
		houseFilesNames.getline(buff, BUFF_SIZE - 1);
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

//getFileType: get houseFiles fileType.
int HouseFiles::getFileType()
{
	return fileType;
}
//setFileType: set houseFiles fileType.
void HouseFiles::setFileType(int _fileType)
{
	fileType = _fileType;
}
//getHouseNumberChoice: get house number choice.
int HouseFiles::getHouseNumberChoice()
{
	return houseNumberChoice;
}
//setHouseNumberChoice: set house number choice.
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
	char buff[BUFF_SIZE];
	ifstream in(house_name);

	in.getline(buff, BUFF_SIZE - 1);//title of the house

	in.getline(buff, BUFF_SIZE - 1);
	*maxStepsFromFile = atoi(buff);

	in.getline(buff, BUFF_SIZE - 1);
	*rows = atoi(buff);

	in.getline(buff, BUFF_SIZE - 1);
	*cols = atoi(buff);

	if (checkRowsAndColsValidation(*rows, *cols))
	{
		house_array = new char*[*rows];

		for (int i = 0; i < *rows; i++)
		{
			house_array[i] = new char[*cols]; //memory allocation for a row
			for (int j = 0; j < *cols; j++)
			{
				house_array[i][j] = ' ';
			}
		}
		while (!in.eof() && rowIndex < *rows)
		{
			in.getline(buff, BUFF_SIZE - 1);
			colIndex = 0;
			while ((colIndex < strlen(buff)) && colIndex < *cols)
			{
				house_array[rowIndex][colIndex] = buff[colIndex];
				colIndex++;
			}
			rowIndex++;
		}

		in.close();
		return house_array;
	}
	else //house size is invalid
	{
		in.close();
		return nullptr;
	}

}

House HouseFiles::getHouseFromFile(string houseName)
{
	House newHouse;
	char buff[BUFF_SIZE];
	ifstream in(houseName);
	bool rowsColsValidationFlag;
	string houseNote;
	char** house_array;
	int rowIndex = 0;
	int colIndex = 0;
	int dockingCounter = 0;


	in.getline(buff, BUFF_SIZE - 1);//title of the house

	in.getline(buff, BUFF_SIZE - 1);
	newHouse.setMaxSteps(atoi(buff));

	in.getline(buff, BUFF_SIZE - 1);
	newHouse.setRows(atoi(buff));
	
	in.getline(buff, BUFF_SIZE - 1);
	newHouse.setCols(atoi(buff));

	newHouse.checkRowsAndColsValidationAndUpdateNote(newHouse.getRows(), newHouse.getCols());

	if (newHouse.isValidHouse())
	{
		house_array = new char*[newHouse.getRows()];

		for (int i = 0; i < newHouse.getRows(); i++)
		{
			house_array[i] = new char[newHouse.getCols()]; //memory allocation for a row
			for (int j = 0; j < newHouse.getCols(); j++)
			{
				house_array[i][j] = ' ';
			}
		}
		while (!in.eof() && rowIndex < newHouse.getRows())
		{
			in.getline(buff, BUFF_SIZE - 1);
			colIndex = 0;
			while ((colIndex < strlen(buff)) && colIndex < newHouse.getCols())
			{
				if (house_array[rowIndex][colIndex] == DOCK_LETTER)
				{
					newHouse.setDockingPosition(colIndex, rowIndex);
					dockingCounter++;
				}
				house_array[rowIndex][colIndex] = buff[colIndex];
				colIndex++;
			}
			rowIndex++;
		}

		newHouse.setHouseArray(house_array);
		newHouse.checkDockingValidationAndUpdateNote(dockingCounter);
		
	}
	
	in.close();
		
	return newHouse;
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
	char buff[BUFF_SIZE];
	ofstream outputFile;
	string solutionFileName = this->currHouseName.substr(START_INDEX_NAME, END_INDEX_NAME) + ".house_solution";
	outputFile.open(solutionFileName, ios::_Noreplace);

	if(!outputFile) //file exist
	{
		ifstream inFile(solutionFileName);
		inFile.getline(buff, BUFF_SIZE - 1);
		if (stepsNum < atoi(buff) && stepsNum != 0)
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
	case (int)(Direction::North):
		return 'w';
		break;
	case (int)(Direction::East):
		return 'd';
		break;
	case (int)(Direction::South):
		return 'x';
		break;
	case (int)(Direction::West):
		return 'a';
		break;
	case (int)(Direction::Stay):
		return 's';
		break;

	}
	return 's';
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

//checkRowsAndColsValidation: check rows and cols validation 
bool HouseFiles::checkRowsAndColsValidation(int _rows, int _cols)
{
	char hold_the_screen;
	if (_rows < MIN_ROWS || _rows > MAX_ROWS || _cols < MIN_COLS || _cols > MAX_COLS)
	{
		system("cls");
		cout << "Invalid house:" << endl;
		cout << "Reason: House size is invalid" << endl;
		cout << "Press any key to continue to the next house" << endl;
		cin >> hold_the_screen;
		system("cls");
		return false;
	}
	else
	{
		return true;
	}
}
/*
bool HouseFiles::checkRowsAndColsValidationAndReturnNote(int _rows, int _cols, string * _note)
{
	if (_rows < MIN_ROWS)
	{
		*_note = "";
		return false;
	}
		
	if (_rows > MAX_ROWS)
	{
		*_note = "";
		return false;
	}
		
	if (_cols < MIN_COLS)
	{
		*_note = "";
		return false;
	}
	if (_cols > MAX_COLS)
	{
		*_note = "";
		return false;
	}
	return true;
		
}

bool HouseFiles::checkDockingValidationAndReturnNote(int dockingCounter, string *_note)
{
	if (dockingCounter == 0)
	{
		*_note = "";
		return false;
	}
	if (dockingCounter > 1)
	{
		*_note = "";
		return false;
	}
	return true;
}
*/