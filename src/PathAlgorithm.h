#pragma once

#include <vector>
#include "Node.h"

// Base class for implementing your own algorithms. Pure virtual methods
// ( getPath() and releaseNodes() ) should be defined.
template<class T>
class PathAlgorithm
{
	public:
		
		// Currently not used
		enum Distance
		{
			EUCLIDEAN,
			FAST_EUCLIDEAN,
			MANHATTAN
		};

		virtual bool getPath(std::vector<Node*>& path, Distance mode = FAST_EUCLIDEAN) = 0;
		virtual void releaseNodes() = 0;
		virtual void clear() = 0;

		PathAlgorithm()
		{
			m_start = m_goal = nullptr;
		}

		~PathAlgorithm(void)
		{
		}

		Distance getDistanceMode() const
		{
			return m_distanceMode;
		}

		void setDistanceMode(Distance mode)
		{
			m_distanceMode = mode;
		}

		void setGoal(T* goal)
		{
			m_goal = goal;
		}

		void setStart(T* start)
		{
			m_start = start;
		}

	protected:

		float distanceBetween(T* n1, T* n2) const
		{
			return n1->distanceTo(n2);
		}

		float realDistanceFromStart(T* node) const
		{
			T* parent = reinterpret_cast<T*>(node->getParent());
			T* current = node;
			float distance = 0.0;

			while(parent != nullptr)
			{
				distance += distanceBetween(current, parent);
				current = parent;
				parent = reinterpret_cast<T*>(parent->getParent());
			}
			return distance;
		}

		float distanceToGoal(T* node) const
		{
			return distanceBetween(node, m_goal);
		}

		void reconstructPath(Node* node, std::vector<Node*>& path)
		{
			Node* parent = node->getParent();
			path.push_back(node);
			while(parent != nullptr)
			{
				path.push_back(parent);
				parent = parent->getParent();
			}
		}

		T* m_start, *m_goal;
		Distance m_distanceMode;
};