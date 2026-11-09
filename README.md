# Nodepp-Arduino: An Asynchronous Runtime for C++ ( Arduino )

[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-Arduino-blue)](https://github.com/NodeppOfficial/nodepp)
[![Valgrind Memory Test](https://img.shields.io/badge/memory-zero_leaks-green)](https://github.com/NodeppOfficial/nodepp/blob/main/benchmark/valgrind_benchmark/readme.md)

Nodepp is an asynchronous C++ runtime that unifies application development under a single syntax, a single codebase, and a single execution model. It starts from a simple premise: you don't need a different language for every layer of your application. The same code that runs on a Linux server can run in a browser via WASM, on an ESP32, or on an Arduino Nano — without changes.

The inspiration doesn't come from a modern framework, but from Doom. Doom wasn't revolutionary for its graphics, but for its portability: it ran on hardware nobody imagined because its design didn't depend on a specific platform. That same philosophy guided Nodepp — a runtime so universal it runs on anything with a C++11 compiler, from 2KB of RAM to 64 cores. It's not a framework tied to an ecosystem. It's a runtime that adapts to the hardware, not the other way around.

Most runtimes grow until they can't be understood. Nodepp went the other direction. ~3,800 lines for the entire core. 2KB for the binary. 0% CPU when idle. No STL, no exceptions, no RTTI — not because they're bad, but because they aren't necessary. The result is a runtime small enough to fit on any controller and simple enough to audit completely. Nothing to trust. Nothing to hide.

## Featured Projects

**[Enigma Machine - Arduino Nano](https://wokwi.com/projects/449104127751150593)**  
A fully functional Enigma machine running on 2KB of RAM.
https://github.com/user-attachments/assets/9b870671-3854-444f-893d-40fdce31a629

**[Spacesus.io](https://spacesus.io)**  
P2P multiplayer game built on Nodepp, WebRTC, and Ungine.
https://github.com/user-attachments/assets/a8b4d56d-0291-4aa8-98e6-926116215f8f

## Quick Start

```cpp
#include <nodepp/nodepp.h>

using namespace nodepp;

void onMain(){ 

    pinMode( 13, INPUT );

    process::add( coroutine::add( COROUTINE(){
    coBegin while( true ){

        digitalWrite( 13, HIGH ); coDelay(1000);
        digitalWrite( 13, LOW  ); coDelay(1000);

    } coFinish }));
    
}
```

## License
MIT. Use it anywhere.