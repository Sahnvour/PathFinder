/*
		USAGE

	run the executable with 3 arguments as follow :
	output_exe filename city1 city2
	with filename the path to a text file containing
	lines in the following format : CityA CityB distance
	to represent a link between CityA and CityB
	and city1 / city2 being the start and goal

	example for France.txt :
		PathFinder.exe France.txt Lille Toulouse
*/


#include "../src/PathFinder.h"
#include "../src/Djikstra.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>


/*
Create our own class deriving DjikstraNode.
This is needed for applying Djikstra's Algorithm to our cities.
We can though implement other functionnalities we need, that's why
I am giving them a name for example.
*/
class City : public DjikstraNode
{
	public:
		City(const std::string& name = "Unknown")
		{
			this->name = name;
		}

		std::string getName() const
		{
			return name;
		}

		void setName(const std::string& name)
		{
			this->name = name;
		}

	private:
		std::string name;
};

int main(int argc, char** argv)
{
	std::map<std::string, City> cities;

	// Again, it requires 3 arguments + the program name = 4
	if(argc != 4)
	{
		std::cerr << "Invalid number of arguments provided (got " << argc << ", expected 4), type to exit." << std::endl;
		return 0;
	}

	std::string start(argv[2]), end(argv[3]);
	std::fstream file(argv[1], std::ios::in);

	if(!file)
	{
		std::cerr << "Could not open file '" << argv[1] << "', type to exit." << std::endl;
		return 0;
	}

	std::string line;
	std::string city1, city2;
	float distance;

	// We'll read the file and take the links between cities described in each line
	while(!file.eof())
	{
		file >> city1 >> city2 >> distance; // read a line
		cities[city1].setName(city1); // Dummy initialization but hey, that's not the point here,
		cities[city2].setName(city2);
		/*
			Now we have to create the links between cities in order to make
			them usable by Djikstra. A 'child' of a city is another city which
			can be directly accessed.
		*/
		cities[city1].addChild(&cities[city2], distance);
		cities[city2].addChild(&cities[city1], distance);
	}

	// Create the PathFinder and PathAlgorithm stuff
	PathFinder<DjikstraNode> p;
	Djikstra d;
	std::vector<DjikstraNode*> solution;

	// We'll assume that the user is giving correct arguments, because we deny all responsibilities !
	p.setStart(cities[start]);
	p.setGoal(cities[end]);

	std::cout << "Looking for shortest path between " << start << " and " << end << " ..." << std::endl;
	bool r = p.findPath(d, solution);

	if(r) // path found
	{
		City* city;

		std::cout << "Solution (" << solution.size()-1 << " steps) :" << std::endl;
		for(const auto& c : solution)
		{
			city = static_cast<City*>(c); // take it back as a City
			std::cout << city->getName() << " ";
		}
		std::cout << std::endl;
	}
	else
		std::cerr << "No path was found, sorry." << std::endl;

	return 0;
}