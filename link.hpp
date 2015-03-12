#ifndef LINK_HPP
#define LINK_HPP

template < typename Node >
class Link {
public:
	Node	source;
	Node 	destination;
	double	delta;

	Link( Node src, double time, Node dst ) :
		source( src ),
		destination( dst ),
		delta( time )
	{}

	Link() :
		source( Node() ),
		destination( Node() ),
		delta( 0.0 )
	{}

	bool hasDestination( const Node & d ) const {
		return d == this->destination;
	}

	//bool operator <( const Link & rhs ) const;
	bool operator <( const Link< Node > & rhs) const {
		return this->delta < rhs.delta;
	}
};


#endif
