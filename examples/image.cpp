/*
		USAGE

This example takes an image and searchs a path between
2 points user-defined. Pure white RGB(255,255,255) is a
"walkable" pixel ans any other color is a wall.
Produce an image solution named solution.png

Run with 5 arguments :
output_exe filename x1 y1 x2 y2
with filename the name of the image file (should work
on .jpg, .png, .bmp and all formats supported by SFML)
x1 y1 the coordinates of the start pixel
x2 y2 the coordinates of the goal pixel

don't forget that a 100*100 image has pixels coordinates
in range [0;99]

*/



#include "../src/PathFinder.h"
#include "../src/AStar.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>


/*
Create our own class deriving AStarNode.
This is needed for applying A* Algorithm to our squares.
*/

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

		// A diagonal move has a sqrt(2) cost, 1 otherwise
		float localDistanceTo(AStarNode* node) const
		{
			if(node->getX() != m_x && node->getY() != m_y)
				return 1.41421356237f;
			else
				return 1.0f;
		}

		float distanceTo(AStarNode* node) const
		{
			int newX = m_x - node->getX(), newY = m_y - node->getY();
			return static_cast<float>(sqrt(newX*newX + newY*newY));
		}

	private:
		// To tell wether a pixel is "walkable" or not
		bool m_type;
};

int main(int argc, char** argv)
{
	// Create the PathFinding stuff and the SFML image to load the image
	AStar astar;
	PathFinder<AStarNode> p;
	
	sf::Image image;
	std::vector<AStarNode*> path;

	// 5 arguments + program name = 6
	if(argc != 6)
	{
		std::cerr << "Invalid number of arguments provided (got " << argc << ", expected 6), type to exit." << std::endl;
		return 0;
	}

	// test the image loading
	std::string filename(argv[1]);
	if(!image.loadFromFile(filename))
	{
		std::cerr << "Failed to load '" << filename << "', type to exit." << std::endl;
		return 0;
	}
	int width = image.getSize().x,
		height = image.getSize().y;

	// We'll assume the user gave coordinates that are actually possible in this image
	unsigned int	x1 = atoi(argv[2]),
					y1 = atoi(argv[3]),
					x2 = atoi(argv[4]),
					y2 = atoi(argv[5]);
	
	/* 	Now let's create the nodes, one for each pixel
		the SFML stuff is pretty self-explanatory	 */
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

	/*
		And setup the relations between nodes. In this case,
		we want to create a link between pixels that are
		next to each other (so that a pixel has 8 neighbours)
	*/
	int newX, newY;
	Square *aChild;
	for(int x = 0; x < width; ++x)
		for(int y = 0; y < height; ++y) // traverse all squares
		{
			for(int i = -1; i < 2; ++i)
			{
				newX = squares[x][y].getX() + i;
				for(int j = -1; j < 2; ++j) // for all squares in this 3*3 square
				{
					newY = squares[x][y].getY() + j;
					if( newX > -1 && newX < width && newY > -1 && newY < height ) // be sure not to go outside the limits
					{
						aChild = &(squares[newX][newY]);
						if( aChild->getType() && (newX != x || newY != y) ) // only take free squares and not the one we are examining
							squares[x][y].addChild(aChild, squares[x][y].localDistanceTo(aChild));
					}
				}
			}
		}

	p.setStart(squares[x1][y1]);
	p.setGoal(squares[x2][y2]);

	std::cout << "Searching for path in '" << filename << "' from pixel(" << x1 << "," << y1 << ") to pixel(" << x2 << "," << y2 << ") ..." << std::endl;

	// Do some timing stuff for fun
	auto before = std::chrono::high_resolution_clock::now();
	bool r = p.findPath(astar, path);
	auto after = std::chrono::high_resolution_clock::now();
	auto diff = after - before;
	float count = std::chrono::duration<float, std::milli>(diff).count();

	std::cout << (r ? "success" : "failure") <<  " time : " << count << "ms" << std::endl;
	std::cout << "path size : " << path.size() << std::endl;

	// Modify the image to draw the solution and save it
	for(const auto& square : path)
		image.setPixel(square->getX(), square->getY(), sf::Color::Red);
	image.saveToFile("solution.png");

	for(unsigned short int x = 0; x < width; ++x)
		delete[] squares[x];
	delete[] squares;

	return 0;
}