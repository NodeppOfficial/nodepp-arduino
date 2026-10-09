/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_ARDUINO_OS
#define NODEPP_ARDUINO_OS

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace os {

    inline uchar_64 rand() {
    thread_local static uchar_64 seed = (uchar_64)&seed;
        seed ^= seed << 0x11;
        seed ^= seed >> 0x07;
        seed ^= seed << 0x0b; return seed;
    }
    
    inline string_t tmp(){ return "/"; }

    inline string_t cwd(){ return "/"; }

    inline uint    cpus(){ return   1; }

    inline void   reset(){ ARDUINO_RESET(); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif