#pragma once

#include <vector>
#include <algorithm>
#include "PathAlgorithm.h"

class AStarNode : public Node
{
	public:

		AStarNode()
		{
			m_f = m_g = m_h = 0.0;
			closed = open = false;
			m_index = 0;
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

		void setOpen(bool value)
		{
			open = value;
		}

		void setClosed(bool value)
		{
			closed = true;
		}

		void setIndex(int value)
		{
			m_index = value;	
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

		inline int getIndex() const
		{
			return m_index;
		}

		std::vector<AStarNode*>& getChildren()
		{
			return reinterpret_cast<std::vector<AStarNode*>&>(m_children);
		}

		float distanceTo(AStarNode* node) const
		{
			int newX = m_x - node->getX(), newY = m_y - node->getY();
			return static_cast<float>(sqrt(newX*newX + newY*newY));
		}

		virtual float localDistanceTo(AStarNode* node) const = 0;

		void release()
		{
			open = closed = false;
			m_f = m_g = m_h = 0.0f;
			m_parent = nullptr;
			m_index = 0;
		}

	protected:
		float m_f, m_g, m_h;
		int m_x, m_y;
		int m_index;
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
		AStar();
		~AStar();
		
		bool getPath(std::vector<AStarNode*>& path);
		void clear();

		float realDistanceFromStart(AStarNode* node) const;

		bool isUniform() const;
		void setUniform(bool value);

	private:
		void releaseNodes();
		void pushOpen(AStarNode* node);
		void popOpen(AStarNode* node);
		
		std::vector<AStarNode*> open, closed;

		bool uniform;
};
