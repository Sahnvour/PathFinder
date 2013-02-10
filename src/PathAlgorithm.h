#pragma once

#include <vector>

template<class T>
class PathAlgorithm
{
	public:
		
		virtual bool getPath(std::vector<T*>& path) = 0;
		virtual void clear() = 0;

		PathAlgorithm()
		{
			m_start = m_goal = nullptr;
		}

		virtual ~PathAlgorithm()
		{}

		void setGoal(T* goal)
		{
			m_goal = goal;
		}

		void setStart(T* start)
		{
			m_start = start;
		}

	protected:

		inline float distanceBetween(T* n1, T* n2) const
		{
			return n1->distanceTo(n2);
		}

		inline float localDistanceBetween(T* n1, T* n2) const
		{
			return n1->localDistanceTo(n2);
		}

		inline float distanceToGoal(T* node) const
		{
			return distanceBetween(node, m_goal);
		}

		void reconstructPath(T* node, std::vector<T*>& path)
		{
			T* parent = static_cast<T*>(node->getParent());
			path.push_back(node);
			while(parent != nullptr)
			{
				path.push_back(parent);
				parent = static_cast<T*>(parent->getParent());
			}
		}

		T* m_start, *m_goal;
};
