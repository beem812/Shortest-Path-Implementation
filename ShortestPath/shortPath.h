#pragma once
#include <vector>
#include "MapNode.h"
class shortPath
{
private:
	MapNode * nodes[200][250];
public:
	shortPath();
	~shortPath();
	void buildIntMap();
	void printHeights();
	void processNodes();
	void generateImage();
	void markShortPath();
};

