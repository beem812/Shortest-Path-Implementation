// ShortestPath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "shortPath.h"
using namespace std;

int main()
{	
	shortPath path;
	path.buildIntMap(); // read from file into nodes
	path.processNodes(); //Find shortest path for all nodes
	path.generateImage(); //writing the approach directions back to a raw file output = map2.raw
	//map2.raw is formatted such that a byte value of: 50 = approached from the north
													//100 = approached from the east
													//150 = approched form the south
													//200 = approached from the west
	path.markShortPath(); //drawing shortest path from [0][0] to [199][249] output = path.raw
    return 0;
}

