#include "House.h"

//setHouse: Set house data members, including validation check relative to house conditions
void House::setHouse(char ** myHouse, int _rows, int _cols)
{
	int dockingCounter = 0;
	overallDirtLevel = 0;

	if (initRowsAndCols(_rows, _cols))
	{
		house = new char*[rows];
		for (int i = 1; i < rows - 1; i++)
		{
			house[i] = new char[cols + 1];
			for (int j = 1; j < cols - 1; j++)
			{
				house[i][j] = myHouse[i][j];
				if (house[i][j] == DOCK_LETTER)
				{
					dockingCounter++;
					setDockingPosition(j, i);
				}
				if (house[i][j] > (MIN_DIRT_LEVEL + '0') && house[i][j] <= (MAX_DIRT_LEVEL + '0'))
					overallDirtLevel += (int)(house[i][j] - '0');
			}
			//house[i][cols] = '\0';
		}
		fillSurroundingWalls();

		if (dockingCounter != 1)
		{
			validHouseFlag = false;
			endGameForInvalidNumOfDocking();
		}
	}
	else {
		//exit(0);//need to be changed
		
	}
}

//getValueFromPoint: return the character in a specifiec point.
char House::getValueFromPoint(Point p)
{
	return house[p.getY()][p.getX()];
}

//getValueFromPoint: return the character in a x,y coordinations.
char House::getValueFromPoint(int x, int y)
{
	return house[y][x];
}

//reduceValueAtPoint: reduce value by 1 to a specifiec point.
void House::reduceValueAtPoint(Point p)
{
	int value = (int)(house[p.getY()][p.getX()] - '0');
	if (value == 1)
		house[p.getY()][p.getX()] = ' '; //to Print nothing instead of 0.
	else
		house[p.getY()][p.getX()] = (char)((value - 1) + '0');
}

//setDockingPosition: set dockingPosition data member.
void House::setDockingPosition(int x, int y)
{
	dockingPosition.setPoint(x, y);
}

//getDockingPosition: return dockingPosition.
Point House::getDockingPosition()
{
	return dockingPosition;
}

//reduceOverallDirtLevel: reduce overallDirtLevel by 1.
void House::reduceOverallDirtLevel()
{
	overallDirtLevel--;
}

//getOverallDirtLevel: return overallDirtLevel.
int House::getOverallDirtLevel()
{
	return overallDirtLevel;
}

void House::setOverallDirtLevel(int _overallDirtLevel)
{
	overallDirtLevel = _overallDirtLevel;
}

//endGameForInvalidNumOfDocking: Print a message for invalid number of docking stations.
void House::endGameForInvalidNumOfDocking()
{
	system("cls");
	cout << "Invalid house:" << endl;
	cout << "Reason: More or less than one docking station" << endl;
}

//initRowsAndCols: Check validation size of rows and cols and init data members of them.
bool House::initRowsAndCols(int _rows, int _cols)
{
	if (_rows < MIN_ROWS || _rows > MAX_ROWS || _cols < MIN_COLS || _cols > MAX_COLS)
	{
		system("cls");
		cout << "Invalid house:" << endl;
		cout << "Reason: House size is invalid" << endl;
		validHouseFlag = false;
		return false;
	}
		
	else
	{
		rows = _rows;
		cols = _cols;
		return true;
	}	
}

//fillSurroundingWalls: This function make sure the surrounding walls of the house are complete, so the robot won't escape and eat ice cream.
void House::fillSurroundingWalls()
{
	int i;
	house[0] = new char[cols];
	house[rows-1] = new char[cols];
	for (i = 0; i < cols; i++)//Fill first and last rows
	{
		house[0][i] = WALL_LETTER;
		house[rows-1][i] = WALL_LETTER;
	}
		
	for (i = 0; i < rows; i++)//Fill first and last cols
	{
		house[i][0] = WALL_LETTER;
		house[i][cols-1] = WALL_LETTER;
	}
}

void House::freeHouseMemory()
{

	for (int i = 0; i < rows; i++)
	{
		delete [] house[i];
	}
	delete[] house;
}

void House::copyHouseData(House houseToCopy)
{
	rows = houseToCopy.rows;
	cols = houseToCopy.cols;
	dockingPosition = houseToCopy.dockingPosition;
	overallDirtLevel = houseToCopy.overallDirtLevel;
	validHouseFlag = houseToCopy.validHouseFlag;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			house[i][j] = houseToCopy.house[i][j];
		}
	}
}
int House::getRows()
{
	return rows;
}
int House::getCols()
{
	return cols;
}

void House::setHouseArray(char** arr)
{
	house = arr;
}