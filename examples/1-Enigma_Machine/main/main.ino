#include <LiquidCrystal_I2C.h>

#include <nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;
function_t<void,char> callback;

#include "utils.h"
#include "rotor.h"
#include "board.h"
#include "screen.h"

namespace enigma { void main() {

  ptr_t<char> OUT ({ 13, 12, 11, 10, 8, 7, 5, 4, 3, 2 });
  ptr_t<char> INP ({ 9, 6 });

  for( auto x: OUT ){ pinMode( x, OUTPUT ); }
  for( auto x: INP ){ pinMode( x, INPUT  ); }

  /* Enigma Task */
  auto t0 = rotor   ::task(); process::add( t0 );
  auto t1 = screen  ::task(); process::add( t1 );
  auto t2 = keyboard::task(); process::add( t2 );

  /* OnKeyboarClickEvent */
  callback = [=]( char key ){ 
    if(key=='<'){ t1.clear(); return; }
    t1.append( t0.encode(key), key );
  };

}}

void onMain() { enigma::main(); }
