#include <iostream>
#include "implicit_cartesian.hpp"
#include <boost/graph/graph_concepts.hpp>

int main()
{

	PeriodicCartesian<3> graph(1,2,3);
<<<<<<< HEAD
	//~ boost::AdjacencyGraphConcept< PeriodicCartesian<3> > concept;
=======
	boost::GraphConcept< PeriodicCartesian<3> > concept;
>>>>>>> e5da9d8415a06adff69355ef186412a501d9202d
	
	return 0;

}
