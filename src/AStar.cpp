#include "AStar.h"
#include <algorithm>

AStar::AStar(void)
{
}

AStar::~AStar(void)
{
}

bool AStar::getPath(std::vector<Node*>& path, Distance mode)
{
	Node *currentNode, *childNode;
	std::vector<Node*>* children;
	path.clear();
	open.clear();
	closed.clear();
	open.push_back(m_start);

	while(!open.empty())
	{
		std::sort(open.begin(), open.end(), CompareNodes()); // Not optimized : see the word document
		currentNode = open.front(); // pop n node from open for which f is minimal
		open.pop_front();
		closed.push_back(currentNode);
		
		if(*currentNode == m_goal)
		{
			reconstructPath(currentNode, path);
			return true;
		}
		
		children = currentNode->getChildren(); // for each successor n' of n
		for(std::vector<Node*>::iterator it = children->begin(); it != children->end(); ++it) // again : not optimized
		{
			childNode = *it;
			float g = realDistanceFromStart(currentNode) + distanceBetween(currentNode, childNode);
			if( (inOpen(childNode) || inClosed(childNode)) && childNode->getG() <  g) // n' is already in opend or closed with a lower cost g(n')
				continue; // consider next successor

			float h = distanceToGoal(childNode), f = g + h; // compute f(n')
			childNode->setF(f);
			childNode->setG(g);
			childNode->setH(h);
			childNode->setParent(currentNode);

			if(inClosed(childNode))
				removeFromClosed(childNode);
			if(!inOpen(childNode))
				open.push_back(childNode);
		}
	}
	return false;
}

void AStar::releaseNodes()
{
	releaseOpen();
	releaseClosed();
}

bool AStar::inOpen(Node* Node)
{
	for(openIt = open.begin(); openIt != open.end(); ++openIt)
		if(*(*openIt) == Node)
			return true;
	return false;
}

bool AStar::inClosed(Node* Node)
{
	for(closedIt = closed.begin(); closedIt != closed.end(); ++closedIt)
		if(*(*closedIt) == Node)
			return true;
	return false;
}

void AStar::removeFromClosed(Node* Node)
{
	for(closedIt = closed.begin(); closedIt != closed.end(); ++closedIt)
		if(*(*closedIt) == Node)
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