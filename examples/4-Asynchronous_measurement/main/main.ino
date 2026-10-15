#include <nodepp.h>

using namespace nodepp;

void draw_number( char value, bool digit ){

  auto dig = digit ? 0x00 : 0x01; 
  digitalWrite( 3, LOW );

  switch( value ){
    case 1 : shiftOut( 4, 2, LSBFIRST, 0b01100000 | dig ); break;
    case 2 : shiftOut( 4, 2, LSBFIRST, 0b11011010 | dig ); break;
    case 3 : shiftOut( 4, 2, LSBFIRST, 0b11110010 | dig ); break;
    case 4 : shiftOut( 4, 2, LSBFIRST, 0b01100110 | dig ); break;
    case 5 : shiftOut( 4, 2, LSBFIRST, 0b10110110 | dig ); break;
    case 6 : shiftOut( 4, 2, LSBFIRST, 0b10111110 | dig ); break;
    case 7 : shiftOut( 4, 2, LSBFIRST, 0b11100000 | dig ); break;
    case 8 : shiftOut( 4, 2, LSBFIRST, 0b11111110 | dig ); break;
    case 9 : shiftOut( 4, 2, LSBFIRST, 0b11110110 | dig ); break;
    default: shiftOut( 4, 2, LSBFIRST, 0b11111100 | dig ); break;
  }
      
  digitalWrite( 3, HIGH );

}

void onMain() {

  Serial.begin(9600);

  ptr_t<int>   val=new int(0);
  ptr_t<int>   dis=new int(0);

  ptr_t<uchar> INP ({ 11, A7 });
  ptr_t<uchar> OUT ({ 12, 10, 9, 8, 7, 6, 5, 4, 3, 2 });

  for( auto x: INP ){ pinMode( x, INPUT  ); }
  for( auto x: OUT ){ pinMode( x, OUTPUT ); }

  process::add( coroutine::add( COROUTINE(){
    static char x = 0;
  coBegin

    while( true ){
      digitalWrite( OUT[x+1], LOW  );
      x = ( x + 1 ) % 6; 
      digitalWrite( OUT[x+1], HIGH );
    coDelay( 100 ); }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){

      digitalWrite( OUT[0], HIGH ); coNext;
      digitalWrite( OUT[0], LOW  );

     *dis =pulseIn( 11    , HIGH ) / 58;
     *val =analogRead( INP[1] );

    coNext; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){

      draw_number( floor( *dis / 40  ), 0 );
      draw_number( floor( *val / 100 ), 1 );

    coNext; }

  coFinish
  }));

}
