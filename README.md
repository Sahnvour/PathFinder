PathFinder
==========

A small but convenient C++ path finding library.
Prototype easily your own search algorithms or use existing ones.

## Usage

###### Example
```c++
#include <vector>
#include "PathFinder.h"
#include "AStar.h"

class YourNode : AStarNode
{
	/*
		Implement the pure virtual methods from AStarNode (namely Node::setupChildren())
	*/
};

int main()
{
	PathFinder<AStarNode> myFinder;
	AStar astar;
	std::vector<AStarNode*> path;
	
	YourNode nodes[100];
	
	for(int i = 0; i < 100; ++i)
	{
		// Do your stuff here to link nodes between them
		nodes[i].setupChildren();
	}
	
	// Let's say we want the path from the first node to the last one ...
	myFinder.setStart(&nodes[0]);
	myFinder.setGoal(&nodes[99]);
	// ... and that's it !
	myFinder.getPath(astar, path);
	
	return 0;
}
```
