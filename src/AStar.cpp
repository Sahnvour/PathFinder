#include "AStar.h"


AStar::AStar(void)
{}

AStar::~AStar(void)
{}

bool AStar::getPath(std::vector<AStarNode*>& path, Distance distance)
{
	AStarNode *currentNode, *childNode;

	std::make_heap(open.begin(), open.end(), CompareNodes());
	open.push_back(m_start);
	std::push_heap(open.begin(), open.end(), CompareNodes());
	m_start->setOpen(true);

	while(!open.empty())
	{
		std::sort_heap(open.begin(), open.end(), CompareNodes());
		currentNode = open.front(); // pop n node from open for which f is minimal

		currentNode->setOpen(false);
		std::pop_heap(open.begin(), open.end(), CompareNodes());
		open.pop_back();

		currentNode->setClosed(true);
		closed.push_back(currentNode);
		
		if(currentNode == m_goal)
		{
			reconstructPath(currentNode, path);
			return true;
		}

		for(const auto& child : currentNode->getChildren() )// for each successor n' of n
		{
			childNode = child;
			float g = realDistanceFromStart(currentNode) + distanceBetween(currentNode, childNode);
			if( (childNode->isOpen() || childNode->isClosed()) && childNode->getG() <  g) // n' is already in opend or closed with a lower cost g(n')
				continue; // consider next successor

			float h = distanceToGoal(childNode), f = g + h; // compute f(n')
			childNode->setF(f);
			childNode->setG(g);
			childNode->setH(h);
			childNode->setParent(currentNode);

			if(childNode->isClosed())
				childNode->setClosed(false);//removeFromClosed(childNode);
			if(!childNode->isOpen())
			{
				open.push_back(childNode);
				std::push_heap(open.begin(), open.end(), CompareNodes());
				childNode->setOpen(true);
			}
		}
	}
	return false;
}

void AStar::releaseNodes()
{
	for(const auto& node : open)
		node->release();
	for(const auto& node : closed)
		node->release();
}

void AStar::clear()
{
	releaseNodes();
	open.clear();
	closed.clear();
}
