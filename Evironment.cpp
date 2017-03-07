//
//  Evironment.cpp
//  Q-Learning
//
//  Created by 黄正跃 on 5/2/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "Evironment.h"
#include <random>
#include <time.h>
Evironment* Evironment::evironment;
//constructor
Evironment::Evironment(int width, int height, std::string** input_map, double _noise, double _living_reward) :noise(_noise), living_reward(_living_reward) {
	map = new Map(width, height, input_map);

}

EvironmentFeedBack Evironment::getNextState(const Vect2& pos, int action) {
	return getNextState(pos.x, pos.y, action);
}

EvironmentFeedBack Evironment::getNextState(int x, int y, int action) {
	//random engine
	static std::default_random_engine randEngine(static_cast<int>(time(0)));
	static std::bernoulli_distribution T(1 - noise);
	static std::bernoulli_distribution b(0.5);
	int nx, ny;
	//depend on noise
	//1-noise
	if (T(randEngine)) {
		nx = x + direction[action][0];
		ny = y + direction[action][1];
	}
	else {
		//left
		if (b(randEngine)) {
			nx = x + direction[(action - 1 + 4) % 4][0];
			ny = y + direction[(action - 1 + 4) % 4][1];
		}
		//right
		else {
			nx = x + direction[(action + 1) % 4][0];
			ny = y + direction[(action + 1) % 4][1];
		}
	}

	if (map->isValid(nx, ny) && !map->isTerminal(x, y)) {
		//
		return EvironmentFeedBack(Vect2(nx, ny), living_reward, (*map)[x][y].isTerminal(), (*map)[x][y].getReward());
	}
	else {
		return EvironmentFeedBack(Vect2(x, y), living_reward, (*map)[x][y].isTerminal(), (*map)[x][y].getReward());

	}

}

