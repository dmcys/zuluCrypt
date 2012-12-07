/*
 * 
 *  Copyright (c) 2011
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

static inline int zuluExit( int x,string_t p )
{
	StringDelete( &p ) ;
	return x ;
}

int zuluCryptOpenVolume( const char * dev,const char * map,const char * m_point,uid_t id,const char * mode,const char * pass,size_t pass_size ) 
{
	int h ;
	string_t p = StringVoid ;
	const char * mapper ;
	
	/*
	 * zuluCryptPathIsNotValid() is defined in is_path_valid.c
	 */
	if( zuluCryptPathIsNotValid( dev ) ) 
		return 3 ;
	
	p = String( crypt_get_dir() ) ;
	
	mapper = StringMultipleAppend( p,"/",map,END ) ;

	/*
	 * zuluCryptPathIsValid() is defined in is_path_valid.c
	 */
	if( zuluCryptPathIsValid( mapper ) )
		return zuluExit( 2,p ) ;

	/*
	 * zuluCryptOpenLuks()   is defined in open_luks.c
	 * zuluCryptOpenTcrypt() is defined in open_tcrypt.c
	 * zuluCryptOpenPlain()  is defined in open_plain.c
	 * zuluCryptGetVolumeType() is defined in volume_type.c
	 */
	switch( zuluCryptGetVolumeType( dev,pass,pass_size ) ){
		case 1 : h = zuluCryptOpenLuks(   dev,map,mode,pass,pass_size ) ; break ;
		case 2 : h = zuluCryptOpenTcrypt( dev,map,mode,pass,pass_size ) ; break ;
		default: h = zuluCryptOpenPlain(  dev,map,mode,pass,pass_size ) ; break ;
	}
	
	switch( h ){
		case 1 : return zuluExit( 4,p ) ;
		case 2 : return zuluExit( 8,p ) ; 
		case 3 : return zuluExit( 3,p ) ;
	}
	
	if( m_point != NULL ){
		/*
		 * zuluCryptMountVolume() is defined in mount_volume.c
		 */
		h = zuluCryptMountVolume( mapper,m_point,mode,id ) ;
	
		if( h != 0 ){
			/*
			 * zuluCryptCloseMapper() is defined in close_mapper.c
			 */
			if( zuluCryptCloseMapper( map ) != 0 ){
				h = 15 ;
			}
		}
	}
	
	return zuluExit( h,p ) ;
}

