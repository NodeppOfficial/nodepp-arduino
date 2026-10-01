#include <nodepp.h>

using namespace nodepp;

void draw_number( char value, bool digit, uchar data, uchar clk ){

  auto dig = digit ? 0x00 : 0x01;

  switch( value ){
    case 0 : shiftOut( data, clk, LSBFIRST, 0b11111100 | dig ); break;
    case 1 : shiftOut( data, clk, LSBFIRST, 0b01100000 | dig ); break;
    case 2 : shiftOut( data, clk, LSBFIRST, 0b11011010 | dig ); break;
    case 3 : shiftOut( data, clk, LSBFIRST, 0b11110010 | dig ); break;
    case 4 : shiftOut( data, clk, LSBFIRST, 0b01100110 | dig ); break;
    case 5 : shiftOut( data, clk, LSBFIRST, 0b10110110 | dig ); break;
    case 6 : shiftOut( data, clk, LSBFIRST, 0b10111110 | dig ); break;
    case 7 : shiftOut( data, clk, LSBFIRST, 0b11100000 | dig ); break;
    case 8 : shiftOut( data, clk, LSBFIRST, 0b11111110 | dig ); break;
    case 9 : shiftOut( data, clk, LSBFIRST, 0b11110110 | dig ); break;
    default: shiftOut( data, clk, MSBFIRST, value      | dig ); break;
  }

}

void draw_data( char value, uchar data, uchar clk ){
  shiftOut    ( data, clk, MSBFIRST, value );
}

void onMain(){

  ptr_t<uchar> OUT ({ 8, 7, 6, 4, 3, 2, 13 });
  ptr_t<uchar> INP ({ 12, 11, 10 });

  array_t<ptr_t<uchar>> digit_context ({ 
    ptr_t<uchar>({ 8, 12, 4, 0x00, 0x00, 0x00 }), 
    ptr_t<uchar>({ 7, 11, 3, 0x00, 0x00, 0x00 }), 
    ptr_t<uchar>({ 6, 10, 2, 0x00, 0x00, 0x00 }), 
  });

  for( auto x: INP ){ pinMode( x, INPUT  ); }
  for( auto x: OUT ){ pinMode( x, OUTPUT ); }

  // counter_task_manager
  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ) {

      for( auto x: digit_context ){
      if ( digitalRead( x[1] )==HIGH )
         { x[3] = 0x00; x[4] = 0x00; x[5] = 0x00; }

      digitalWrite( 13, LOW );
        draw_data  ( x[5],    x[0], x[2] );
        draw_number( x[4], 1, x[0], x[2] );
      digitalWrite( 13, HIGH );

      digitalWrite( 13, LOW );
        draw_data  ( x[5],    x[0], x[2] );
        draw_number( x[3], 0, x[0], x[2] );
      digitalWrite( 13, HIGH );

      }

    coNext; }

  coFinish
  }));

  // counter_task_increaser 1 per 7 segment
  for( char id=digit_context.size(); id-->0; ){
  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ) { do {

      auto x = digit_context[id];

      /*----------*/ x[4] = ( x[4] + 1 ) % 10;
      if( x[4]==0 ){ x[3] = ( x[3] + 1 ) % 10; }
      if( x[4]==0 ){ x[5] = ( x[5] + 1 ) %  8; }

    } while(0); coDelay(300); }

  coFinish
  })); }

}