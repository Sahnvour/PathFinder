PathFinder
==========

A small but convenient C++ path finding library.

## What how why

PathFinder is a _really originally_ named library built for path finding in C++. It aims at providing a set of classic algorithms that are widely used such as A* or Djikstra's, for a generic purpose. It also offers an easy base for prototyping your own specific (or not) algorithms.

I started this project while having a course on Artificial Intelligence Programming, and decided to work a bit more on it for learning. It is quite simple actually but if it can be of any use, please test it ! I'd be very glad to have any comments on this, because I'm sure it is far from being perfect.

Yet, the A* is working well so far and gives me satisfying results (though I did not compare it with anything else) even for complex labyrinths with 100 000s of nodes.

## Usage

You will (soon) find a few different examples in the appropriate folder, illustrating how to use PathFinder for solving a pictured labyrinth or finding a path on a road network.

###### Example

Here is a short overview of what is required to get a built-in algorithm to work on your own collection of nodes. The most important thing you have to do yourself is to implement the way your nodes will be related to each other and how to calculate the distance between two linked nodes. The A* will take care of everything else

```c++
#include <vector>
#include <iostream>
#include "PathFinder.h"
#include "AStar.h"

class MyNode : AStarNode
{
	/*
		Implement the pure virtual methods from AStarNode
	*/
};

int main()
{
	PathFinder<AStarNode> myFinder;
	AStar astar;
	
	std::vector<AStarNode*> path;
	MyNode nodes[100];
	
	for(int i = 0; i < 100; ++i)
	{
		// Do your stuff here to link nodes between them as needed
		// by using Node::addChild()
	}
	
	// Let's say we want the path from the first node to the last one ...
	myFinder.setStart(nodes[0]);
	myFinder.setGoal(nodes[99]);
	// ... and that's it !
	bool result = myFinder.findPath(astar, path);
	
	if(result)
		std::cout << "Success ! A path has been found." << std::endl;
	else
		std::cout << "Erk, it seems there is no way through." << std::endl;
	
	return 0;
}
```

## Building

There is no extra dependency for the core library.

I have only tested it on my computer (Win7 x86_64, Visual Studio 2012 CTP November) but it should be able to compile on any system with a C++ compiler that supports C++0x. Note that there is a bug with the heap in the AStar algorithm that triggers an exception in debug mode, but the release executable works well.
