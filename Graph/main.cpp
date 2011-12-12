#include <iostream>
#include "implicit_cartesian.hpp"
#include <boost/graph/graph_concepts.hpp>

int main(int argc, char *argv[])
{
  
	if(argc>10) std::cout <<argv[1][0];

	typedef PeriodicCartesian<3> Graph_t;

	Graph_t graph(3,6,9);
	boost::AdjacencyGraphConcept< Graph_t > concept;
	
	typename Graph_t::vertex_descriptor i(1,2,3);
	std::cout << i << std::endl;
	
	std::pair<typename Graph_t::adjacency_iterator, typename Graph_t::adjacency_iterator > range
		= adjacent_vertices(i, graph);
	
	for(;range.first!=range.second;++range.first)
	{
		std::cout << *range.first << ' ';
	}
		
	
	return 0;

}
