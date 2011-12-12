#ifndef CARTESIAN_PROPERTIES
#define CARTESIAN_PROPERTIES

#include <vector>

#include "implicit_cartesian.hpp"

template <class T, unsigned D>
class CartesianProperties {
public:
	typedef typename PeriodicCartesian<D>::vertex_descriptor index;

	CartesianProperties(PeriodicCartesian<D> &g) : graph(g)
	{
		size_t product = 1;
		for(unsigned j = 0;j<D;++j)
		{
			product *= graph.getDim(j);
		}
		data.resize(product);
	}
	
	T& operator()(index i)
	{
		size_t idx = 0;
		size_t product = 1;
		for(unsigned j = 0;j<D;++j)
		{
			idx += i[j]*product;
			product *= graph.getDim(j);
		}
		return data[idx];
	}
	
	const T& operator()(index i) const
	{
		size_t idx = 0;
		size_t product = 1;
		for(unsigned j = 0;j<D;++j)
		{
			idx += i[j]*product;
			product *= graph.getDim(j);
		}
		return data[idx];
	}

private:
	PeriodicCartesian<D> &graph;
	std::vector<T> data;
};

#endif
