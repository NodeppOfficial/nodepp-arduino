/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_LOOP
#define NODEPP_LOOP

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class loop_t {
private:

    using NODE_CLB = function_t<int>;
    using NODE_TASK= type::pair<ulong,void*>;
    using NODE_PAIR= type::pair<NODE_CLB,ref_t<task_t>>;

protected:

    struct NODE {
        queue_t<NODE_PAIR> queue;
    };  ptr_t<NODE> obj;

    /*─······································································─*/

    inline int queue_queue_next() const {
    
        if( obj->queue.empty() ) /*-*/ { return -1; } do {
        if( obj->queue.get()==nullptr ){ return -1; }

        auto x = obj->queue.get(); /*-------------------------*/
        auto o = obj->queue.get() == obj->queue.last() ? -1 : 1;
        
        if( x->data.second->flag & TASK_STATE::USED   ){ 
            obj->queue.next(); 
        return 1; }
        
        if( x->data.second->flag & TASK_STATE::CLOSED ){ 
            obj->queue.erase(x);
        return 1; } 

        x->data.second->flag |= TASK_STATE::USED;

        int c=0; while( ([&](){
            
            do{ c=x->data.first(); switch(c) {
                case  1 :  goto GOT1;   break;
                case -1 :  goto GOT2;   break;
                case  0 :  goto GOT4;   break;
            } } while(0);

            GOT1:;

                x->data.second->flag &=~ TASK_STATE::USED; 
                obj->queue.next(); return -1;

            GOT2:;

                x->data.second->flag = TASK_STATE::CLOSED;
                /*---------------*/ return -1;

            GOT4:;

        return -1; })() >= 0 ){ /* unused */ }
        return  o; } while(0); return -1;

    }

public: loop_t() noexcept : obj( new NODE() ) {}

    /*─······································································─*/

    void off( ptr_t<task_t> address ) const noexcept { clear( address ); }

    void clear( ptr_t<task_t> address ) const noexcept {
        if( address.null() ) /*-*/ { return; }
        if( address->sign != &obj ){ return; }
        if( address->flag & TASK_STATE::CLOSED ){ return; }
            address->flag = TASK_STATE::CLOSED;
    }

    /*─······································································─*/

    ulong    size() const noexcept { return obj->queue.size  (); }

    bool    empty() const noexcept { return obj->queue.empty (); }

    int get_delay() const noexcept { return 0; }

    /*─······································································─*/

    inline int next() const /*----*/ { return queue_queue_next(); }

    void      clear() const noexcept {  obj->queue.clear(); }

    /*─······································································─*/

    template< class T, class... V >
    ptr_t<task_t> add( T cb, const V&... args ) const noexcept {
    ptr_t<task_t> tsk( 0UL, task_t() ); auto clb = type::bind( cb );

        obj->queue .push({[=](){ return (*clb)( args... );}, tsk });

        tsk->addr = obj->queue.last();
        tsk->flag = TASK_STATE::OPEN ;
        tsk->sign = &obj;

    return tsk; }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/