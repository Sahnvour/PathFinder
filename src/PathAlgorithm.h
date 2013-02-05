#pragma once

#include <vector>
#include "Node.h"

// Base class for implementing your own algorithms. Pure virtual methods
// ( getPath() and releaseNodes() ) should be defined.
class PathAlgorithm
{
	public:
		
		PathAlgorithm();
		~PathAlgorithm(void);

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

		void setDistanceMode(Distance mode);
		void setGoal(Node* goal);
		void setStart(Node* start);
		Distance getDistanceMode() const;

	protected:
		float distanceBetween(Node* n1, Node* n2) const;
		float realDistanceFromStart(Node* node) const;
		float distanceToGoal(Node* node) const;

		void reconstructPath(Node* node, std::vector<Node*>& path);

		Node* m_start, *m_goal;
		Distance m_distanceMode;		
};