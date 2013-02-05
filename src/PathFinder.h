#pragma once
#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include "PathAlgorithm.h"

template <class T>
class PathFinder
{
	public:

		PathFinder()
		{
		}

		PathFinder(PathAlgorithm* algorithm)
		{
			m_algorithm = algorithm;
		}

		void setAlgorithm(PathAlgorithm* algorithm)
		{
			m_algorithm = algorithm;
		}

		void setStart(T* start)
		{
			m_start = start;
		}

		void setGoal(T* goal)
		{
			m_goal = goal;
		}

		bool getPath(std::vector<T*>& solution)
		{
			m_algorithm->setGoal(m_goal);
			m_algorithm->setStart(m_start);
			//solution.clear();
			path.clear();

			// Get the path from the search algorithm
			bool pathFound = m_algorithm->getPath(path);
			m_algorithm->releaseNodes(); // don't forget to release the Nodes, if they are reused to find another path ...

			// Fill in solution backwards, because the path algorithm gives Nodes from goal to start
			for(rit = path.rbegin(); rit != path.rend(); ++rit)
				solution.push_back( static_cast<T*>(*rit) );

			return pathFound;
		}

	private:
		PathAlgorithm* m_algorithm;
		T* m_start, *m_goal;
		std::vector<Node*> path;
		std::vector<Node*>::reverse_iterator rit;
};

#endif