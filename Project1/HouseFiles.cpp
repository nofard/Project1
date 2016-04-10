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

int HouseFiles::getMinHouseNumber() {
	string firstHouseName = (initialHousefilesNames.begin())->data();
	return ((firstHouseName[0] - '0') * 100 + (firstHouseName[1] - '0') * 10 + (firstHouseName[2] - '0'));
}

int HouseFiles::getMaxHouseNumber() {
	string firstHouseName = (initialHousefilesNames.back());


	return ((firstHouseName[0] - '0') * 100 + (firstHouseName[1] - '0') * 10 + (firstHouseName[2] - '0')); 1;
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
	}

	in.close();
	return house_array;
}