/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_MEMORY
#define NODEPP_MEMORY

/*────────────────────────────────────────────────────────────────────────────*/

#define MEMORY(  ... ) /*-----*/ memory::get<TYPE>( __VA_ARGS__ )
#define MEMSTR( DATA ) string_t( memory::get<char>( F( DATA ) ) )

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace memory {

    template< class V >
    ptr_t<V> get( const __FlashStringHelper* data, ulong size ){
    ptr_t<V> out( size ); queue_t<char> list;
        
        ulong x = size * sizeof( V );

        PGM_P raw = type::cast<PGM_P>( data ); do {
            list.push( pgm_read_byte(raw++) );
        } while( x --> 0 );

        memcpy( &out, &list.data, sizeof(V)*size );
        return out;
    }

    template< class V >
    ptr_t<V> get( const __FlashStringHelper* data ){

        PGM_P raw = reinterpret_cast<PGM_P>( data ); 
        queue_t<char> list; do {
            list.push( pgm_read_byte(raw++) );
        } while( list.last()->data != '\0' );

        return list.data();
    }

    /*─······································································─*/

    template< class V, class T, ulong N >
    V get( const T& data ){ V out={0}; 
        PGM_P start_address = reinterpret_cast<PGM_P>(data) + N * sizeof(V);
        memcpy_P( &out, start_address, sizeof(V) ); return out; 
    }

    /*─······································································─*/

    template< class V, class T >
    ptr_t<V> get( const T& data, ulong size ){ 
    ptr_t<V> out( size ); memcpy_P( &out, data, sizeof(V)*size ); 
        return out; 
    }

    template< class V, class T >
    ptr_t<V> get( const T& data ){ 
        char* out = new char[ strlen_P( data ) ];
        ulong len = strlen_P( data ) * sizeof(V);
        memcpy_P( out, data, len ); 
        return out;
    }

} }

/*────────────────────────────────────────────────────────────────────────────*/

#endif