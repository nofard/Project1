#include "Point.h"

void Point::draw(char ch) 
{
	gotoxy(x, y);
	cout << ch;
	cout.flush();
}

Point Point::next(Direction direction)
{
	Point next = *this;
	next.move(direction);
	return next;
}

void Point::move(Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		--y;
		//		if (y < 1) {
		//			y = 24;
		//		}
		break;
	case Direction::RIGHT:
		++x;
		//		if (x > 79) {
		//			x = 1;
		//		}
		break;
	case Direction::DOWN:
		++y;
		//		if (y > 24) {
		//			y = 1;
		//		}
		break;
	case Direction::LEFT:
		--x;
		//		if (x < 1) {
		//			x = 79;
		//		}
		break;
	case Direction::STAY:
		break;
	}
}

void Point::drawToScreenWhenDockingOn(Point docking, char ch)
{
	int newX, newY;
	int x_offset, y_offset;

	x_offset = 40 - docking.getX();
	y_offset = 12 - docking.getY();

	newX = x + x_offset;
	newY = y + y_offset;

	if (newX >= MAX_X)
		newX = newX - MAX_X;
	if (newY >= MAX_Y)
		newY = newY - MAX_Y;

	gotoxy(newX, newY);
	cout << ch;
	cout.flush();
}