#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "Point.h"
#include "SensorInformation.h"

#define DOCK_LETTER 'D'
#define WALL_LETTER 'W'

enum { MIN_DIRT_LEVEL = 0, MAX_DIRT_LEVEL = 9 };
enum { MIN_ROWS = 5, MAX_ROWS = 20, MIN_COLS = 10, MAX_COLS = 79 };

class House
{
	char** house;
	int rows;
	int cols;
	Point dockingPosition;
	int overallDirtLevel = 0;
	int maxSteps;
	string note;
	bool validHouseFlag = true;
	Point currentPosition;
public:
	void setHouse(char ** myHouse, int _rows, int _cols);
	char getValueFromPoint(Point p);
	char getValueFromPoint(int x, int y);
	void reduceValueAtPoint(Point p);
	void setDockingPosition(int x, int y);
	Point getDockingPosition();
	void reduceOverallDirtLevel();
	int getOverallDirtLevel();
	void setOverallDirtLevel(int);
	void endGameForInvalidNumOfDocking();
	void fillSurroundingWalls();
	bool isValidHouse(){return validHouseFlag;}
	void freeHouseMemory();
	void copyHouseData(House houseToCopy);
	int getRows();
	int getCols();
	void setHouseArray(char** arr);
	void setRows(int _rows);
	void setCols(int _cols);
	int getMaxSteps();
	void setMaxSteps(int _maxSteps);
	string getNote();
	char ** getHouse();
	void checkDockingValidationAndUpdateNote(int dockingCounter);
	void checkRowsAndColsValidationAndUpdateNote(int _rows, int _cols);
	House createCopyHouse();
	void setCurrentPosition(Point position);
	SensorInformation getSensorInformation();
};

#endif
