#include "HouseFiles.h"

const int buff_size = 1024;

void HouseFiles::initHouseFiles()
{
	char buff[buff_size];
	system("dir /b /O:N |findstr \"[0-9][0-9][0-9].House\" > houseFilesNames.txt");
	ifstream houseFilesNames("houseFilesNames.txt");

	while (!houseFilesNames.eof()) {
		houseFilesNames.getline(buff, buff_size - 1);
		if (strcmp(buff, ""))
			initialHousefilesNames.push_back(buff);
	}

	houseFilesNames.close();
	/*
	list<string>::iterator it;
	for (it = initialHousefilesNames.begin(); it != initialHousefilesNames.end(); ++it)
		cout << (*it).data() << endl;
		*/
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

string HouseFiles::getHouseNameByIndex(int index)
{
	list<string>::iterator it = initialHousefilesNames.begin();
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

int HouseFiles::convertHouseNameToNumber(string houseName) 
{
	return ((houseName[0] - '0') * 100 + (houseName[1] - '0') * 10 + (houseName[2] - '0'));
}
void HouseFiles::setCurrHouseName(string houseName) {
	currHouseName = houseName;
}

void HouseFiles::saveGameToFile(string fileName, list<StepAndDirection>moves, int stepsNum) 
{
	string tempName;
	int num;
	ofstream outputFile; 

	outputFile.open(this->currHouseName.substr(0,2) + "-" + fileName + ".house_saved", ios::_Noreplace);

	while (!outputFile) {
		cout << "This file already exists, please choose whether to enter another name (1) or to override (2): " << endl;
		cin >> num;
		if (num == 1) {
			cout << "Please enter another file name:" << endl;
			cin >> tempName;
			outputFile.open(currHouseName + "-" + tempName + ".house_saved", ios::_Noreplace);
		}
		else {
			outputFile.open(currHouseName + "-" + fileName + ".house_saved");
		}
	}
	

	outputFile << stepsNum << endl;
	list<StepAndDirection>::iterator it;
	for (it = moves.begin(); it != moves.end(); ++it)
	{
		outputFile << (*it).step << " : " << (*it).dir << endl;
	}
	
	outputFile.close();
}