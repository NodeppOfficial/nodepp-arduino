#include <nodepp.h>

using namespace nodepp;

enum STATES {
  RED_LIGHT        = 0b00000001,
  GREEN_LIGHT      = 0b00000010,
  YELLOW_LIGHT     = 0b00000100,
  PEDESTRIAN_LIGHT = 0b00001000,
};

void show_number( uint value, bool side, uchar data, uchar clock ){

  uchar z = side ? 0x00 : 0x01; switch( value ){
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

}

void show_state( char state, uchar data, uchar clock ){
  uchar value = 0x00;

  if( state & RED_LIGHT        ){ value |= 0x01 << 2; }
  if( state & GREEN_LIGHT      ){ value |= 0x01 << 0; }
  if( state & YELLOW_LIGHT     ){ value |= 0x01 << 1; }
  if( state & PEDESTRIAN_LIGHT ){ value |= 0x01 << 3; }
  else /*--------------------*/ { value |= 0x01 << 4; }

  shiftOut( data, clock, MSBFIRST, value );
}

ptr_t<uchar> get_number( uchar value ){

  string_t raw = string::to_string( value ); for( auto &x: raw ){ x-='0'; }
  
  if( raw.size()==2 ){ return ptr_t<uchar>({ (uchar)raw[0], (uchar)raw[1] }); }
  else /*---------*/ { return ptr_t<uchar>({ (uchar)0x00  , (uchar)raw[0] }); }

}

void onMain() {

  auto light_state   = type::bind( new char( YELLOW_LIGHT ) );
  auto light_counter = type::bind( new char( 0x00 ) );

  ptr_t<uchar> OUT ({ 11, 10, 9 });  
  ptr_t<uchar> INP ({ 12 });

  for( auto x: INP ){ pinMode( x, INPUT  ); }
  for( auto x: OUT ){ pinMode( x, OUTPUT ); }

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){ if( *light_counter != 0 ){ goto NEXT; }

      if ( *light_state & RED_LIGHT ){ 
        *light_counter = 30;
        *light_state   = GREEN_LIGHT; 
      }

      elif( *light_state & GREEN_LIGHT ){ 
        *light_counter = 10;
        *light_state   = YELLOW_LIGHT;
      }

      elif( *light_state & YELLOW_LIGHT ){ 
        *light_counter = 60; 
        *light_state   = RED_LIGHT;
        *light_state  |= PEDESTRIAN_LIGHT;
      }

    NEXT:; *light_counter-=1; coDelay( 1000 ); }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){ 
    coWait(( *light_state & RED_LIGHT )==0 );
      if ( digitalRead( 12 ) ){ 
        *light_counter = 60;
        *light_state  |= RED_LIGHT;
      }
    coNext; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){ do { 
      
    auto data = get_number( *light_counter );

    digitalWrite( 10, LOW );
      show_state (*light_state,    11, 9 );
      show_number( data[0]    , 0, 11, 9 );
    digitalWrite( 10, HIGH );

    digitalWrite( 10, LOW );
      show_state (*light_state,    11, 9 );
      show_number( data[1]    , 1, 11, 9 );
    digitalWrite( 10, HIGH );

    } while(0); coNext; }
    
  coFinish
  }));

}