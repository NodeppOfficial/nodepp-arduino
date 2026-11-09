#pragma once

const char CHARSET[] = "012 QWE ASD ZXC 345 RTY FGH VBN 6789UIO JKL MP@<";

namespace enigma { namespace keyboard { GENERATOR( task ){
public: // Variable

  ptr_t<uint> data = ptr_t<uint>( 4, 0x00 ); char id = 0;

public:

  void click_checker() const noexcept { 
    
    int  y = sizeof(uint)*8-1;
    auto x = data[id]; 

    while( x > 0x00 ){ do {
    if  (( x & 0x01 )== 0 ){ break; }
         callback( CHARSET[y*4+id] );
    } while(0); x>>=1; y--; }

  }

  coEmit() {
  coBegin

    while( true ){ while( id-->0 ){ coNext;

      digitalWrite( 4, HIGH ); digitalWrite( 5, HIGH );

      digitalWrite( 2, HIGH );
      shiftOut    ( 3, 13, MSBFIRST, 0x01 << id );
      digitalWrite( 2, LOW  );

      data[id]  = shiftIn( 6, 4, LSBFIRST );
      data[id]<<= 8;
      data[id] |= shiftIn( 6, 4, LSBFIRST );

      click_checker();

      digitalWrite( 4, LOW ); digitalWrite( 5, LOW );

    } id=4; coDelay(50); }

  coFinish }

};}}