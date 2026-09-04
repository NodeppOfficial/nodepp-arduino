#include <nodepp.h>

using namespace nodepp;

void onMain(){

  ptr_t<uchar> IO ({ 12, 11, 10 });
  for( auto x: IO ){ pinMode( x, OUTPUT ); }

  ptr_t<uint> philosopher_state = new uint( 0x0000 );

  array_t<ptr_t<uchar>> philosopher ({
    ptr_t<uchar>({  0,  1, 14, 0x01 }),
    ptr_t<uchar>({  3,  4,  2, 0x01 }),
    ptr_t<uchar>({  6,  7,  5, 0x01 }),
    ptr_t<uchar>({  9, 10,  8, 0x01 }),
    ptr_t<uchar>({ 12, 13, 11, 0x01 })
  });  

  // philosopher printing state task
  process::add( coroutine::add( COROUTINE(){
  coBegin ; while( true ){

    do {

      //reset all fork state
      *philosopher_state |= 0b0100100100100100;

      //check only forks taken
      for( auto id=philosopher.size(); id-->0; ){
      if ( philosopher[id][3] == 0x02 ){
           *philosopher_state &= ~( 0x001 << philosopher[id+0][2] );
           *philosopher_state &= ~( 0x001 << philosopher[id+1][2] );
      }  }

    } while(0);

    do {
      digitalWrite( 11, LOW ); char mem[sizeof(uint)];
      memcpy( &mem, &philosopher_state, sizeof(uint) );

      for( auto id=sizeof(uint); id-->0; )
         { shiftOut( 12, 10, MSBFIRST, mem[id] ); }

      digitalWrite( 11, HIGH );
    } while(0);

  coNext; } coFinish
  }));
  
  // philosopher state management task - 1 per philosopher
  for( auto id=philosopher.size();id-->0; ){
  process::add( coroutine::add( COROUTINE(){
  coBegin

    while( true ){ do {

      auto a = id == 0 ? ( philosopher.size() ) : ( id );

      auto prev = philosopher[ a-1];
      auto next = philosopher[id+1];  // out of bound supported by nodepp
      auto self = philosopher[id+0];

      //check forks state machine
      do { 

        if  ( self[3]== 0x02 ){ self[3] = 0x01; break; }
        elif( prev[3]!= 0x02 && next[3]!= 0x02 )
            { self[3] = 0x02; break; }
        else{ self[3] = 0x00; break; } 

      } while(0);

      //update philosopher state
      do { switch( self[3] ){

        case 0x00: // starving 
          *philosopher_state |=    0x0001 << self[0];
          *philosopher_state |=    0x0001 << self[1];
        break;

        case 0x01: // thinking
          *philosopher_state &= ~( 0x0001 << self[0] );
          *philosopher_state |=    0x0001 << self[1];
        break;

        case 0x02: // eating
          *philosopher_state &= ~( 0x0001 << self[1] );
          *philosopher_state |=    0x0001 << self[0];
        break; 

      } } while(0);

    } while(0);
    
    if  ( philosopher[id][3]==0x00 ) { coNext; }
    else{ coDelay( ( 5 + rand() % 5 ) * 100 ); }}

  coFinish
  })); }

}