#include <nodepp.h>

using namespace nodepp;
#define FLAG 0b10000000

void onMain() {

    auto IO = ptr_t<uchar>({ 2, 3, 4, 5 });
    for( auto x: IO ){ pinMode( x, INPUT ); }

    process::add( coroutine::add( COROUTINE(){
        static uchar x = 0;
    coBegin

        while(true){

            digitalWrite( x, HIGH );

            if((x&0x0F)==0x00 ){ 
            if( x & FLAG ){ x &=~ FLAG; }
            else /*----*/ { x |=  FLAG; }}
            
            x = ( x + 1 ) % IO.size();

        coDelay(100); }

    coFinish
    }));

}
