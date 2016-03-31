#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "io_utils.h"
#include "Point.h"

enum { MIN_ROWS = 5, MAX_ROWS = 24, MIN_COLS = 10, MAX_COLS = 79 };

class House
{
	char** house;
	int rows;
	int cols;
	Point dockingPosition;
	int overallDirtLevel = 0;
	bool validHouseFlag = true;

public:
	void setHouse(char ** myHouse, int _rows, int _cols);
	char** getHouse();
	char getValueFromPoint(Point p);
	char getValueFromPoint(int x, int y);
	void reduceValueAtPoint(Point p);
	void setDockingPosition(int x, int y);
	Point getDockingPosition();
	void reduceOverallDirtLevel();
	int getOverallDirtLevel();
	void endGameForInvalidNumOfDocking();
	bool initRowsAndCols(int _rows, int _cols);
	void fillSurroundingWalls();
	bool isValidHouse(){return validHouseFlag;}
};

#endif

