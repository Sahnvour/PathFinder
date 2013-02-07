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

		//virtual bool operator==(Node* Node) const = 0;

		void setParent(Node* parent);

		Node* getParent();

		std::vector<Node*>* getChildren();

		// bool pollChild(Node*& child);  ----> Maybe later
		virtual void setupChildren() = 0;
		
		//virtual float distanceTo(Node* Node) = 0;

	protected:
		void addChild(Node* child);
		void clearChildren();

		// Basic node information for many (all ?) research algorithm
		Node* m_parent;

		std::vector<Node*> m_children;	
};