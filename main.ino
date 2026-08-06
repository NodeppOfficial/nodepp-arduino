#include <nodepp.h>

using namespace nodepp;

void onMain() {

    console::enable( 9600 );

    timer::interval([=](){
        static bool b = false;
        digitalWrite( 13, b ); b =! b;
    }, 300 );

    timer::interval([=](){
        console::log( "hello world", process::now() );
    }, 1000 );

}
