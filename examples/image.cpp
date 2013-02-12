//#include "PathGame.h"
#include "../src/PathFinder.h"
#include "../src/AStar.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <conio.h>

class Square : public AStarNode
{
	public:

		Square()
		{}

		~Square()
		{}

		void setType(const bool type)
		{
			m_type = type;
		}

		char getType() const
		{
			return m_type;
		}

		float localDistanceTo(AStarNode* node) const
		{
			return 1.f;
		}

		float distanceTo(AStarNode* node) const
		{
			int newX = m_x - node->getX(), newY = m_y - node->getY();
			return static_cast<float>(sqrt(newX*newX + newY*newY));
		}

	private:
		bool m_type;
};

int main(int argc, char** argv)
{
	AStar astar;
	PathFinder<AStarNode> p;
	
	sf::Image image;
	std::vector<AStarNode*> path;

	if(argc != 6)
	{
		std::cout << "Invalid number of arguments provided (got " << argc << ", expected 6), type to exit." << std::endl;
		_getch();
		return 0;
	}

	std::string filename(argv[1]);
	if(!image.loadFromFile(filename))
	{
		std::cout << "Failed to load '" << filename << "', type to exit." << std::endl;
		_getch();
		return 0;
	}
	int width = image.getSize().x, height = image.getSize().y;

	unsigned int x1 = atoi(argv[2]), y1 = atoi(argv[3]), x2 = atoi(argv[4]), y2 = atoi(argv[5]);
	
	Square **squares;

	squares = new Square* [width];
	for(unsigned short int x = 0; x < width; ++x)
	{
		squares[x] = new Square[height];
		for(unsigned short int y = 0; y < height; ++y)
		{
			squares[x][y].setPosition(x, y);
			squares[x][y].setType(image.getPixel(x, y) == sf::Color::White ? true : false);
		}
	}

	int newX, newY;
	Square *aChild;
	for(int x = 0; x < width; ++x)
		for(int y = 0; y < height; ++y)
		{
			for(int i = -1; i < 2; ++i)
			{
				newX = squares[x][y].getX() + i;
				for(int j = -1; j < 2; ++j)
				{
					newY = squares[x][y].getY() + j;
					if( newX > -1 && newX < width && newY > -1 && newY < height ) 
					{
						aChild = &(squares[newX][newY]);
						if( aChild->getType() && (newX != x || newY != y) )
							squares[x][y].addChild(aChild);
					}
				}
			}
		}

	p.setStart(squares[x1][y1]);
	p.setGoal(squares[x2][y2]);

	std::cout << "Searching for path in '" << filename << "' from pixel(" << x1 << "," << y1 << ") to pixel(" << x2 << "," << y2 << ") ..." << std::endl;

	path.clear();

	auto before = std::chrono::high_resolution_clock::now();
	bool r = p.findPath(astar, path);
	auto after = std::chrono::high_resolution_clock::now();
	auto diff = after - before;
	float count = std::chrono::duration<float, std::milli>(diff).count();

	std::cout << (r ? "success" : "failure") <<  " time : " << count << "ms" << std::endl;
	std::cout << "path size : " << path.size() << std::endl;

	for(const auto& square : path)
		image.setPixel(square->getX(), square->getY(), sf::Color::Red);
	image.saveToFile("solution.png");

	_getch();

	return 0;
}