#pragma once
#include "PathAlgorithm.h"
#include <queue>
#include <vector>

struct CompareNodes
{
	bool operator() (const Node* s1, const Node *s2) const
	{
		return s1->getF() < s2->getF();
	}
};

// My simple implementation of A*
class AStar : public PathAlgorithm
{
	public:
		AStar(void);
		~AStar(void);
		
		bool getPath(std::vector<Node*>& path, Distance mode);
		void releaseNodes();

	private:
		bool inOpen(Node* node);
		bool inClosed(Node* node);
		void removeFromClosed(Node* node);
		void releaseOpen();
		void releaseClosed();
		
		std::deque<Node*> open;
		std::deque<Node*> closed;
};