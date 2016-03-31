#ifndef _SCORE_H_
#define _SCORE_H_


class Score{
	int position_in_copmetition;
	int winner_num_steps;
	int this_num_steps;
	int sum_dirt_in_house;
	int dirt_collected;
	bool is_back_in_docking;

public:
	Score() {}
	Score(int position, int winnerSteps, int thisSteps, int overallDirt, int dirtCollected, bool backInDock) {
		position_in_copmetition = position;
		winner_num_steps = winnerSteps;
		this_num_steps = thisSteps;
		sum_dirt_in_house = overallDirt;
		dirt_collected = dirtCollected;
		is_back_in_docking = backInDock;
	
	}
	int calculateScore();
	void setPosition(int);
};

#endif