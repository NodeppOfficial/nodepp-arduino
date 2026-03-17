/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_FS
#define NODEPP_FS

/*────────────────────────────────────────────────────────────────────────────*/

#if   _KERNEL_ == NODEPP_KERNEL_ARDUINO
    #include "path.h"
    #include "stream.h"
    #include "promise.h"
    #include "arduino/fs.h"
#else
    #error "This OS Does not support fs.h"
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#endif