#pragma once
#include "PathAlgorithm.h"
#include <queue>
#include <vector>

// My implementation of A*
class AStar : public PathAlgorithm
{
	public:
		AStar(void);
		~AStar(void);
		
		bool getPath(std::vector<Node*>& path, Distance mode);
		void releaseNodes();

	private:
		bool inOpen(Node* Node);
		bool inClosed(Node* Node);
		void removeFromClosed(Node* Node);
		void releaseOpen();
		void releaseClosed();
		
		std::deque<Node*> open;
		std::deque<Node*>::iterator openIt;
		std::deque<Node*> closed;
		std::deque<Node*>::iterator closedIt;
};

// Struct used for the std::sort algorithm
struct CompareNodes
{
	bool operator() (const Node* s1, const Node *s2) const
	{
		return s1->getF() < s2->getF();
	}
};