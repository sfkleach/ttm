#ifndef SIMPLE_NETWORK_HPP
#define SIMPLE_NETWORK_HPP

#include "network.hpp"
#include "simplenode.hpp"

class SimpleNetwork : public Network< SimpleNode > {
private:
	SimpleNode limit;

public:
	SimpleNetwork( SimpleNode limit ) :
		limit( limit )
	{}

public:

	virtual void fetchNeighbors( SimpleNode node, std::vector< Link< SimpleNode > > & neighbors );

};

#endif
