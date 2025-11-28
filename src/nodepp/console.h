/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_CONSOLE
#define NODEPP_CONSOLE

/*────────────────────────────────────────────────────────────────────────────*/

#include "conio.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace console {

    template< class... T >
    int err( const T&... args ){ return conio::err(args...,"\n"); }

    template< class... T >
    int log( const T&... args ){ return conio::log(args...,"\n"); }

    template< class... T >
    int scan( const T&... args ){ return conio::scan( args... ); }

    template< class... T >
    int pout( const T&... args ){ return conio::log( args... ); }
    
    /*─······································································─*/

    inline void enable( uint port ){ Serial.begin( port ); }

    inline void wait(){ char x; conio::scan("%c",&x); }
    
    /*─······································································─*/

    template< class... T >
    int warning( const T&... args ){ 
        conio::log( "WARNING: ");
        return log( args... ); 
    }

    template< class... T >
    int success( const T&... args ){ 
        conio::log( "SUCCESS: ");
        return log( args... );  
    }

    template< class... T >
    int error( const T&... args ){ 
        conio::log( "ERROR: "); 
        return log( args... ); 
    }

    template< class... T >
    int done( const T&... args ){ 
        conio::log( "DONE: "); 
        return log( args... ); 
    }

    template< class... T >
    int info( const T&... args ){ 
        conio::log( "INFO: "); 
        return log( args... ); 
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif