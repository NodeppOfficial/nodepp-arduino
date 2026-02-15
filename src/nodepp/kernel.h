/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_POSIX_KERNEL
#define NODEPP_POSIX_KERNEL
    #define NODEPP_POLL_NPOLL
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#ifdef NODEPP_POLL_NPOLL

namespace nodepp { class kernel_t {
private:

    enum FLAG { 
         KV_STATE_UNKNONW = 0b00000000, 
         KV_STATE_WRITE   = 0b00000001,
         KV_STATE_READ    = 0b00000010,
         KV_STATE_EDGE    = 0b10000000,
         KV_STATE_USED    = 0b00000100,
         KV_STATE_AWAIT   = 0b00001100,
         KV_STATE_CLOSED  = 0b00001000
    };

    struct kevent_t { public:
        function_t<int> callback;
        ulong timeout; int fd, flag; 
    };

    /*─······································································─*/

    int get_delay_ms() const noexcept {
        ulong tasks= obj->ev_queue.size() + obj->probe.get();
        ulong time = TIMEOUT==0 || tasks==0 ? 0 : TIMEOUT;
    return ( tasks==0 ) ? 10 : time; }

protected:

    struct NODE { loop_t ev_queue; }; ptr_t<NODE> obj;

public:

    kernel_t() noexcept : obj( new NODE() ) {}

public:

    void off( ptr_t<task_t> address ) const noexcept { clear( address ); }

    void clear( ptr_t<task_t> address ) const noexcept {
         if( address.null() ) /*--------------*/ { return; }
         if( address->flag & TASK_STATE::CLOSED ){ return; }
             address->flag = TASK_STATE::CLOSED;
    }

    /*─······································································─*/

    ulong size() const noexcept { return obj->ev_queue.size() + obj.count()-1; }

    void clear() const noexcept { /*--*/ obj->ev_queue.clear(); }

    bool empty() const noexcept { return size()==0; }

    int   emit() const noexcept { return -1; }

    /*─······································································─*/

    template< class T, class U, class... W >
    ptr_t<task_t> poll_add ( T /*unused*/, int /*unused*/, U cb, ulong timeout=0, const W&... args ) noexcept {
        auto time = type::bind( timeout>0 ? timeout + process::now() : timeout );
        auto clb  = type::bind( cb ); return obj->ev_queue.add( [=](){ 
        if( *time > 0 && *time < process::now() ){ return -1; }
            return (*clb)( args... )>=0 ? 1 : -1; 
        } );
    }

    template< class T, class... V >
    ptr_t<task_t> loop_add ( T cb, const V&... args ) noexcept {
        return obj->ev_queue.add( cb, args... );
    }

    /*─······································································─*/

    template< class T, class... V > 
    int await( T cb, const V&... args ) const { int c=0;

        if ((c =cb(args...))>=0 ){ next(); return 1; } 
    
    return -1; }

    /*─······································································─*/

    inline int next() const {

        while( obj->ev_queue.next() >= 0 ){ return 1; } 
        process::set_timeout(obj->ev_queue.get_delay());
        process::delay( get_delay_ms() );
        process::clear_timeout();

    return 1; }

};}

#endif

/*────────────────────────────────────────────────────────────────────────────*/