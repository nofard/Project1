#include "_204032031_Point.h"

//draw: draw a character at (x,y).
void _204032031_Point::draw(char ch)
{
	gotoxy(x, y);
	cout << ch;
	cout.flush();
}

//next: return the next point according to the recieved direction.
_204032031_Point _204032031_Point::next(Direction direction)
{
	_204032031_Point next = *this;
	next.move(direction);
	return next;
}

//move: increase/decrease x and y by one according to the recieved direction.
void _204032031_Point::move(Direction dir)
{
	switch (dir)
	{
	case Direction::North:
		--y;
		break;
	case Direction::East:
		++x;
		break;
	case Direction::South:
		++y;
		break;
	case Direction::West:
		--x;
		break;
	case Direction::Stay:
		break;
	}
}

//drawToScreenWhenDockingOn: draw to the screen "this" point when docking station is shifted to the middle of the screen.
//if the point is out of bounds of the screen, it will be reflected from the opposite side.
void _204032031_Point::drawToScreenWhenDockingOn(_204032031_Point docking, char ch)
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

Point Point::neighbour(Direction d)const
{
	_204032031_Point p = *this;
	p.move(d);
	return p;
}