#pragma once

#include <vector>

class Node
{
	public:

		Node();
		~Node();

		void setParent(Node* parent);
		Node* getParent();

		std::vector<Node*>& getChildren();
		virtual void setupChildren() = 0;

	protected:

		void addChild(Node* child);
		void clearChildren();

		Node* m_parent;

		std::vector<Node*> m_children;
};
