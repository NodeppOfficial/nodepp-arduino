#pragma once

inline void show_number( uint value, bool side, uchar data, uchar clock ){

  uchar z = side ? 0x01 : 0x00; switch( value ){
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

inline ptr_t<uchar> get_number( uchar value ){

  string_t raw = string::to_string( value ); for( auto &x: raw ){ x-='0'; }
  
  if( raw.size()==2 ){ return ptr_t<uchar>({ (uchar)raw[0], (uchar)raw[1] }); }
  else /*---------*/ { return ptr_t<uchar>({ (uchar)0x00  , (uchar)raw[0] }); }

}

inline uchar get_index( string_t data, char input, uchar rotA, uchar rotB ){
       uchar  idx = data.find( input )[0];
       char   acc = idx + rotA - rotB;
       return acc < 0? acc+38: acc%38;
}