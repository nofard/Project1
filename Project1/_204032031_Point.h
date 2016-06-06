#ifndef __204032031_Point_H_
#define __204032031_Point_H_

#include "io_utils.h"

enum { MAX_Y = 20, MAX_X = 79 };
enum {DOCK_X = 40, DOCK_Y = 12};

class _204032031_Point 
{
	int x = 1, y = 1;

	struct NeighboursIterator
	{
		Direction d;
		const _204032031_Point& p;
		NeighboursIterator(Direction _d, const _204032031_Point& _p) : d(_d), p(_p) {}
		NeighboursIterator operator++()
		{
			d = (Direction)((int)d + 1); // Stay represent end
			return *this;
		}
		_204032031_Point operator*()const
		{
			_204032031_Point neighbour = p;
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
		const _204032031_Point& p;
		Neighbours(const _204032031_Point& _p) : p(_p) {}
	};


public:
	int getX() const {return x;}
	int getY() const {return y;}
	_204032031_Point()  {}
	_204032031_Point(int _x, int _y) : x(_x), y(_y) {}
	void setPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void draw(char ch);
	void move(Direction direction);
	bool operator==(const _204032031_Point& other)const {
		return (x == other.x && y == other.y);
	}

	_204032031_Point next(Direction direction);
	bool isSame(_204032031_Point& p) {return x == p.x && y == p.y;}
	void drawToScreenWhenDockingOn(_204032031_Point docking, char ch);
	Neighbours neighbours()const { return Neighbours(*this); }
	_204032031_Point neighbour(Direction d)const;
	/*
	bool operator==(const _204032031_Point& other)const 
	{
		return (x == other.x && y == other.y);
	}
	*/
	// operator< required by map<_204032031_Point, T>
	bool operator<(const _204032031_Point& other)const {
		return (x < other.x || (x == other.x && y < other.y));
	}
};


#endif