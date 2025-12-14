#include <nodepp.h>

using namespace nodepp;

void onMain(){
    
    console::enable( 9600 );

    ptr_t<uint> GC = new uint(10);

    console::log("-- --");
    console::log( "value->", *GC );
    console::log( "addr ->",  GC );
    console::log( "count->",  GC.count() );

    process::add([=](){

        console::log("-- --");
        console::log( "value->", *GC );
        console::log( "addr ->",  GC );
        console::log( "count->",  GC.count() );

    return -1;
    });

    process::await([=](){

        console::log("-- --");
        console::log( "value->", *GC );
        console::log( "addr ->",  GC );
        console::log( "count->",  GC.count() );

    return -1;
    });

    console::log("-- --");
    console::log( "value->", *GC );
    console::log( "addr ->",  GC );
    console::log( "count->",  GC.count() );

}