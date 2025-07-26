/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_NODEPP
#define NODEPP_NODEPP

/*────────────────────────────────────────────────────────────────────────────*/

#include "import.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process { loop_t loop;

    /*─······································································─*/

    ulong size(){ return _TASK_ + loop.size(); }

    void clear(){ _TASK_=0; loop.clear(); }

    bool empty(){ return size() <= 0; }

    /*─······································································─*/

    void exit( int err=0 ){ _EXIT_=true; clear(); ::exit(err); }

    bool should_close(){ return _EXIT_ || empty(); }

    /*─······································································─*/

    int next(){ static ulong count = 0;
        if(( ++count % 64 )==0){ yield(); }
    coStart
        coWait( loop.next()==1 );
    coStop }

    void clear( void* address ){
         if( address == nullptr ){ return; }
         memset( address, 0, sizeof(bool) );
    }

    /*─······································································─*/

    template< class... T >
    void* add( const T&... args ){ return loop.add( args... ); }

    template< class T, class... V >
    void await( T cb, const V&... args ){ ++_TASK_;
    while( !should_close() && ([&](){

        switch( cb( args... ) ){
            case  1: next(); return 1; break;
            case  0: /*---*/ return 0; break;
            default: /*-------------*/ break;
        }

    return -1; })()>=0 ){} --_TASK_; }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process { array_t<string_t> args;

    template< class... T >
    void error( const T&... msg ){ ARDUINO_ERROR( msg... ); }

    void reset(){ void(*callback) (void)=0; callback(); }

    /*─······································································─*/

    void start(){ process::yield(); }

    /*─······································································─*/

    void stop(){ 
        while(!process::should_close() )
             { process::next(); }
        process::exit(1);
    }

    /*─······································································─*/

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
