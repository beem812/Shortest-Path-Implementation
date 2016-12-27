#pragma once

/*
	Custom comparrison operator to allow the Heap to work with MapNode objects
*/

struct CompareDistance {
	bool operator()(const MapNode *node1, const MapNode * node2) {
		return node1->distanceFromStart > node2->distanceFromStart;
	}
	//MAY HAVE TO MAKE THESE MEMBERS PUBLIC AND NOT HIDDEN BEHIND A FUNCTION
};
