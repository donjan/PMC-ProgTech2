#ifndef IMPLICIT_CARTESIAN_H
#define IMPLICIT_CARTESIAN_H

#include <utility>
#include <algorithm>
#include <ostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/static_assert.hpp>


template <unsigned D>
struct vertex {
	vertex() {}
	vertex(int d1)
	{ 
		BOOST_STATIC_ASSERT(D==1);
		pos[0]= d1;
	}
	
	vertex(int d1, int d2)
	{ 
		BOOST_STATIC_ASSERT(D==2);
		pos[0] = d1; pos[1] = d2;
	}
	
	vertex(int d1, int d2, int d3) 
	{
		BOOST_STATIC_ASSERT(D==3);
		pos[0] = d1; pos[1] = d2; pos[2] = d3;		 
	}
	int pos[D];
	int& operator[](int i) { return pos[i]; }
	int operator[](int i) const { return pos[i]; }
};

template <unsigned D>
std::ostream& operator<<(std::ostream &out, const vertex<D> &v)
{
	out << '(' << v[0];
	for(unsigned i = 1;i<D;++i)
		out << ',' << v[i];
	out << ')';
	
	return out;
}

template <unsigned D>
bool operator==(const vertex<D> &a, const vertex<D> &b)
{
	for(unsigned i = 0;i<D;++i)
		if(a[i]!=b[i])
			return false;
	return true;
}

template <unsigned D>
bool operator!=(const vertex<D> &a, const vertex<D> &b)
{
	return !(a==b);
}

template <unsigned D>
class adjacency_iterator_t;

template <unsigned D>
class PeriodicCartesian {
public:
	typedef vertex<D> 							vertex_descriptor;
	typedef std::pair< vertex<D>, vertex<D> > 	edge_descriptor;
	typedef boost::undirected_tag				directed_category;
	typedef boost::disallow_parallel_edge_tag	edge_parallel_category;
	typedef boost::adjacency_graph_tag			traversal_category;
	typedef adjacency_iterator_t<D>				adjacency_iterator;
	
	PeriodicCartesian() {}
	
	PeriodicCartesian(int d1)
	{ 
		BOOST_STATIC_ASSERT(D==1);
		dim[0]= d1;
	}
	
	PeriodicCartesian(int d1, int d2)
	{ 
		BOOST_STATIC_ASSERT(D==2);
		dim[0] = d1; dim[1] = d2;
	}
	
	PeriodicCartesian(int d1, int d2, int d3) 
	{
		BOOST_STATIC_ASSERT(D==3);
		dim[0] = d1; dim[1] = d2; dim[2] = d3;		 
	}

	int getDim(int i) const { return dim[i]; }

	friend std::pair<adjacency_iterator, adjacency_iterator > adjacent_vertices(const vertex_descriptor &v, const PeriodicCartesian<D> &g)
	{
		int i = 3;
		for(int j = 1;j<D;++j) i*=3;
		return std::make_pair(adjacency_iterator(&g, v, 0), adjacency_iterator(&g, v, i));
	}

private:
	int dim[D];
};

const int offsets[27][3] =
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
class adjacency_iterator_t {
public:
	typedef PeriodicCartesian<D> 					graph_t;
	typedef typename graph_t::vertex_descriptor 	vertex_descriptor;
	typedef std::forward_iterator_tag 				iterator_category;
    typedef vertex_descriptor        				value_type;
    typedef int   									difference_type;
    typedef vertex_descriptor*           			pointer;
    typedef vertex_descriptor&         				reference;
	
	
	adjacency_iterator_t() {}
	adjacency_iterator_t(const graph_t *g, vertex_descriptor c, int p)
	: graph(g), current(c), pos(p) { }
	
	vertex_descriptor operator*()
	{
		vertex_descriptor result;
		for(unsigned i = 0;i<D;++i)
			result[i] = (current[i]+offsets[pos][i]+graph->getDim(i))%graph->getDim(i);
		return result; 
	}
	
	adjacency_iterator_t& operator++()
	{ ++pos; if((D==1 && pos == 1) || (D==2 && pos == 4) || (D==3 && pos == 13)) ++pos; return *this; }
	adjacency_iterator_t operator++(int)
	{ adjacency_iterator_t tmp = *this; ++pos; if((D==1 && pos == 1) || (D==2 && pos == 4) || (D==3 && pos == 13)) ++pos; return tmp; }
	
	friend bool operator==(adjacency_iterator_t<D> &a, adjacency_iterator_t<D> &b)
	{ return a.graph == b.graph && a.current == b.current && a.pos == b.pos; }
	friend bool operator!=(adjacency_iterator_t<D> &a, adjacency_iterator_t<D> &b)
	{ return !(a==b); }
private:
	const graph_t *graph;
	vertex_descriptor current;
	int pos;
};

namespace boost {
    template<unsigned D>
    struct graph_traits< PeriodicCartesian<D> > {
        typedef typename PeriodicCartesian<D>::vertex_descriptor      vertex_descriptor;
        typedef typename PeriodicCartesian<D>::edge_descriptor        edge_descriptor;
        typedef typename PeriodicCartesian<D>::adjacency_iterator     adjacency_iterator;

        typedef typename PeriodicCartesian<D>::directed_category      directed_category;
        typedef typename PeriodicCartesian<D>::edge_parallel_category edge_parallel_category;
        typedef typename PeriodicCartesian<D>::traversal_category     traversal_category;
    };
}

#endif
