#include <LiquidCrystal.h>
#include <nodepp.h>

using namespace nodepp;

LiquidCrystal lcd( 12, 11, 10, 9, 8, 7 );

void onMain() {

  lcd.begin( 16, 2 );
  ptr_t<uchar> interval ( new uchar(0) );

  process::add( coroutine::add( COROUTINE(){
    static uchar interval = 0;
  coBegin

    while( true ){
      lcd.setCursor( 0, 0 );
      lcd.print( string::format( "Tsk1=%d ", interval ).get() );
    coDelay(500); interval = ( interval + 1 ) % 99; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
    static uchar interval = 0;
  coBegin

    while( true ){
      lcd.setCursor( 0, 1 );
      lcd.print( string::format( "Tsk2=%d ", interval ).get() );
    coDelay(200); interval = ( interval + 1 ) % 99; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
    static uchar interval = 0;
  coBegin

    while( true ){
      lcd.setCursor( 9, 0 );
      lcd.print( string::format( "Tsk3=%d ", interval ).get() );
    coDelay(300); interval = ( interval + 1 ) % 99; }

  coFinish
  }));

  process::add( coroutine::add( COROUTINE(){
    static uchar interval = 0;
  coBegin

    while( true ){
      lcd.setCursor( 9, 1 );
      lcd.print( string::format( "Tsk4=%d ", interval ).get() );
    coDelay(400); interval = ( interval + 1 ) % 99; }

  coFinish
  }));

}