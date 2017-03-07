//
//  Map.cpp
//  MDP
//
//  Created by 黄正跃 on 4/30/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#include "Map.h"
#include <QtCore/QDebug>
//Map::Map(int _width,int _height):width(_width),height(_height){
//    
//    //allocate memory
//    map=new MapBlock*[width];
//    for(int i=0;i<width;i++){
//        map[i]=new MapBlock[height];
//    }
//
//}

Map::Map(int _width, int _height, std::string** input_map) :width(_width), height(_height) {

	//allocate memory
	map = new MapBlock*[width];
	for (int i = 0; i < width; i++) {
		map[i] = new MapBlock[height];
	}
	initMap(input_map);

}

void Map::initMap(std::string** input_map) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			if (0 == input_map[i][j].compare("0")) {
				map[i][j].setReward(0);
			}
			else if (0 == input_map[i][j].compare("#")) {
				map[i][j].setWall();
				map[i][j].setReward(0);
			}
			else {
				map[i][j].setReward(atof(input_map[i][j].c_str()));
				map[i][j].setTerminal();
			}

		}
	}
}


bool Map::isValid(int x, int y) {
	if (x < width && x >= 0 && y < height && y >= 0 && !map[x][y].isWall()) {
		return true;
	}
	else {
		return false;
	}

}


Map::~Map() {
	qDebug() << "******here************" << endl;
	//
	for (int i = 0; i < width; i++)
		delete[] map[i];
	//
	delete[] map;
}
