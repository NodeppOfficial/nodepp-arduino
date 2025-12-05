#include <nodepp.h>

using namespace nodepp;

void onMain() {

    ptr_t<uchar> IO ({ 2, 3, 4, 5 });
    for( auto x: IO ){ pinMode( x, OUTPUT ); }

    process::add( coroutine::add( COROUTINE(){
        static uchar pin = 0;
    coBegin

        while( true ){
            digitalWrite( pin, LOW );
            pin = ( pin + 1 ) % IO.size();
            digitalWrite( pin, HIGH );
        coDelay( 300 ); }

    coFinish
    }));

}