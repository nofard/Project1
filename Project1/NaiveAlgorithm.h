#include "AbstractAlgorithm.h"


class NaiveAlgorithm : public AbstractAlgorithm {
	const AbstractSensor* sensor;
	Direction currDir = Direction::East;
public:
	// setSensor is called once when the Algorithm is initialized 
	virtual void setSensor(const AbstractSensor& _sensor) override;

	// setConfiguration is called once when the Algorithm is initialized - see below 
	virtual void setConfiguration(map<string, int> config);
	// step is called by the simulation for each time unit 
	virtual Direction step(Direction previousStep);

	// this method is called by the simulation either when there is a winner or 
	// when steps == MaxSteps - MaxStepsAfterWinner 
	// parameter stepsTillFinishing == MaxStepsAfterWinner 
	virtual void aboutToFinish(int stepsTillFinishing);
};
