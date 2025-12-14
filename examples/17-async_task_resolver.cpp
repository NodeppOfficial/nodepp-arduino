#include <nodepp.h>
#include <nodepp/promise.h>

using namespace nodepp;

void onMain() {

    console::enable( 9600 );

    ptr_t<uint> value = new uint(0);

    promise::resolve( coroutine::add( COROUTINE(){
    coBegin

        coDelay( 1000 );
        *value = 10;

    coFinish
    }))

    .then([=]( null_t ){
        console::log( *value );
    })

    .fail([=]( except_t err ){
        console::error( err.what() );
    });

    console::log( "Hello!" );

}