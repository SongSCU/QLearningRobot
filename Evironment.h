//
//  Evironment.h
//  Q-Learning
//
//  Created by 黄正跃 on 5/2/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef Evironment_h
#define Evironment_h
#include "Map.h"
#include "baseDataStruct.h"
#include <iostream>

class Evironment {
private:
	double noise;
	double living_reward;

	Map *map;

	int direction[4][2] = {
		{0,1},//up
		{1,0},//right
		{0,-1},//down
		{-1,0}//left
	};

	static Evironment* evironment;

	Evironment(int _width, int _height, std::string** input_map, double _noise, double _living_reward);

public:

    void setNoise(double p_noise){
        this->noise=p_noise;
    }
    void setLivingReward(double p_livingReward){
        this->living_reward=p_livingReward;
    }
	static Evironment*create(int width, int height, std::string** input_map, double _noise, double _living_reward) {
        //if (nullptr == evironment) {
			evironment = new Evironment(width, height, input_map, _noise, _living_reward);
        //}
		return evironment;
	}

	//must be called after create()
	static Evironment* getInstance() {
        if (evironment == nullptr) {
			std::cerr << "Evironment has not been created!" << std::endl;
        }

		return evironment;
	}

	EvironmentFeedBack getNextState(const Vect2& pos, int action);

	EvironmentFeedBack getNextState(int x, int y, int action);


	bool isValid(const Vect2& pos) {
		return map->isValid(pos.x, pos.y);
	}

	bool isTerminal(const Vect2& pos) {
		return (*map)[pos.x][pos.y].isTerminal();
	}

	//destructor
	~Evironment() {
		delete map;
	}

};

#endif /* Evironment_h */
