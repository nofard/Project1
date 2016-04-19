#include "Point.h"

//draw: draw a character at (x,y).
void Point::draw(char ch)
{
	gotoxy(x, y);
	cout << ch;
	cout.flush();
}

//next: return the next point according to the recieved direction.
Point Point::next(Direction direction)
{
	Point next = *this;
	next.move(direction);
	return next;
}

//move: increase/decrease x and y by one according to the recieved direction.
void Point::move(Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		--y;
		break;
	case Direction::RIGHT:
		++x;
		break;
	case Direction::DOWN:
		++y;
		break;
	case Direction::LEFT:
		--x;
		break;
	case Direction::STAY:
		break;
	}
}

//drawToScreenWhenDockingOn: draw to the screen "this" point when docking station is shifted to the middle of the screen.
//if the point is out of bounds of the screen, it will be reflected from the opposite side.
void Point::drawToScreenWhenDockingOn(Point docking, char ch)
{
	int newX, newY;
	int x_offset, y_offset;

	x_offset = DOCK_X - docking.getX();
	y_offset = DOCK_Y - docking.getY();

	newX = x + x_offset;
	newY = y + y_offset;

	if (newX >= MAX_X)
		newX = newX - MAX_X;
	if (newX < 0)
		newX = newX + MAX_X;

	if (newY >= MAX_Y)
		newY = newY - MAX_Y;
	if (newY < 0)
		newY = newY + MAX_Y;

	gotoxy(newX, newY);
	cout << ch;
	cout.flush();
}