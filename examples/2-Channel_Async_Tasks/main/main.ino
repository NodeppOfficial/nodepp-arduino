#include <nodepp.h>

using namespace nodepp;

void draw_number( uint value, uchar data, uchar latch, uchar clock ){

  string_t   raw = string::to_string( value ); for( auto &x: raw ){ x-='0'; }
  
  uchar chars[2] = { 
    raw.size()==2 ? raw[0] : 0x00 ,
    raw.size()==2 ? raw[1] : raw[0]
  };

  for( char x=2; x-->0; ){ /**/ uchar y = chars[x];
    digitalWrite( latch, LOW ); uchar z = x%2==0 ? 0x01 : 0x00;

    switch( y ){
      case 1 : shiftOut( data, clock, LSBFIRST, 0b01100000 | z ); break;
      case 2 : shiftOut( data, clock, LSBFIRST, 0b11011010 | z ); break;
      case 3 : shiftOut( data, clock, LSBFIRST, 0b11110010 | z ); break;
      case 4 : shiftOut( data, clock, LSBFIRST, 0b01100110 | z ); break;
      case 5 : shiftOut( data, clock, LSBFIRST, 0b10110110 | z ); break;
      case 6 : shiftOut( data, clock, LSBFIRST, 0b10111110 | z ); break;
      case 7 : shiftOut( data, clock, LSBFIRST, 0b11100000 | z ); break;
      case 8 : shiftOut( data, clock, LSBFIRST, 0b11111110 | z ); break;
      case 9 : shiftOut( data, clock, LSBFIRST, 0b11110110 | z ); break;
      default: shiftOut( data, clock, LSBFIRST, 0b11111100 | z ); break;
    }
        
    digitalWrite( latch, HIGH );
  }

}

void onMain() {

  console::enable(9600);

  ptr_t<int>   val= new int(0);
  ptr_t<int>   dis= new int(0);

  ptr_t<uchar> INP ({ 11, A0 });
  ptr_t<uchar> OUT ({ 12, 7, 6, 5, 4, 3, 2 });

  for( auto x: INP ){ pinMode( x, INPUT  ); }
  for( auto x: OUT ){ pinMode( x, OUTPUT ); }

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){

      digitalWrite( 12, HIGH ); coNext;
      digitalWrite( 12, LOW  );

     *dis = pulseIn( 11 , HIGH ) / 58;
     *val = analogRead( A0 );

    coNext; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){

    draw_number( type::cast<uint>( floor( *dis /  4.03 ) ), 4, 3, 2 );
    draw_number( type::cast<uint>( floor( *val / 10.24 ) ), 5, 6, 7 );

    coNext; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){

      console::log( "HC_SE84", *dis, "VALUE", *val );

    coNext; }

  coFinish
  }));

}