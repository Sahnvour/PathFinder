#pragma once

#include <vector>

// This class is abstract, therefore it can not be instanciated or used as-is.
// You must derive it into a class of your own, and define the pure virtual methods
// ( operator==(), setupchildren() and distanceTo() ) the way you want to fit your needs.
class Node
{

	public:

		Node(void);
		~Node(void);

		virtual bool operator==(Node* Node) const = 0;

		void setPosition(int x, int y);
		void setF(float f);
		void setG(float g);
		void setH(float h);
		void setParent(Node* parent);

		inline int Node::getX() const
		{
			return m_x;
		}

		inline int Node::getY() const
		{
			return m_y;
		}

		inline float Node::getF() const
		{
			return m_f;
		}

		inline float Node::getG() const
		{
			return m_g;
		}

		inline float Node::getH() const
		{
			return m_h;
		}

		Node* getParent();

		std::vector<Node*>* getChildren();

		// bool pollChild(Node*& child);  ----> Maybe later
		virtual void setupChildren() = 0;
		
		virtual float distanceTo(Node* Node) = 0;

	protected:
		void addChild(Node* child);
		void clearChildren();

		// Basic Node/node information for many (all ?) research algorithm
		Node* m_parent;
		float m_f, m_g, m_h;
		int m_x, m_y;

		std::vector<Node*> m_children;	
};