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
		std::priority_queue<Node*, std::deque<Node*>, CompareNodes> open_queue;
		std::deque<Node*> closed;
		std::priority_queue<Node*, std::deque<Node*>, CompareNodes> closed_queue;
};