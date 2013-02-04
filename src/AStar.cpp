#include "AStar.h"
#include <algorithm>

AStar::AStar(void)
{
}

AStar::~AStar(void)
{
}

bool AStar::getPath(std::vector<Step*>& path, Distance mode)
{
	Step *currentStep, *childStep;
	std::vector<Step*>* children;
	path.clear();
	open.clear();
	closed.clear();
	open.push_back(m_start);

	while(!open.empty())
	{
		std::sort(open.begin(), open.end(), CompareSteps()); // Not optimized : see the word document
		currentStep = open.front(); // pop n node from open for which f is minimal
		open.pop_front();
		closed.push_back(currentStep);
		
		if(*currentStep == m_goal)
		{
			reconstructPath(currentStep, path);
			return true;
		}
		
		children = currentStep->getChildren(); // for each successor n' of n
		for(std::vector<Step*>::iterator it = children->begin(); it != children->end(); ++it) // again : not optimized
		{
			childStep = *it;
			float g = realDistanceFromStart(currentStep) + distanceBetween(currentStep, childStep);
			if( (inOpen(childStep) || inClosed(childStep)) && childStep->getG() <  g) // n' is already in opend or closed with a lower cost g(n')
				continue; // consider next successor

			float h = distanceToGoal(childStep), f = g + h; // compute f(n')
			childStep->setF(f);
			childStep->setG(g);
			childStep->setH(h);
			childStep->setParent(currentStep);

			if(inClosed(childStep))
				removeFromClosed(childStep);
			if(!inOpen(childStep))
				open.push_back(childStep);
		}
	}
	return false;
}

void AStar::releaseSteps()
{
	releaseOpen();
	releaseClosed();
}

bool AStar::inOpen(Step* step)
{
	for(openIt = open.begin(); openIt != open.end(); ++openIt)
		if(*(*openIt) == step)
			return true;
	return false;
}

bool AStar::inClosed(Step* step)
{
	for(closedIt = closed.begin(); closedIt != closed.end(); ++closedIt)
		if(*(*closedIt) == step)
			return true;
	return false;
}

void AStar::removeFromClosed(Step* step)
{
	for(closedIt = closed.begin(); closedIt != closed.end(); ++closedIt)
		if(*(*closedIt) == step)
		{
			closed.erase(closedIt);
			break;
		}
}

void AStar::releaseOpen()
{
	for(openIt = open.begin(); openIt != open.end(); ++openIt)
	{
		(*openIt)->setF(0.0f);
		(*openIt)->setG(0.0f);
		(*openIt)->setH(0.0f);
		(*openIt)->setParent(nullptr);
	}
}

void AStar::releaseClosed()
{
	for(closedIt = closed.begin(); closedIt != closed.end(); ++closedIt)
	{
		(*closedIt)->setF(0.0f);
		(*closedIt)->setG(0.0f);
		(*closedIt)->setH(0.0f);
		(*closedIt)->setParent(nullptr);
	}
}