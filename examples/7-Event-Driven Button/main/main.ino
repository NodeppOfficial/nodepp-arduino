#include <nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;
event_t<int> evento;

void onMain() {

  Serial.begin( 9600 ); pinMode( 7, INPUT );

  ptr_t<char> IO ({ 12, 11, 10, 9, 8 });
  for( auto x:IO ){ pinMode( x,OUTPUT ); }

  evento.on([=]( int x ){
    digitalWrite( 10, x & 0b001 );
    digitalWrite( 11, x & 0b010 );
    digitalWrite( 12, x & 0b100 );
    console::log( "button pressed" );
  });

  process::add( coroutine::add( COROUTINE(){
    static uint x = 0; 
  coBegin

    while( true ){ coDelay( 1000 );
      console::log( "interval", x );
    x++; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
    static bool x = 0;
  coBegin

    while( true ) { coDelay( 300 );
      digitalWrite( 9,  x );
      digitalWrite( 8, !x);
    x =! x; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
    static char x = 7;
  coBegin

    while( true ){
      coWait( digitalRead( 7 ) == LOW );
      evento.emit(x); x = ( x + 1 ) % 8;
      coWait( digitalRead( 7 ) == HIGH );
      coDelay( 300 );
    }

  coFinish
  }));

  console::log( "hello world" );

}