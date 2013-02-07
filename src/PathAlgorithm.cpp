#include "PathAlgorithm.h"

/*PathAlgorithm::PathAlgorithm()
{
	m_start = m_goal = nullptr;
}

PathAlgorithm::~PathAlgorithm(void)
{
}

PathAlgorithm::Distance PathAlgorithm::getDistanceMode() const
{
	return m_distanceMode;
}

void PathAlgorithm::setDistanceMode(Distance mode)
{
	m_distanceMode = mode;
}

void PathAlgorithm::setGoal(Node* goal)
{
	m_goal = goal;
}

void PathAlgorithm::setStart(Node* start)
{
	m_start = start;
}

float PathAlgorithm::distanceBetween(Node* n1, Node* n2) const
{
	return n1->distanceTo(n2);
}

float PathAlgorithm::realDistanceFromStart(Node* node) const
{
	Node* parent = node->getParent();
	Node* current = node;
	float distance = 0.0;

	while(parent != nullptr)
	{
		distance += distanceBetween(current, parent);
		current = parent;
		parent = parent->getParent();
	}
	return distance;
}

float PathAlgorithm::distanceToGoal(Node* node) const
{
	return distanceBetween(node, m_goal);
}

void PathAlgorithm::reconstructPath(Node* node, std::vector<Node*>& path)
{
	Node* parent = node->getParent();
	path.push_back(node);
	while(parent != nullptr)
	{
		path.push_back(parent);
		parent = parent->getParent();
	}
}*/