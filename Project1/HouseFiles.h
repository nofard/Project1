#ifndef _HOUSE_FILES_H_
#define _HOUSE_FILES_H_

#include "io_utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define NEW_HOUSE 0
#define SAVED_HOUSE 1
#define SOLUTION_HOUSE 2

class HouseFiles{
	list<string> initialHousefilesNames;
	list<string> savedHousefilesNames;
	list<string> solutionHousefilesNames;
	int houseNumberChoice;
	string currHouseName;
	int fileType; //0 - new house, 1 - saved house, 2 - solution house

public:
	HouseFiles() {}
	void initHouseFiles();
	int getMinHouseNumber();
	int getMaxHouseNumber();
	void saveGameToFile(string fileName, list<StepAndDirection>&moves, int stepsNum);
	void setFileType(int);
	void setHouseNumberChoice(int);
	string getHouseNameByIndex(list<string>&lst, int index);
	char** getHouseFromFile(string house_name, int *rows, int *cols);
	int getIntialFilesListLength();
	int convertHouseNameToNumber(string);
	void setCurrHouseName(string);
	void saveSolutionToFile(list<StepAndDirection>&moves, int stepsNum);
	void copyListToFile(ostream& outputFile, list<StepAndDirection>&moves, int stepsNum);
	void initList(list<string>&lst, char* regex);
	list<string>* getInitialHouseFilesList();
	list<string>* getSavedHouseFilesList();
	char convertNumToDirLetter(int number);
	int getHouseNumberChoice();
	
};

#endif