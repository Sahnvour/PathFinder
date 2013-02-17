#include "Djikstra.h"

#include <limits>
#include <algorithm>

const float DjikstraNode::infinity = std::numeric_limits<float>::infinity();

Djikstra::Djikstra()
{}

Djikstra::~Djikstra()
{}

bool Djikstra::getPath(std::vector<DjikstraNode*>& path)
{
	DjikstraNode *currentNode, *childNode;
	float dist;

	std::make_heap(open.begin(), open.end(), CompareNodes());
	pushOpen(m_start);
	m_start->setDistance(0.0f);

	while(!open.empty())
	{
		std::sort(open.begin(), open.end(), CompareNodes());

		currentNode = open.front();
		popOpen(currentNode);

		if(currentNode == m_goal)
		{
			reconstructPath(currentNode, path);
			return true;
		}

		for(const auto& children : currentNode->getChildren())
		{
			childNode = static_cast<DjikstraNode*>(children.first);
			
			dist = currentNode->getDistance() + children.second;
			if(!childNode->isClosed() && dist < childNode->getDistance())
			{
				childNode->setDistance(dist);
				childNode->setParent(currentNode);
				pushOpen(childNode);
			}
		}
	}

	return false;
}

void Djikstra::pushOpen(DjikstraNode* node)
{
	open.push_back(node);
	std::push_heap(open.begin(), open.end(), CompareNodes());
}

void Djikstra::popOpen(DjikstraNode* node)
{
	std::pop_heap(open.begin(), open.end(), CompareNodes());
	open.pop_back();
	node->setClosed(true);
	closed.push_back(node);
}


void Djikstra::releaseNodes()
{
	for(const auto& node : open)
		node->release();
	for(const auto& node : closed)
		node->release();
}

void Djikstra::clear()
{
	releaseNodes();
	open.clear();
	closed.clear();
}