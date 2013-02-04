#include "PathAlgorithm.h"

PathAlgorithm::PathAlgorithm()
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

void PathAlgorithm::setGoal(Step* goal)
{
	m_goal = goal;
}

void PathAlgorithm::setStart(Step* start)
{
	m_start = start;
}

// Uses the user implementation of Step::distanceTo
float PathAlgorithm::distanceBetween(Step* s1, Step* s2) const
{
	return s1->distanceTo(s2);
}

float PathAlgorithm::realDistanceFromStart(Step* step) const
{
	Step* parent = step->getParent();
	Step* current = step;
	float distance = 0.0;

	while(parent != nullptr)
	{
		distance += distanceBetween(current, parent);
		current = parent;
		parent = parent->getParent();
	}
	return distance;
}

float PathAlgorithm::distanceToGoal(Step* step) const
{
	return distanceBetween(step, m_goal);
}

void PathAlgorithm::reconstructPath(Step* step, std::vector<Step*>& path)
{
	Step* parent = step->getParent();
	path.push_back(step);
	while(parent != nullptr)
	{
		path.push_back(parent);
		parent = parent->getParent();
	}
}