#ifndef IMPLICIT_CARTESIAN_H
#define IMPLICIT_CARTESIAN_H

#include <utility>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/static_assert.hpp>


template <unsigned D>
struct vertex {
	size_t pos[D];
	size_t& operator[](size_t i) { return pos[i]; }
	size_t operator[](size_t i) const { return pos[i]; }
};

template <unsigned D>
bool operator==(const vertex<D> &a, const vertex<D> &b)
{
	for(unsigned i = 0;i<D;++i)
		if(a[i]!=b[i])
			return false;
	return true;
}


template <unsigned D>
class adjacency_iterator;

template <unsigned D>
class PeriodicCartesian {
public:
	typedef vertex<D> 							vertex_descriptor;
	typedef std::pair< vertex<D>, vertex<D> > 	edge_descriptor;
	typedef boost::undirected_tag				directed_category;
	typedef boost::disallow_parallel_edge_tag	edge_parallel_category;
	typedef boost::adjacency_graph_tag			traversal_category;
	typedef adjacency_iterator<D>				adjacency_iterator;
	
	PeriodicCartesian(size_t d1)
	{ 
		BOOST_STATIC_ASSERT(D==1);
		dim[0]= d1;
	}
	
	PeriodicCartesian(size_t d1, size_t d2)
	{ 
		BOOST_STATIC_ASSERT(D==2);
		dim[0] = d1; dim[1] = d2;
	}
	
	PeriodicCartesian(size_t d1, size_t d2, size_t d3) 
	{
		BOOST_STATIC_ASSERT(D==3);
		dim[0] = d1; dim[1] = d2; dim[2] = d3;		 
	}

	size_t getDim(size_t i) const { return dim[i]; }

	friend std::pair<adjacency_iterator<D>, adjacency_iterator<D> > adjacent_vertices(const vertex_descriptor &v, const PeriodicCartesian<D> &g)
	{
		return std::make_pair(adjacency_iterator<D>(&g, v, 0), adjacency_iterator<D>(&g, v, 0));
	}

private:
	size_t dim[D];
};

const size_t offsets[27][3] =
{
	{ 1, 1, 1}, { 0, 1, 1}, { -1, 1, 1},
	{ 1, 0, 1}, { 0, 0, 1}, { -1, 0, 1},
	{ 1,-1, 1}, { 0,-1, 1}, { -1,-1, 1},
	
	{ 1, 1, 0}, { 0, 1, 0}, { -1, 1, 0},
	{ 1, 0, 0}, { 0, 0, 0}, { -1, 0, 0},
	{ 1,-1, 0}, { 0,-1, 0}, { -1,-1, 0},
	
	{ 1, 1,-1}, { 0, 1,-1}, { -1, 1,-1},
	{ 1, 0,-1}, { 0, 0,-1}, { -1, 0,-1},
	{ 1,-1,-1}, { 0,-1,-1}, { -1,-1,-1}
};

template <unsigned D>
class adjacency_iterator {
public:
	typedef PeriodicCartesian<D> 					graph_t;
	typedef typename graph_t::vertex_descriptor 	vertex_descriptor;
	
	adjacency_iterator(graph_t *g, vertex_descriptor c, size_t p)
	: graph(g), current(c), pos(p) { }
	
	vertex_descriptor operator*()
	{
		vertex_descriptor result;
		for(size_t i = 0;i<D;++i)
			result[i] = (current[i]+offsets[pos][i]+graph->getDim(i))%graph->getDim(i);
		return result; 
	}
	
	adjacency_iterator& operator++()
	{ ++pos; if((D==1 && pos == 1) || (D==2 && pos == 4) || (D==3 && pos == 13)) ++pos; return *this; }
	adjacency_iterator operator++(int)
	{ adjacency_iterator tmp = *this; ++pos; if((D==1 && pos == 1) || (D==2 && pos == 4) || (D==3 && pos == 13)) ++pos; return tmp; }
private:
	graph_t *graph;
	vertex_descriptor current;
	size_t pos;
};

#endif
