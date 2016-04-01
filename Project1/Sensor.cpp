#include "Sensor.h"

//initSensor: set sensor data members.
void Sensor::initSensor(Simulator * _sim, House *_house, Point _robotPosition)
{
	sim = _sim;
	house = _house;
	updateSensorInfo(_robotPosition);
}

//sense: return SensorInformation.
SensorInformation Sensor::sense()const //this function called from the algorithm, so the const make sure the values of the sensor won't be changed.
{
	return sensorInfo;
}

//updateSensorInfo: update SensorInformation, and robotPosition in accordance with the current house.
void Sensor::updateSensorInfo(Point currPosition)
{
	robotPosition = currPosition;
	updateWallsInfo();
	updateDirtLevel();
}

//setCurrPosition: set new robotPosition.
void Sensor::setCurrPosition(Point currPosition)
{
	robotPosition = currPosition;
}

//updateWallsInfo: update isWall array with boolean parameters that indicates if there is wall in the direction(by index).
void Sensor::updateWallsInfo()
{
	sensorInfo.isWall[0] = (house->getValueFromPoint(robotPosition.getX(), robotPosition.getY() - 1) == 'W'); //UP
	sensorInfo.isWall[1] = (house->getValueFromPoint(robotPosition.getX() + 1, robotPosition.getY()) == 'W'); //RIGHT
	sensorInfo.isWall[2] = (house->getValueFromPoint(robotPosition.getX(), robotPosition.getY() + 1) == 'W'); //DOWN
	sensorInfo.isWall[3] = (house->getValueFromPoint(robotPosition.getX() - 1, robotPosition.getY()) == 'W'); //LEFT
}

//updateDirtLevel: update sensor information about the dirt level in the current position of the robot.
void Sensor::updateDirtLevel()
{
	char char_currDirtLevel;

	char_currDirtLevel = house->getValueFromPoint(robotPosition);
	if (char_currDirtLevel > '0' && char_currDirtLevel <= '9')
		sensorInfo.dirtLevel = (int)(char_currDirtLevel - '0');
	else
		sensorInfo.dirtLevel = 0;
}

//revealArea: reveal to the screen the area(= 4 directions) near the robot position.
void Sensor::revealArea()
{
	Point neibhor;
	char charToDraw;

	for (int dir = 0; dir < 4; dir++)
	{
		neibhor = robotPosition.next((Direction)dir);
		charToDraw = house->getValueFromPoint(neibhor);
		neibhor.drawToScreenWhenDockingOn(house->getDockingPosition(), charToDraw);
	}

}
