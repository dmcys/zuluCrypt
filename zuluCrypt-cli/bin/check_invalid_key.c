/*
 * 
 *  Copyright (c) 2012
 *  name : mhogo mchungu 
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "includes.h"

void check_invalid_key( const char * device )
{
	char * d = empty_slots( device ) ;
	char * c ;
	int e = 0  ;
	
	if( d == NULL ){
		/*
		 * we got here because the volume is either not luks based or the path is invalid
		 */
		return ;
	}
	
	c = d - 1 ;
	
	while( *++c ){
		if( *c == '2' )
			printf("WARNING: key slot number: %d is corrupted\n",e ) ;
		e++ ;
	}	
	free( d ) ;
} 
