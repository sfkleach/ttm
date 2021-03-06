/******************************************************************************\
    Copyright (c) 2010 Stephen Leach. AppGinger is distributed under the terms 
    of the GNU General Public License. This file is part of AppGinger.

    AppGinger is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AppGinger is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AppGinger.  If not, see <http://www.gnu.org/licenses/>.
\******************************************************************************/

#ifndef MAYBE_HPP
#define MAYBE_HPP

#include "mishap.hpp"

template< typename T > 
class Maybe {
private:
    T 		a_value;
    bool 	is_valid;

public:
    Maybe( const T& x ) : a_value( x ), is_valid( true ) {}
    Maybe() : is_valid( false ) {}

    bool hasValue() const { return this->is_valid; }
    
    bool hasntValue() const { return not this->is_valid; }

    T& fastValue() { return this->a_value; }

    T& value() {
        if ( not this->is_valid ) {
            throw Mishap( "Trying to take value from an invalid Maybe" );
        }
        return this->a_value;
    }

};

#endif
