#pragma once

const char ROTOR0[] = "7RE3 A8B@Z2UJNTY6XQ4P9OFDKCW05VGHMLI1S";
const char ROTOR1[] = "9WL8NFOQP1RC3GDJ IAMZ6UKB40Y@HTSXV72E5";
const char ROTOR2[] = "QUM@OLTZ1SKYXGV469 PNRWA72CDB0JI5HE8F3";

const char ROTORA[] = "LGR@1IMHNDQ6U4C9EXFPSAZO7BK 052YWT3JV8";
const char ROTORB[] = "8VJ3TWY250 KB7OZASPFXE9C4U6QDNHMI1@RGL";

namespace enigma { namespace rotor { GENERATOR( task ){
public: //Variables

  ptr_t<uchar> data = ptr_t<uchar>({ 0x00,0x00,0x00 });

  void add( uchar id ) const noexcept { data[id] =(data[id]+1) % 38; }
  void sub( uchar id ) const noexcept { data[id]==0?data[id]=37: data[id]--; }

public:

  int read_data_task() const noexcept {

    digitalWrite( 7, HIGH ); digitalWrite( 8, HIGH ); 
    auto raw = shiftIn( 9, 7, LSBFIRST );
    digitalWrite( 8, LOW  ); digitalWrite( 7, LOW  );

  coStart

    while( true ){ coWait( raw==0x00 ); do {

      if  ( raw & 0b00000010 ){ process::reset(); }

      if  ( raw & 0b01000000 ){ sub(2); }
      elif( raw & 0b10000000 ){ add(2); }

      if  ( raw & 0b00010000 ){ sub(1); }
      elif( raw & 0b00100000 ){ add(1); }

      if  ( raw & 0b00000100 ){ sub(0); }
      elif( raw & 0b00001000 ){ add(0); }
      
    } while(0); coWait( raw!=0x00 );
    /*-------*/ coDelay(50); }

  coStop }

  int write_data_task() const noexcept {
  coStart

    while( true ){ do { 

      ptr_t<uchar> data_0 = get_number( data[0] );
      ptr_t<uchar> data_1 = get_number( data[1] );
      ptr_t<uchar> data_2 = get_number( data[2] ); 

      digitalWrite( 11, LOW );

      show_number( data_0[0], 0, 12, 10 );
      show_number( data_1[0], 0, 12, 10 );
      show_number( data_2[0], 0, 12, 10 );

      digitalWrite( 11, HIGH );
      digitalWrite( 11, LOW  );

      show_number( data_0[1], 1, 12, 10 );
      show_number( data_1[1], 1, 12, 10 );
      show_number( data_2[1], 1, 12, 10 );

      digitalWrite( 11, HIGH );

    } while(0); coNext; }

  coStop }

  char encode( char idxx ) const noexcept { 

    if( data[1]==0 ){ add(2); } /*---*/
    if( data[0]==0 ){ add(1); } add(0);
		 
		char idx0 = ROTOR0[ get_index( ROTOR1, idxx, data[0], data[1] ) ];
		char idx1 = ROTOR1[ get_index( ROTOR2, idx0, data[1], data[2] ) ];
		char idx2 = ROTOR2[ get_index( ROTORA, idx1, data[2], 0       ) ];
		
		char idx3 = ROTORB[ get_index( ROTOR2, idx2, 0      , data[2] ) ];
		char idx4 = ROTOR2[ get_index( ROTOR1, idx3, data[2], data[1] ) ];
		char idx5 = ROTOR1[ get_index( ROTOR0, idx4, data[1], data[0] ) ];

    return /**/ idx5;

  }

  coEmit(){
  coBegin

    while( true ){ 
      read_data_task (); /*---*/
      write_data_task(); coNext; 
    }

  coFinish }

};}}