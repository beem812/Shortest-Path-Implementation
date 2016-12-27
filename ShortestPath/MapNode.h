#pragma once
class MapNode
{
private:
	int height;
	int shortestAdjacent;
	int iIndex;
	int jIndex;
	bool visited;
	bool inqueue;
public:
	float distanceFromStart;
	MapNode();
	~MapNode();
	void setHeight(int in_height);
	int getHeight();
	void setIndex(int i, int j);
	int getI();
	int getJ();
	bool setDistance(MapNode * comparator);
	float getDistance();
	void setVisited();
	bool getVisited();
	bool getQueueStatus();
	void setQueueStatus(bool status);
	int getAdjacent();

};

