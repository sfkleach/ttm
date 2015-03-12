#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include "link.hpp"
#include "maybe.hpp"

template < typename Node >
class Network {
public:

	//	 Fills the neighbors vector with links to neighbors of node.
	virtual void fetchNeighbors( Node node, std::vector< Link< Node > > & neighbors ) = 0;

	virtual Maybe< Link< Node > > fetchLink( Node source, Node destination ) {
		std::vector< Link< Node > > neighbors;
		this->fetchNeighbors( source, neighbors );
		for ( Link< Node > node : neighbors ) {
			if ( node.hasDestination( destination ) ) {
				return Maybe< Link< Node > >( node );
			}
		}
		return Maybe< Link< Node > >();
	}

};

#endif
