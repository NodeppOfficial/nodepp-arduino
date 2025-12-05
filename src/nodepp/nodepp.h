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

namespace nodepp { namespace process { loop_t _loop_;

    /*─······································································─*/

    inline ulong size(){ return _TASK_ + _loop_.size(); }

    inline void clear(){ _TASK_=0; _loop_.clear(); }

    inline bool empty(){ return size() <= 0; }

    /*─······································································─*/

    inline bool should_close(){ return _EXIT_ || empty(); }

    inline void clear( void* address ){
         if( address == nullptr ){ return; }
         memset( address, 0, sizeof(bool) );
    }

    inline void exit( int err=0 ){ 
        if( should_close() ){ goto DONE; }
        _EXIT_=true; /**/ clear(); 
        DONE:; ARDUINO_RESET();
        ::exit(err);
    }

    /*─······································································─*/

    inline int next(){ static uchar count=0; if( count%64==0 ){ yield(); }
    count++ ; coStart
        if( !_loop_.empty() ) { _loop_.next(); coNext; }
    coStop }
    
    /*─······································································─*/

    template< class... T >
    void* loop( const T&... args ){ return _loop_.add( args... ); }

    template< class... T >
    void* add ( const T&... args ){ return _loop_.add( args... ); }

    /*─······································································─*/

    template< class T, class... V >
    void await( T cb, const V&... args ){ ++_TASK_;
         while( cb( args... )>=0 && !should_close() )
              { process::next(); } 
    --_TASK_; }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process { array_t<string_t> args;

    template< class... T >
    void error( const T&... msg ){ ARDUINO_ERROR( msg... ); }

    inline void start(){ process::yield(); }

    inline void reset(){ ARDUINO_RESET(); }

    /*─······································································─*/

    inline void stop(){ 
        while(!process::should_close() )
             { process::next(); }
        process::exit(0);
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
