#pragma once

#include "PathAlgorithm.h"
#include "Node.h"
#include <vector>

class DjikstraNode : public Node
{
	static const float infinity;

	public:
		DjikstraNode() :
			distance(infinity),
			closed(false)
		{}

		~DjikstraNode()
		{}

		void setClosed(bool value)
		{
			closed = value;
		}

		void setDistance(float value)
		{
			distance = value;
		}

		inline bool isClosed() const
		{
			return closed;
		}

		inline float getDistance() const
		{
			return distance;
		}

		void release()
		{
			distance = infinity;
			closed = false;
			m_parent = nullptr;
		}

	protected:
		bool closed;
		float distance;
};


struct CompareNodes
{
	bool operator() (const DjikstraNode* n1, const DjikstraNode* n2)
	{
		return n1->getDistance() < n2->getDistance();
	}
};


class Djikstra : public PathAlgorithm<DjikstraNode>
{
	public:
		Djikstra();
		~Djikstra();

		bool getPath(std::vector<DjikstraNode*>& path);
		void clear();

	private:
		void pushOpen(DjikstraNode* node);
		void popOpen(DjikstraNode* node);
		void releaseNodes();

		std::vector<DjikstraNode*> open, closed;
};