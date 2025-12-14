/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_CONIO
#define NODEPP_CONIO

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace conio {

    inline int perr( const string_t& args ){ return Serial.write( args.get(), args.size() ); }
    
    inline int pout( const string_t& args ){ return Serial.write( args.get(), args.size() ); }

    template< class V, class... T >
    int scan( const V& argc, const T&... args ){ while(!Serial.available() ){/**/}
        return string::parse( Serial.readString().c_str(), (char*) argc, args... );
    }

    /*─······································································─*/

    template< class... T >
    int log( const T&... args ){
        auto  data = string::join( " ", args... );
        pout( data ); return data.size();
    }

    template< class... T >
    int err( const T&... args ){
        auto  data = string::join( " ", args... );
        perr( data ); return data.size();
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif