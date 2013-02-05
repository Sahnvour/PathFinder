#include "Node.h"
#include <iostream>

Node::Node(void)
{
	m_parent = nullptr;
	m_f = m_g = m_h = 0.0;
}

Node::~Node(void)
{
}

Node* Node::getParent()
{
	return m_parent;
}

std::vector<Node*>* Node::getChildren()
{
	return &m_children;
}


void Node::addChild(Node* child)
{
	m_children.push_back(child);
}

void Node::clearChildren()
{
	m_children.clear();
}

void Node::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Node::setF(float f)
{
	m_f = f;
}

void Node::setG(float g)
{
	m_g = g;
}

void Node::setH(float h)
{
	m_h = h;
}

void Node::setParent(Node* parent)
{
	m_parent = parent;
}

