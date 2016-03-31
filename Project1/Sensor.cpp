#include "Sensor.h"

void Sensor::initSensor(Simulator * _sim, House *_house, Point _robotPosition)
{
	sim = _sim;
	house = _house;
	updateSensorInfo(_robotPosition);
}

SensorInformation Sensor::sense()const //this function called from the algorithm, so the const make sure the values of the sensor won't be changed.
{
	return sensorInfo;
}

void Sensor::updateSensorInfo(Point currPosition)
{
	robotPosition = currPosition;
	updateWallsInfo();
	updateDirtLevel();
}

void Sensor::setCurrPosition(Point currPosition)
{
	robotPosition = currPosition;
}

void Sensor::updateWallsInfo()
{
	sensorInfo.isWall[0] = (house->getValueFromPoint(robotPosition.getX(), robotPosition.getY() - 1) == 'W'); //UP
	sensorInfo.isWall[1] = (house->getValueFromPoint(robotPosition.getX() + 1, robotPosition.getY()) == 'W'); //RIGHT
	sensorInfo.isWall[2] = (house->getValueFromPoint(robotPosition.getX(), robotPosition.getY() + 1) == 'W'); //DOWN
	sensorInfo.isWall[3] = (house->getValueFromPoint(robotPosition.getX() - 1, robotPosition.getY()) == 'W'); //LEFT
}

void Sensor::updateDirtLevel()
{
	char char_currDirtLevel;

	char_currDirtLevel = house->getValueFromPoint(robotPosition);
	if (char_currDirtLevel > '0' && char_currDirtLevel <= '9')
		sensorInfo.dirtLevel = (int)(char_currDirtLevel - '0');
	else
		sensorInfo.dirtLevel = 0;
}

void Sensor::revealArea()
{
	Point neibhor;
	char charToDraw;

	for (int dir = 0; dir < 4; dir++)
	{
		neibhor = robotPosition.next((Direction)dir);
		charToDraw = house->getValueFromPoint(neibhor);
//		neibhor.draw(charToDraw);
		neibhor.drawToScreenWhenDockingOn(house->getDockingPosition(), charToDraw);
		//Point offset; offset.setPoint(40 - house->getDockingPosition().getX(), 12 - house->getDockingPosition().getY());
	}

}
