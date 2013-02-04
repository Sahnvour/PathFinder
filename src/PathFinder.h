#pragma once
#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include "PathAlgorithm.h"

template <class T> // The class derived from Step the user is working with, to avoid him having to cast some things.
class PathFinder
{
	public:
		PathFinder(void);
		PathFinder(PathAlgorithm* algorithm);
		~PathFinder(void);

		void setAlgorithm(PathAlgorithm* algorithm);
		void setStart(T* start);
		void setGoal(T* goal);

		bool getPath(std::vector<T*>& solution);

	private:
		PathAlgorithm* m_algorithm;
		T* m_start, *m_goal;
		std::vector<Step*> path;
		std::vector<Step*>::reverse_iterator rit;
};

#include "PathFinder.cpp"

#endif