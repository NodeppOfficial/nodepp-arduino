/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_SLEEP
#define NODEPP_SLEEP

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    inline ulong seconds(){ return ::millis() / 1000; }

    inline ulong  micros(){ return ::micros(); }

    inline ulong  millis(){ return ::millis(); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    inline ulong& get_timeout( bool reset=false ) {
    static ulong stamp=0; 
        if( reset ) { stamp=(ulong)-1; }
    return stamp; }

    inline void clear_timeout() { get_timeout(true); }

    inline ulong set_timeout( int time=0 ) { 
        if( time < 0 ){ /*--------------*/ return 1; }
        auto stamp=&get_timeout(); ulong out=*stamp;
        if( *stamp>(ulong)time ){ *stamp=(ulong)time; }
    return out; }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    inline void delay( ulong time ){ ::delay( time ); }

    inline ulong now(){ return millis(); }

    inline void yield(){ delay(TIMEOUT); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
