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

    inline void delay( ulong time ){ ::delay( time ); }

    inline ulong now(){ return millis(); }

    inline void yield(){ delay(TIMEOUT); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
