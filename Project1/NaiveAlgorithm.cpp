#include "NaiveAlgorithm.h"


REGISTER_ALGORITHM(NaiveAlgorithm)

	// setSensor is called once when the Algorithm is initialized 
void NaiveAlgorithm::setSensor(const AbstractSensor& _sensor)  {
		sensor = &_sensor;
	}


	// setConfiguration is called once when the Algorithm is initialized - see below 
void NaiveAlgorithm::setConfiguration(map<string, int> config) {
		// ignore
	}

	// step is called by the simulation for each time unit 
Direction NaiveAlgorithm::step(Direction previousStep) {
		SensorInformation s = sensor->sense();
		Direction checkDir = currDir;
		do {
			if (!s.isWall[(int)checkDir]) {
				currDir = checkDir;
				return currDir;
			}
		} while (++checkDir != currDir);
		return Direction::Stay;
	}

	// this method is called by the simulation either when there is a winner or 
	// when steps == MaxSteps - MaxStepsAfterWinner 
	// parameter stepsTillFinishing == MaxStepsAfterWinner 
	void NaiveAlgorithm::aboutToFinish(int stepsTillFinishing) {
		// ignore
	}
	