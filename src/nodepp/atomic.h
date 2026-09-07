/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_ATOMIC
#define NODEPP_ATOMIC

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined( NODEPP_THREAD_SUPPORTED )
    #error "This OS Does not support atomic.h"
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#include "arduino/atomic.h"

/*────────────────────────────────────────────────────────────────────────────*/

#endif