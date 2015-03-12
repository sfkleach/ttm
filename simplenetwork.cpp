#include "simplenetwork.hpp"


void SimpleNetwork::fetchNeighbors( SimpleNode node, std::vector< Link< SimpleNode > > & neighbors ) {
	if ( node < this->limit ) {
		neighbors.push_back( Link< SimpleNode >( node, 1.0, node + 1 ) );
		neighbors.push_back( Link< SimpleNode >( node, 1.0, node * 2 ) );
	}
}

