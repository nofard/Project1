#include "Score.h"

//calculateScore: calculate the score respectively to the requested formula.
int Score::calculateScore() {
	int tempScore = 2000;

	tempScore -= ((position_in_copmetition - 1) * 50);
	tempScore += ((winner_num_steps - this_num_steps) * 10);
	tempScore -= ((sum_dirt_in_house - dirt_collected) * 3);
	tempScore += (is_back_in_docking ? 50 : -200);

	return (0 > tempScore ? 0 : tempScore);
}
