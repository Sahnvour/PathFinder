/*#ifdef PATHFINDER_H

template <class T>
PathFinder<T>::PathFinder(void)
{
}

template <class T>
PathFinder<T>::PathFinder(PathAlgorithm* algorithm)
{
	m_algorithm = algorithm;
}

template <class T>
PathFinder<T>::~PathFinder(void)
{
}

template <class T>
void PathFinder<T>::setAlgorithm(PathAlgorithm* algorithm)
{
	m_algorithm = algorithm;
}

template <class T>
void PathFinder<T>::setStart(T* start)
{
	m_start = start;
}

template <class T>
void PathFinder<T>::setGoal(T* goal)
{
	m_goal = goal;
}

template <class T>
bool PathFinder<T>::getPath(std::vector<T*>& solution)
{
	m_algorithm->setGoal(m_goal);
	m_algorithm->setStart(m_start);
	//solution.clear();
	path.clear();

	// Get the path from the search algorithm
	bool pathFound = m_algorithm->getPath(path);
	m_algorithm->releaseNodes(); // don't forget to release the Nodes, if they are reused to find another path ...

	// Fill in solution backwards, because the path algorithm gives Nodes from goal to start
	for(rit = path.rbegin(); rit != path.rend(); ++rit)
		solution.push_back( static_cast<T*>(*rit) );

	return pathFound;
}

#endif*/