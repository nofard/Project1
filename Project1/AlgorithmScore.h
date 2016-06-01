#ifndef _ALGORITHM_SCORE_H_
#define _ALGORITHM_SCORE_H_

#include <list>
#include <iostream>
#include <stdio.h>
using namespace std;

class AlgorithmScore {

	list<int> scores;
	int average;

public:
	AlgorithmScore() {};
	AlgorithmScore(int score, int _average = 0) {
		scores.push_back(score);
		average = _average;
	}
	void addScore(int score)
	{
		scores.push_back(score);
	}

	void calculateAvg()
	{
		//list<StepAndDirection>::iterator it;
		//for (it = moves.begin(); it != moves.end(); ++it)
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

	int& getAverage()
	{
		return average;
	}

	list<int>& getScoresList()
	{
		return scores;
	}
};

#endif