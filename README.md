# Nodepp-Arduino: The Unified Asynchronous Real-Time C++ Runtime
> **The DOOM of Async Frameworks: Write Once, Compile Everywhere, Process Everything.**

[![Platform](https://img.shields.io/badge/platform-Arduino%20|%20ESP32%20|%20ESP8266%20|%20STM32-blue)](https://github.com/NodeppOfficial/nodepp-arduino)
[![MIT License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Nodepp-Arduino is a lightweight, 100% asynchronous framework designed to bring the power of event-driven programming to microcontrollers. It eliminates the limitations of blocking code (like delay()), allowing your Arduino to handle massive concurrency—from sensor polling to complex encryption—without skipping a beat.

By combining an internal Event Loop with EE-optimized memory primitives, Nodepp enables a **Write Once, Compile Everywhere** workflow. Your logic stays consistent whether you're targeting an 8-bit Nano, a dual-core ESP32, or a high-end cloud server.

## Featured Project: Asynchronous Enigma Machine

To showcase [Nodepp for Arduino](https://github.com/NodeppOfficial/nodepp-arduino) efficiency on **bare metal** hardware, we implemented a fully functional Enigma Machine on an Arduino Nano.

https://github.com/user-attachments/assets/9b870671-3854-444f-893d-40fdce31a629

Try it now: [Enigma Machine Simulation](https://wokwi.com/projects/449104127751150593)

## Features

- **Zero-Blocking Architecture:** Never use `delay()` again. Every task runs asynchronously, keeping your MCU responsive.
- **EE-Optimized Memory:** Custom `ptr_t` and `string_t` use **Small Stack Optimization (SSO)** and **zero-copy slicing** to prevent heap fragmentation on low-RAM chips.

- **Universal Logic:** Write your application logic once and deploy it across Linux, Windows, Mac, Android, WASM, and ESP32/Arduino.

- **Batteries Included:** Built-in engines for JSON parsing, RegExp, UTF manipulation, and Promises—all optimized for embedded constraints.

## Code Examples

### Coroutines: Multi-threaded Feel on Single-core Chips
Stop managing complex state machines. Use coDelay to pause a task without freezing the whole system.

```cpp
#include <nodepp.h>

using namespace nodepp;

void onMain() {

    ptr_t<uchar> LEDs ({ 2, 3, 4, 5 }); // SSO Optimized
    for( auto x: LEDs ){ pinMode( x, OUTPUT ); }

    process::add( coroutine::add( COROUTINE(){
        static uchar i = 0;
    coBegin

        while( true ){
            digitalWrite( LEDs[i], LOW );
            i = ( i + 1 ) % LEDs.size();
            digitalWrite( LEDs[i], HIGH );
        coDelay( 300 ); // Non-blocking delay
        }

    coFinish
    }));

}
```

### Event-Driven Logic
Trigger actions based on system signals or custom events seamlessly.

```cpp
#include <nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

event_t<> ev;

void onMain(){
    
    pinMode( 13, OUTPUT );

    ev.on([](){
        static bool state=0; state=!state;
        digitalWrite( 13, state );
    });

    ev.emit(); // Manually trigger or bind to interrupts
}
```

### Asynchronous Promises
Handle long-running tasks or sensor readings using a modern Promise style API.

```cpp
#include <nodepp.h>
#include <nodepp/promise.h>

using namespace nodepp;

void onMain(){ Serial.begin( 9600 );

    promise_t<int,except_t>([=]( res_t<int> res, rej_t<except_t> rej ){
        res( 10 );
    })

    .then([=]( int res ){ console::log( res ); })

    .fail([=]( except_t err ){ console::log( err.what() ); })

}
```

## Explore Projects (Interactive Simulations)

### 3 channel Asynchronous Led Chaser
[![IMAGE](https://thumbs.wokwi.com/projects/397439909199432705/thumbnail.jpg)](https://wokwi.com/projects/397439909199432705)

### LCD 16x2 Async Task

[![IMAGE](https://thumbs.wokwi.com/projects/449159602715398145/thumbnail.jpg)](https://wokwi.com/projects/449159602715398145)

### Event-Driven Button

[![IMAGE](https://thumbs.wokwi.com/projects/448281938490194945/thumbnail.jpg)](https://wokwi.com/projects/448281938490194945)

### Dining Philosophers

[![IMAGE](https://thumbs.wokwi.com/projects/448442428745256961/thumbnail.jpg)](https://wokwi.com/projects/448442428745256961)

### Asynchronous measurement

[![IMAGE](https://thumbs.wokwi.com/projects/448295308358068225/thumbnail.jpg)](https://wokwi.com/projects/448295308358068225)

### Asynchronous Traffic Light

[![IMAGE](https://thumbs.wokwi.com/projects/449004059236124673/thumbnail.jpg)](https://wokwi.com/projects/449004059236124673)

### 3 Channel Asynchronous Counter 

[![IMAGE](https://thumbs.wokwi.com/projects/448348853985471489/thumbnail.jpg)](https://wokwi.com/projects/448348853985471489)

### Enigma Machine
[![IMAGE](https://thumbs.wokwi.com/projects/449104127751150593/thumbnail.jpg)](https://wokwi.com/projects/449104127751150593)

## One Codebase, Every Screen
Nodepp is the only framework that lets you share logic between the deepest embedded layers and the highest web layers.

- **Hardware:** [NodePP for Arduino](https://github.com/NodeppOfficial/nodepp-arduino)
- **Desktop:** [Nodepp for Desktop](https://github.com/NodeppOfficial/nodepp)
- **Browser:** [Nodepp for WASM](https://github.com/NodeppOfficial/nodepp-wasm)

## Contributing

Nodepp is an open-source project that values Mechanical Sympathy and Technical Excellence.

- **Sponsorship:** Support the project via [Ko-fi](https://ko-fi.com/edbc_repo).
- **Bug Reports:** Open an issue via GitHub.
- **License:** MIT.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/edbc_repo)

## License
**Nodepp** is distributed under the MIT License. See the LICENSE file for more details.
