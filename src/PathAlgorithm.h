#pragma once

#include <vector>

/**
	Represents a generic path finding algorithm. It can not be used
	or instanciated as-is and is provided for implementing algorithms.
	PathAlgorithm only provide general methods for use with PathFinder.

	@see PathFinder
*/
template<class T>
class PathAlgorithm
{
	public:
		
		/**
			@brief The core method of the algorithm, where the path will be evaluated.
			@param[out] path A vector of nodes which will be filled with the nodes from
			the path found, if there is one.
			@return true if a path is found, false if there isn't
		*/
		virtual bool getPath(T* start, T* goal, std::vector<T*>& path) = 0;

		/**
			@brief Provides a way for the algorithm to clean-up its data, if needed. Useful
			when storing information on nodes, for example.
		*/
		virtual void clear() = 0;

		/**
			@brief Default constructor.
		*/
		PathAlgorithm()
		{}

		/**
			@brief Destructor.
		*/
		virtual ~PathAlgorithm()
		{}

	protected:

		inline float distanceBetween(T* n1, T* n2) const
		{
			return n1->distanceTo(n2);
		}

		/**
			@brief Builds the path from the goal found back up to the start.
			@param[in] node The node from where to get the path.
			@param[out] path The vector to fill with the nodes.
		*/
		void reconstructPath(T* node, std::vector<T*>& path)
		{
			T* parent = static_cast<T*>(node->getParent());
			path.push_back(node);
			while(parent != nullptr)
			{
				path.push_back(parent);
				parent = static_cast<T*>(parent->getParent());
			}
		}
};
