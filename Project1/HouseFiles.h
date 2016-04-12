#ifndef _HOUSE_FILES_H_
#define _HOUSE_FILES_H_

#include "io_utils.h"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

class HouseFiles{
	list<string> initialHousefilesNames;
	list<string> savedHousefilesNames;
	list<string> solutionHousefilesNames;
	int houseNumberChoice;
	int fileType; //0 - new house, 1 - saved house, 2 - solution house

public:
	HouseFiles() {}
	void initHouseFiles();
	int getMinHouseNumber();
	int getMaxHouseNumber();
	void saveGameToFile(char * name, char * gameMoves);
	void setFileType(int);
	void setHouseNumberChoice(int);
	string getHouseNameByIndex(int index);
	char** getHouseFromFile(string house_name, int *rows, int *cols);
	int getIntialFilesListLength();
	int convertHouseNameToNumber(string);
};

#endif