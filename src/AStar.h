#pragma once
#include "PathAlgorithm.h"
#include <vector>
#include <algorithm>
#include <iostream>

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
		void clear();

	private:
		bool inOpen(Node* node);
		bool inClosed(Node* node);
		void removeFromClosed(Node* node);
		void releaseOpen();
		void releaseClosed();
		
		std::vector<Node*> open, closed;
};