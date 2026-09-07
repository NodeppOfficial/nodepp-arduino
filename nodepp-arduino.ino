#include "./src/nodepp/nodepp.h"

using namespace nodepp;

void onMain(){

  console::enable(9600);

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){
      console::log( "hello world" );
    coDelay(500); }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){
      console::log( "bye world" );
    coDelay(300); }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){
      console::log( "COÑO DE LA MADRE" );
    coDelay(1000); }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){
      console::log( "MOJON VERDOSO" );
    coDelay(2000); }

  coFinish
  }));

}
