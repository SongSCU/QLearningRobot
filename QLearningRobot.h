//
//  QLearningRobot.h
//  Q-Learning
//
//  Created by 黄正跃 on 5/3/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef QLearningRobot_h
#define QLearningRobot_h
#include "Map.h"
#include "Evironment.h"
class QLearningRobot {
private:
	double epison;
	double alpha;
	double discount;
	////magic number ha ha~
	double k = 1;

	int startX;

	int startY;

	int width;

	int height;

	Vect2 posNow;

	ValueNode** valueMap;

	int iter;//当前迭代次数

	void processNext();

	int takeNextAction(const Vect2& pos);//influenced by epison

public:
	//constructor
	QLearningRobot(int _width, int _height, int _startX, int _startY, double _epison, double _alpha, double _discount) :width(_width), height(_height), posNow(_startX, _startY), epison(_epison), alpha(_alpha), discount(_discount), iter(0) {
		startX = _startX;
		startY = _startY;
		valueMap = new ValueNode*[width];

		for (int i = 0; i < width; i++) {
			valueMap[i] = new ValueNode[height];
		}



	}
	//
	~QLearningRobot() {
		for (int i = 0; i < width; i++)
			delete[] valueMap[i];
		delete[] valueMap;
	}
	//
	void runNextIteration(int delta);

	int getIteration() {
		return iter;
	}

	Vect2 getPositon() {
		return posNow;
	}

	//dangerous to call,this function will be replaced in next version
	ValueNode** getValueMap() {
		return valueMap;
	}

    void setEpisilon(double p_epsilon){
        epison=p_epsilon;
    }
    void setAlpha(double p_alpha){
        alpha=p_alpha;
    }
    void setDiscount(double p_discount){
        discount=p_discount;
    }

};

#endif /* QLearningRobot_h */
