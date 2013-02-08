#pragma once
#include "PathAlgorithm.h"
#include <vector>
#include <algorithm>
#include <iostream>

class AStarNode : public Node
{
	public:

		AStarNode()
		{
			m_f = m_g = m_h = 0.0;
		}

		void setPosition(int x, int y)
		{
			m_x = x;
			m_y = y;
		}

		void setF(float f)
		{
			m_f = f;
		}

		void setG(float g)
		{
			m_g = g;
		}

		void setH(float h)
		{
			m_h = h;
		}

		inline int getX() const
		{
			return m_x;
		}

		inline int getY() const
		{
			return m_y;
		}

		inline float getF() const
		{
			return m_f;
		}

		inline float getG() const
		{
			return m_g;
		}

		inline float getH() const
		{
			return m_h;
		}

		inline bool isOpen() const
		{
			return open;
		}

		inline bool isClosed() const
		{
			return closed;
		}

		std::vector<AStarNode*>& getChildren()
		{
			return reinterpret_cast<std::vector<AStarNode*>&>(m_children);
		}

		float distanceTo(AStarNode* node)
		{
			int newX = m_x - node->getX(), newY = m_y - node->getY();
			return static_cast<float>(sqrt(newX*newX + newY*newY)); // euclidean distance
			// Note : fast euclidean (no square root) does not give good results
		}

	protected:
		float m_f, m_g, m_h;
		int m_x, m_y;
		bool open, closed;
};

struct CompareNodes
{
	bool operator() (const AStarNode* s1, const AStarNode *s2) const
	{
		return s1->getF() < s2->getF();
	}
};

class AStar : public PathAlgorithm<AStarNode>
{
	public:
		AStar(void);
		~AStar(void);
		
		bool getPath(std::vector<AStarNode*>& path, Distance mode);
		void releaseNodes();
		void clear();

	private:
		bool inOpen(Node* node);
		bool inClosed(Node* node);
		void removeFromClosed(Node* node);
		void releaseOpen();
		void releaseClosed();
		
		std::vector<AStarNode*> open, closed;
};