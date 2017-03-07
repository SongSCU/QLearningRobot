//
//  QLearningRobot.cpp
//  Q-Learning
//
//  Created by 黄正跃 on 5/3/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//
#include "QLearningRobot.h"
#include <random>
#include <time.h>

void QLearningRobot::processNext() {

	Evironment *evironment = Evironment::getInstance();

	int action = 0;
	double sample = 0;
	double nowQvalue = 0;

	//next action depends on epison and the current policy
	action = this->takeNextAction(posNow);

	EvironmentFeedBack feedBack = evironment->getNextState(posNow, action);

	if (feedBack.isTerminal) {
		for (int i = 0; i < 4; i++) {
			valueMap[posNow.x][posNow.y].setQValue(i, feedBack.reward);
		}
		valueMap[posNow.x][posNow.y].updateValue();
		posNow = Vect2(startX, startY);
		return;
	}

	sample = discount* valueMap[feedBack.position.x][feedBack.position.y].getValue() + feedBack.livingReward;


	nowQvalue = valueMap[posNow.x][posNow.y].getQValue(action);

	valueMap[posNow.x][posNow.y].setQValue(action, (1 - alpha)*nowQvalue + alpha*sample);

	//go next state
	posNow = feedBack.position;

}

int QLearningRobot::takeNextAction(const Vect2& pos) {
	int action = 0;
	//random engine
	static std::default_random_engine randEngine(static_cast<int>(time(0)));
	static std::bernoulli_distribution T(1 - epison);
	static std::uniform_int_distribution<int> I(0, 4);
	//about (1-epison) T wiil return true
	if (T(randEngine)) {
		//exploit
		action = valueMap[pos.x][pos.y].getPolicy();

	}
	else {
		//explorer
		action = I(randEngine);

	}
	iter++;
	return action;

}

void QLearningRobot::runNextIteration(int delta) {
	int end = iter + delta;
	while (end > iter) {
		processNext();
	}
}
