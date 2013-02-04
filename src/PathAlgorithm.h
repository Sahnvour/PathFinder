#pragma once

#include <vector>
#include "Step.h"

// Base class for implementing your own algorithms. Pure virtual methods
// ( getPath() and releaseSteps() ) should be defined.
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

		virtual bool getPath(std::vector<Step*>& path, Distance mode = FAST_EUCLIDEAN) = 0;
		virtual void releaseSteps() = 0;

		void setDistanceMode(Distance mode);
		void setGoal(Step* goal);
		void setStart(Step* start);
		Distance getDistanceMode() const;

	protected:
		float distanceBetween(Step* s1, Step* s2) const;
		float realDistanceFromStart(Step* step) const;
		float distanceToGoal(Step* step) const;

		void reconstructPath(Step* step, std::vector<Step*>& path);

		Step* m_start, *m_goal;
		Distance m_distanceMode;		
};