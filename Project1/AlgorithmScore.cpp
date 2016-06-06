#include "AlgorithmScore.h"

//addScore: Adding score to the scores list.
void AlgorithmScore::addScore(int score)
{
	scores.push_back(score);
}

//calculateAvg: calculate average of all scores in the scores list.
void AlgorithmScore::calculateAvg()
{
	int numOfScores = scores.size();
	int sum = 0;
	list<int>::iterator it = scores.begin();

	while (it != scores.end())
	{
		sum += *it;
		it++;
	}

	average = sum / numOfScores;
}

//getAverage: return average.
int& AlgorithmScore::getAverage()
{
	return average;
}

//getScoresList: return scores list.
list<int>& AlgorithmScore::getScoresList()
{
	return scores;
}