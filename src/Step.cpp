#include "Step.h"
#include <iostream>

Step::Step(void)
{
	m_parent = nullptr;
	m_f = m_g = m_h = 0.0;
}

Step::~Step(void)
{
}

Step* Step::getParent()
{
	return m_parent;
}

std::vector<Step*>* Step::getChildren()
{
	return &m_children;
}


void Step::addChild(Step* child)
{
	m_children.push_back(child);
}

void Step::clearChildren()
{
	m_children.clear();
}

void Step::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Step::setF(float f)
{
	m_f = f;
}

void Step::setG(float g)
{
	m_g = g;
}

void Step::setH(float h)
{
	m_h = h;
}

void Step::setParent(Step* parent)
{
	m_parent = parent;
}

int Step::getX() const
{
	return m_x;
}

int Step::getY() const
{
	return m_y;
}

float Step::getF() const
{
	return m_f;
}

float Step::getG() const
{
	return m_g;
}

float Step::getH() const
{
	return m_h;
}