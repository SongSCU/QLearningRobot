//
//  Map.h
//  MDP
//
//  Created by 黄正跃 on 4/30/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef Map_h
#define Map_h
#include "baseDataStruct.h"
#include <iostream>
class Map {
private:
	int width;
	int height;
	MapBlock** map;

public:
	//constructor
	Map(int _width, int _height);
	//constructor with innitial map
	Map(int _width, int _height, std::string** input_map);

	void initMap(std::string** input_map);

	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}

	bool isValid(int x, int y);

	bool isTerminal(int x, int y) {
		return map[x][y].isTerminal();
	}

	MapBlock* operator[](int x) {
		return map[x];
	}

	~Map();

};

#endif /* Map_h */
