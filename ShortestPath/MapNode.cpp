#include "MapNode.h"
#include <climits>
#include <math.h>
#include <iostream>
using namespace std;

MapNode::MapNode()
{
	shortestAdjacent = 0;
	height = 0;
	distanceFromStart = INT_MAX;
	visited = false;
	inqueue = false;
}
/*Shortest Adjacent:
	North: 50,
	East: 100,
	South: 150,
	West: 200
*/
MapNode::~MapNode()
{
}

void MapNode::setHeight(int in_height)
{
	height = in_height;
}

int MapNode::getHeight() { //returns Height of THIS node
	return height;
}

void MapNode::setIndex(int i, int j) { //sets index for THIS node
	iIndex = i;
	jIndex = j;
	if (i == 0 && j == 0) {
		distanceFromStart = 0;
	}
}

int MapNode::getI() {//row index of THIS node
	return iIndex;
}

int MapNode::getJ() {//column index of THIS node
	return jIndex;
}

bool MapNode::setDistance(MapNode * comparator) {
	if (comparator->distanceFromStart > distanceFromStart) {
		return false;
	}

	float calculatedCost = sqrt(1 + (height - comparator->getHeight())*(height - comparator->getHeight())); //generating cost of movement to THIS node
	
	float calculatedDistance = calculatedCost + comparator->distanceFromStart; //generating distance from origin through comparator node to THIS node
	
	if (calculatedDistance < distanceFromStart) {
		distanceFromStart = calculatedDistance;
		/*Shortest Adjacent:
		North: 50,
		East: 100,
		South: 150,
		West: 200
		*/
		if (iIndex == comparator->getI()) { //Big mess of if statements determining where the path is coming from
			if (jIndex < comparator->getJ()) {
				shortestAdjacent = 100;
			}
			else {
				shortestAdjacent = 200;
			}
		}
		else if (iIndex > comparator->getI()) {
			shortestAdjacent = 50;
		}
		else {
			shortestAdjacent = 150;
		}
		return true;
	}
	return false;
}

float MapNode::getDistance() { //returns distance from origin
	return distanceFromStart;
}

void MapNode::setVisited() { 
	visited = true;
}

bool MapNode::getVisited() {
	return visited;
}

bool MapNode::getQueueStatus() { //queue status determines if THIS node should go on the heap in the process function
	return inqueue;
}

void MapNode::setQueueStatus(bool status) { //queue status determines if THIS node should go on the heap in the process function
	inqueue = status;
}

int MapNode::getAdjacent() { //adjacent value shows where the shortest path came from to reach this node
	return shortestAdjacent;
}

