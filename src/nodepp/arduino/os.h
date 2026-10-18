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
    
    /*─······································································─*/

    inline bool is_little_endian(){
        uchar_16 value = 0x01;
        return ( (char*)&value )[0] == 0x01;
    }

    inline bool is_big_endian(){
        uchar_16 value = 0x01;
        return ( (char*)&value )[0] == 0x00;
    }
    
    /*─······································································─*/
    
    inline string_t tmp(){ return "/"; }

    inline string_t cwd(){ return "/"; }

    inline uint    cpus(){ return   1; }

    inline void   reset(){ NODEPP_RESET(); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif