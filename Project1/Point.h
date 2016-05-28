#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"

enum { MAX_Y = 20, MAX_X = 79 };
enum {DOCK_X = 40, DOCK_Y = 12};

class Point 
{
	int x = 1, y = 1;

	struct NeighboursIterator
	{
		Direction d;
		const Point& p;
		NeighboursIterator(Direction _d, const Point& _p) : d(_d), p(_p) {}
		NeighboursIterator operator++()
		{
			d = (Direction)((int)d + 1); // Stay represent end
			return *this;
		}
		Point operator*()const
		{
			Point neighbour = p;
			neighbour.move(d);
			return neighbour;
		}
		bool operator!=(NeighboursIterator other)const
		{
			return !(other.p == p && other.d == d);
		}
	};
	struct Neighbours
	{
		NeighboursIterator begin() { return NeighboursIterator(directions[0], p); }
		NeighboursIterator end() { return NeighboursIterator(Direction::Stay, p); }
		const Point& p;
		Neighbours(const Point& _p) : p(_p) {}
	};


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
	bool operator==(const Point& other)const {
		return (x == other.x && y == other.y);
	}

	Point next(Direction direction);
	bool isSame(Point& p) {return x == p.x && y == p.y;}
	void drawToScreenWhenDockingOn(Point docking, char ch);
	Neighbours neighbours()const { return Neighbours(*this); }
	Point neighbour(Direction d)const;
	/*
	bool operator==(const Point& other)const 
	{
		return (x == other.x && y == other.y);
	}
	*/
	// operator< required by map<Point, T>
	bool operator<(const Point& other)const {
		return (x < other.x || (x == other.x && y < other.y));
	}
};


#endif