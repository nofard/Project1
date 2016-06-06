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

	void addScore(int score);
	void calculateAvg();
	int& getAverage();
	list<int>& getScoresList();
};

#endif