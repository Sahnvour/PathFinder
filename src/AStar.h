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
		
		bool getPath(std::vector<Step*>& path, Distance mode);
		void releaseSteps();

	private:
		bool inOpen(Step* step);
		bool inClosed(Step* step);
		void removeFromClosed(Step* step);
		void releaseOpen();
		void releaseClosed();
		
		std::deque<Step*> open;
		std::deque<Step*>::iterator openIt;
		std::deque<Step*> closed;
		std::deque<Step*>::iterator closedIt;
};

// Struct used for the std::sort algorithm
struct CompareSteps
{
	bool operator() (const Step* s1, const Step *s2) const
	{
		return s1->getF() < s2->getF();
	}
};