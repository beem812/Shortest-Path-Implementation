#include "shortPath.h"
#include "MapNode.h"
#include "stdafx.h"
#include "HeapComparator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


shortPath::shortPath()
{
	
}


shortPath::~shortPath()
{
}

void shortPath::buildIntMap() //Reading in binary values and storing them in MapNode objects for later processing.
{
	uint8_t map[200][250];
	FILE * mapfile;
	char finish;
	mapfile = fopen("map1.raw", "rb");
	size_t readElements = fread((void *)map, 1, 200 * 250, mapfile);
	
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 250; j++) {
			MapNode * newNode = new MapNode();
			newNode->setHeight((int)map[i][j]);
			newNode->setIndex(i,j);
			nodes[i][j] = newNode;
		}
	}
	
	
}

void shortPath::printHeights() //Diagnostic function allowing me to see if the general concept of the process function is working, not currently called in ShortestPath.cpp
{
	char finish;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << "{";
			cout << nodes[i][j]->getHeight();
			cout << ", ";
			cout << nodes[i][j]->distanceFromStart;
			cout << ", ";
			cout << nodes[i][j]->getAdjacent();
			cout << "}";
		}
		cout << endl;
	}
	cin >> finish;
}

void shortPath::processNodes() { // Calculates the shortest path to each node in the nodes array
	MapNode * activeNode;
	vector<MapNode*> min_heap; //vector to hold our frontier nodes, it will be turned in to a min heap using make_heap() and my CompareDistance struct in the HeapComparator.h file

	min_heap.push_back(nodes[0][0]);

	cout << "Processing shortest path to all pixels in map1.raw, this may take a few moments, a message will display when complete." << endl;

	make_heap(min_heap.begin(), min_heap.end(), CompareDistance());

	while (!min_heap.empty()) { //Looping until all frontier Nodes have been dealt with
		activeNode = min_heap.front(); // grabbing the current minimum distance frontier node
		pop_heap(min_heap.begin(),min_heap.end(), CompareDistance()); //removes current active frontier node from heap
		min_heap.pop_back(); //pop_heap just sets the boundary so that heap operations no longer touch the back node, this removes it fully
		activeNode->setQueueStatus(false);
		activeNode->setVisited();
		//If statements calculate the distance from start to each adjacent node through the active node and if necessary, push adjacent nodes on heap to represent frontier.
		if (activeNode->getI() - 1 >= 0) { 
			//checking if the node were looking at updates it's value, is not in the queue, and is not considered settled
			if (nodes[activeNode->getI() - 1][activeNode->getJ()]->setDistance(activeNode) && !nodes[activeNode->getI() - 1][activeNode->getJ()]->getQueueStatus()&& !nodes[activeNode->getI() - 1][activeNode->getJ()]->getVisited()) {
				//pushing on to the heap
				min_heap.push_back(nodes[activeNode->getI() - 1][activeNode->getJ()]);
				push_heap(min_heap.begin(), min_heap.end(), CompareDistance());
				nodes[activeNode->getI() - 1][activeNode->getJ()]->setQueueStatus(true);
			}
		}

		if (activeNode->getI() + 1 < 200) {
			//checking if the node were looking at updates it's value, is not in the queue, and is not considered settled
			if (nodes[activeNode->getI() + 1][activeNode->getJ()]->setDistance(activeNode)&& !nodes[activeNode->getI() + 1][activeNode->getJ()]->getQueueStatus() && !nodes[activeNode->getI() + 1][activeNode->getJ()]->getVisited()) {
				min_heap.push_back(nodes[activeNode->getI() + 1][activeNode->getJ()]);
				push_heap(min_heap.begin(), min_heap.end(), CompareDistance());
				nodes[activeNode->getI() + 1][activeNode->getJ()]->setQueueStatus(true);
			}
		}

		if (activeNode->getJ() - 1 >= 0) {
			//checking if the node were looking at updates it's value, is not in the queue, and is not considered settled
			if (nodes[activeNode->getI()][activeNode->getJ() - 1]->setDistance(activeNode) && !nodes[activeNode->getI()][activeNode->getJ() - 1]->getQueueStatus() && !nodes[activeNode->getI()][activeNode->getJ() - 1]->getVisited()) {
				min_heap.push_back(nodes[activeNode->getI()][activeNode->getJ() - 1]);
				push_heap(min_heap.begin(), min_heap.end(), CompareDistance());
				nodes[activeNode->getI()][activeNode->getJ() - 1]->setQueueStatus(true);
			}
		}

		if (activeNode->getJ() + 1 < 250) { // if the value of j is in range 
			//checking if the node were looking at updates it's value, is not in the queue, and is not considered settled
			if (nodes[activeNode->getI()][activeNode->getJ() + 1]->setDistance(activeNode) && !nodes[activeNode->getI()][activeNode->getJ() + 1]->getQueueStatus() && !nodes[activeNode->getI()][activeNode->getJ() + 1]->getVisited()) {
				//pushing on to the heap
				min_heap.push_back(nodes[activeNode->getI()][activeNode->getJ() + 1]);
				push_heap(min_heap.begin(), min_heap.end(), CompareDistance());
				nodes[activeNode->getI()][activeNode->getJ() + 1]->setQueueStatus(true);

			}
		}
		make_heap(min_heap.begin(), min_heap.end(), CompareDistance()); //The heap is rebuilt here each iteration 
	}                                                                   //because each iteration contains commands to edit the comparrison values of the objects on the heap 
		                                                                //which will result in errors if you try to user other heap commands on an improperly built heap.
																	    //Possible to hide this command behind an if statement to keep it from firing when nothing has been updated.
	                                                                    //May be a better data structure that doesn't require processing the all the data every pass.
}
/*Shortest Adjacent:
North: 50,
East: 100,
South: 150,
West: 200
*/
void shortPath::generateImage() { // Generates a raw file filled with a value for each node or pixel 
	uint8_t north = 50;           // representing what direction the pixel was approached from on its shortest path from the [0][0] point
	uint8_t east = 100;
	uint8_t south = 150;
	uint8_t west = 200;
	int adjacent;
	ofstream myfile("map2.raw", ios::out | ios::binary);

	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 250; j++) {
			 
			switch (nodes[i][j]->getAdjacent()) {
			case 50:
				myfile.write((char*)&north, 1);
				break;
			case 100:
				myfile.write((char*)&east, 1);
				break;
			case 150:
				myfile.write((char*)&south, 1);
				break;
			case 200:
				myfile.write((char*)&west, 1);
				break;
			}

		}
	}
}
/*Shortest Adjacent:
North: 50,
East: 100,
South: 150,
West: 200
*/
void shortPath::markShortPath() { //drawing the shortest path from the top left node [0][0] to the bottom right node [199][249]
	uint8_t colorMap[200][250] = { 0 };
	colorMap[199][249] = 250;
	MapNode *activeNode = nodes[199][249];
	char finish;
	while (colorMap[0][0] == 0) {
		switch (activeNode->getAdjacent()) { // Switch moving the active node to the next node in the shortest path
		case 50:			                // getAdjacent() returns an int value that's mapped to a cardinal direction representing how the shortest path algo got to the current node, 
										   //  the active pointer is changed to the node "North, East, West, or South" of the current active position.
			activeNode = nodes[activeNode->getI() - 1][activeNode->getJ()];//
			break;
		case 100:
			activeNode = nodes[activeNode->getI()][activeNode->getJ()+1];
			break;
		case 150:
			activeNode = nodes[activeNode->getI() + 1 ][activeNode->getJ()];
			break;
		case 200:
			activeNode = nodes[activeNode->getI() ][activeNode->getJ() - 1];
			break;
		}
		colorMap[activeNode->getI()][activeNode->getJ()] = 250; //Setting the new active node, which is confirmed to be on the shortest path, to the color white in our color map
	}
	ofstream myfile("path.raw", ios::out | ios::binary);//writing binary in to our path.raw file which will show the shortest path in white on a black background.
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 250; j++) {
			myfile.write((char*)&colorMap[i][j], 1);
		}
	}
	cout << "The shortest paths to all pixels in the image have been processed, and the shortest path from the top left to the bottom right pixel has been drawn, Press any key and hit enter to exit." << endl;
	cin >> finish;

}