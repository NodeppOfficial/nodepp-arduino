/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_MAP
#define NODEPP_MAP

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { template<class U, class V> class map_t {
protected:

    using T = type::pair< U, V >;

    struct NODE {
        queue_t<T> queue;
    };  ptr_t<NODE> obj;

protected:

    void append( const T& pair ) const noexcept {
        auto x = obj->queue.first();

        while( x != nullptr ){
          if ( x->data.first == pair.first )
             { x->data.second = pair.second; return; }
        else { x = x->next; } }

        obj->queue.push( pair );
    }

public:

    template< ulong N >
    map_t( const T (&args) [N] ) noexcept : obj(new NODE()) {
      for( auto &x: args ){ append(x); }
    }

    map_t() noexcept : obj(new NODE()) {}

    virtual ~map_t() noexcept {} 

    /*─······································································─*/

    V& operator[]( const U& id ) const noexcept {
        auto x = obj->queue.first();

        while( !id.empty() && x != nullptr ){
           if( x->data.first == id )
             { return x->data.second; }
         else{ x = x->next; }
        }   append({ id, V() });

        return obj->queue.last()->data.second;
    }

    /*─······································································─*/

    array_t<U> keys() const noexcept { array_t<U> result;
        auto x = obj->queue.first(); while( x!=nullptr ){
            result.push( x->data.first ); x=x->next;
        }   return result;
    }

    /*─······································································─*/

    bool has( const U& id ) const noexcept {
        auto x = obj->queue.first();

        while( x != nullptr ){
          if ( x->data.first == id )
             { return true; }
        else { x = x->next; } }

        return false;
    }

    /*─······································································─*/

    void map( function_t<void,T&> callback ) const noexcept {
         obj->queue.map( callback );
    }

    /*─······································································─*/

    bool     empty() const noexcept { return obj->queue.empty(); }
    ulong     size() const noexcept { return obj->queue.size(); }
    ptr_t<T>  data() const noexcept { return obj->queue.data(); }
    ptr_t<T>   get() const noexcept { return obj->queue.data(); }
    queue_t<T> raw() const noexcept { return obj->queue; }

    /*─······································································─*/

    void erase() const noexcept { obj->queue.erase(); }

    void erase( const U& id ) const noexcept {
        obj->queue.erase( obj->queue.index_of(
        [&]( T arg ){ return arg.first==id; }));
    }

    void clear() const noexcept { erase(); }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif