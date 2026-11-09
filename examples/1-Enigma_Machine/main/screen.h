#pragma once

const char ENCMSG[] = "\xff[    - ]\xff[ENC]\xff";
const char DECMSG[] = "\xff[    - ]\xff[DEC]\xff";

LiquidCrystal_I2C lcd( 0x27, 16, 2 );

namespace enigma { namespace screen { GENERATOR( task ){ 
public: // Variables

  task() { lcd.init(); lcd.backlight(); }
  queue_t<char> dec, enc;

public:

  void clear() const noexcept { uchar y=0; /**/ dec.clear(); enc.clear();
    y=0; for( auto &x:ENCMSG ){ lcd.setCursor(y,0); lcd.write(x); y++; }
    y=0; for( auto &x:DECMSG ){ lcd.setCursor(y,1); lcd.write(x); y++; }
  }

  void draw() const noexcept {

    do { auto x = dec.first(); char y=7; while( x!=nullptr ){
       /*----------*/ lcd.setCursor(y,0); lcd.write(x->data);
    if ( y==7 ){ y--; }
    x = x->next; y--; } } while(0);

    do { auto x = enc.first(); char y=7; while( x!=nullptr ){
       /*----------*/ lcd.setCursor(y,1); lcd.write(x->data);
    if ( y==7 ){ y--; }
    x = x->next; y--; } } while(0);

  }

  void append( char key, char yek ) const noexcept {
    dec.unshift( key ); if( dec.size()>5 ){ dec.pop(); } /*---*/
    enc.unshift( yek ); if( enc.size()>5 ){ enc.pop(); } draw();
  }

  coEmit(){ clear(); return -1; }

}; }}