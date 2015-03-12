#ifndef FIND_ROUTE_HPP
#define FIND_ROUTE_HPP

#include <map>
#include <queue>
#include <deque>
#include <memory>
#include <vector>
#include <math.h> 


#include "maybe.hpp"
#include "network.hpp"


template < typename Node >
class FindRoute {

	/** Tip is a member of the priority queue, representing the tip of
	 * 	the search from the origin - and the time taken to get there.
	 *	The best routes to nodes are encoded in the known_chain map.
	 */
	struct Tip {
		Node head;
		double travel_time;
		Tip( Node head, double time ) : head( head ), travel_time( time ) {}
	};

	/** TipLessThan is the comparison operator used to sort the 
	 *	the priority queue.
	 */	
	class TipLessThan {
	public:
		bool operator()( const Tip & lhs, const Tip & rhs ) const {
			return lhs.travel_time > rhs.travel_time;
		}
	};

	struct TipLink {
		Node head;
		double time;
		Maybe< Node > previous;
		int count;
		TipLink( Node head, double time, Maybe< Node > prev, int count ) : 
			head( head ), 
			time( time ),
			previous( prev ), 
			count( count )  
		{}
		TipLink() : head( Node() ), time( 0.0 ), previous( Maybe< Node >() ), count( 0 ) {}
	};

private:
	Network< Node > & network;
	std::map< Node, TipLink > known_chain;
	std::priority_queue< Tip, std::vector< Tip >, TipLessThan > fringe;

private:
	//	Values just for debugging. If DEBUG is true then you can 
	//	see the progress of the algorithm. If DEBUG is false then
	//	the progress is silent.
	static const bool DEBUG = false;
	static const int modulus = 1e6;

public:
	FindRoute( Network< Node > & network ) : 
		network( network ) 
	{}

	void findRoute( Node start, Maybe< Node > finish = Maybe< Node >() ) {
		fringe.emplace( start, 0.0 );
		known_chain[ start ] = TipLink( start, 0.0, Maybe< Node >(), 1 );

		int count = 0;
		for ( ; not fringe.empty(); count++ ) {
			Tip top = fringe.top();
			fringe.pop();

			this->known_chain[ top.head ].count -= 1;
			if ( this->known_chain[ top.head ].time < top.travel_time ) {
				//	Discard.
				continue;
			}

			if ( DEBUG && count % modulus == 0 ){
				std::cout << "Known chain length : " << known_chain.size() << std::endl;
				std::cout << "Fringe length      : " << fringe.size() << std::endl;
			}
			
			//	At this point the route for the top.head is optimal.
			if ( finish.hasValue() and top.head == finish.fastValue() ) break;

			std::vector< Link< Node > > neighbors;
			network.fetchNeighbors( top.head, neighbors );

			int added = 0;

			for ( Link< Node > link : neighbors ) {
				const double t = top.travel_time + link.delta;

				auto known_it = this->known_chain.find( link.destination );
				if ( known_it != this->known_chain.end() ) {

					TipLink & known_link = known_it->second;
					if ( t < known_link.time ) {

						if ( DEBUG && count % modulus == 0 ) {
							std::cout << "    From       : " << top.head << std::endl;
							std::cout << "    To         : " << link.destination << std::endl;
							std::cout << "    Improvement: " << t << "<" << known_link.time << std::endl;
							std::cout << "    Delta      : " << known_link.time - t << std::endl;
						}

						known_link.time = t;
						known_link.previous = top.head;
						known_link.count += 1;
						fringe.emplace( link.destination, t );
						added += 1;	
					}
				} else {
					known_chain[ link.destination ] = TipLink( link.destination, t, top.head, 1 );
					fringe.emplace( link.destination, t );
					added += 1;				
				}
			}

			if ( DEBUG && count % modulus == 0 ) {
				std::cout << "    Added : " << added << std::endl;
			}		
		}

		if ( DEBUG ) {
			std::cout << "Num popped to calculate TTM = " << count << std::endl;
		}
	}


	void outwardsRoute( Maybe< Node > node, std::deque< Link< Node > > & route ) {
		while ( node.hasValue() ) {
			auto p = known_chain.find( node.fastValue() );
			if ( p != known_chain.end() ) {
				TipLink & tip_link = p->second;
				if ( tip_link.previous.hasntValue() ) break;
				route.push_back( 
					Link< Node >( 
						tip_link.previous.fastValue(), 
						tip_link.time, 
						tip_link.head
					) 
				);
				node = tip_link.previous;
			} else {
				throw Mishap( "Broken chain" );
			}
		}
		if ( DEBUG ) {
			std::cout << "Deque# = " << route.size() << std::endl;
		}
	}

	Maybe< Link< Node > > linkToPrevious( Node here ) {
		auto p = known_chain.find( here );
		if ( p != known_chain.end() ) {
			TipLink & tip_link = p->second;
			if ( tip_link.previous.hasValue() ) {
				return this->network.fetchLink( tip_link.previous.fastValue(), here );
			} else {
				return Maybe< Link< Node > >();
			}
		} else {
			return Maybe< Link< Node > >();
		}
	}

	double predictedTimeToOrigin( Node here ) {
		auto p = known_chain.find( here );
		if ( p != known_chain.end() ) {
			TipLink & tip_link = p->second;
			return tip_link.time;
		} else {
			return INFINITY;
		}
	}

};

#endif
