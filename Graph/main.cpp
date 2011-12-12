#include <iostream>
#include "implicit_cartesian.hpp"
#include <boost/graph/graph_concepts.hpp>

int main(int argc, char *argv[])
{
	PeriodicCartesian<3> graph(1,2,3);
	//boost::AdjacencyGraphConcept< PeriodicCartesian<3> > concept;
	
	return 0;

}
