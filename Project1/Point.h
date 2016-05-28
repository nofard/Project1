#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"

enum { MAX_Y = 20, MAX_X = 79 };
enum {DOCK_X = 40, DOCK_Y = 12};

class Point 
{
	int x = 1, y = 1;
public:
	int getX() const {return x;}
	int getY() const {return y;}
	Point()  {}
	Point(int _x, int _y) : x(_x), y(_y) {}
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
	Point neighbour(Direction d)const;
	/*
	bool operator==(const Point& other)const 
	{
		return (x == other.x && y == other.y);
	}
	*/
	
};


#endif