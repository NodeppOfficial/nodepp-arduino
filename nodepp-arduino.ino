
#include <nodepp/nodepp.h>

using namespace nodepp;

void onMain(){ 

    pinMode( 13, INPUT );

    process::add( coroutine::add( COROUTINE(){
    coBegin while( true ){

        digitalWrite( 13, HIGH ); coDelay(1000);
        digitalWrite( 13, LOW  ); coDelay(1000);

    } coFinish }));
    
}