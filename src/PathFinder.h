#pragma once

#include <vector>
#include "PathAlgorithm.h"

template <class T>
class PathFinder
{
	public:

		PathFinder()
		{}

		void setStart(T& start)
		{
			m_start = &start;
		}

		void setGoal(T& goal)
		{
			m_goal = &goal;
		}

		T* getStart() const
		{
			return m_start;
		}

		T* getGoal() const
		{
			return m_goal;
		}

		bool getPath(PathAlgorithm<T>& algorithm, std::vector<T*>& solution)
		{
			algorithm.setGoal(m_goal);
			algorithm.setStart(m_start);
			
			path.clear();

			bool pathFound = algorithm.getPath(path);
			algorithm.clear();

			if(!pathFound)
				return false;

			for(auto rit = path.rbegin(); rit != path.rend(); ++rit)
				solution.push_back( static_cast<T*>(*rit) );

			return true;
		}

	private:
		T *m_start, *m_goal;
		std::vector<T*> path;
};
