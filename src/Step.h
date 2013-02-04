#pragma once

#include <vector>

// This class is abstract, therefore it can not be instanciated or used as-is.
// You must derive it into a class of your own, and define the pure virtual methods
// ( operator==(), setupchildren() and distanceTo() ) the way you want to fit your needs.
class Step
{

	public:

		Step(void);
		~Step(void);

		virtual bool operator==(Step* step) const = 0;

		void setPosition(int x, int y);
		void setF(float f);
		void setG(float g);
		void setH(float h);
		void setParent(Step* parent);

		int getX() const;
		int getY() const;
		float getF() const;
		float getG() const;
		float getH() const;
		Step* getParent();

		std::vector<Step*>* getChildren();

		// bool pollChild(Step*& child);  ----> Maybe later
		virtual void setupChildren() = 0;
		
		virtual float distanceTo(Step* step) = 0;

	protected:
		void addChild(Step* child);
		void clearChildren();

		// Basic step/node information for many (all ?) research algorithm
		Step* m_parent;
		float m_f, m_g, m_h;
		int m_x, m_y;

		std::vector<Step*> m_children;	
};