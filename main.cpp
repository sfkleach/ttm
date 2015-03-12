#include <iostream>
#include <deque>

#include "network.hpp"
#include "findroute.hpp"
#include "simplenetwork.hpp"

using namespace std;

int main( int argc, char **argv ) {
    SimpleNetwork network( 1000000 );
    FindRoute< SimpleNode > finder( network );

    finder.findRoute( 0, Maybe< SimpleNode >() );

    SimpleNode target = 999999;

    deque< Link< SimpleNode > > route;
    finder.outwardsRoute( target, route );

    cout << "--- Route ---" << endl;    
    for ( Link< SimpleNode > link : route ) {
        cout << link.source << "-> " << link.destination << endl;
    }

    Maybe< Link< SimpleNode > > m = finder.linkToPrevious( target );
    cout << "First move is to: " << m.value().source << endl;

    cout << "Predicted time to origin: " << finder.predictedTimeToOrigin( target ) << endl;
}
