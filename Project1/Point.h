#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"


using namespace std;

enum { MAX_Y = 20, MAX_X = 79 };

class Point {
	int x = 1, y = 1;

public:
	int getX() const {return x;}
	int getY() const {return y;}

	void setPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void draw(char ch);
	void move(Direction direction);
	Point next(Direction direction);
	bool isSame(Point& p) {return x == p.x && y == p.y;}
	void drawToScreenWhenDockingOn(Point docking, char ch);
};

#endif