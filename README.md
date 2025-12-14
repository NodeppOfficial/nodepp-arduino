# Nodepp-Arduino

Nodepp is a groundbreaking open-source project that simplifies C++ application development by bridging the gap between the language's raw power and the developer-friendly abstractions of Node.js. By providing a high-level API, Nodepp empowers developers to write C++ code in a familiar, Node.js-inspired style.

One of the standout features of Nodepp is its 100% asynchronous architecture, powered by an internal Event Loop. This design efficiently manages Nodepp’s tasks, enabling you to develop scalable and concurrent applications with minimal code. Experience the power and flexibility of Nodepp as you streamline your development process and create robust applications effortlessly!

🔗: [Nodepp The MOST Powerful Framework for Asynchronous Programming in C++](https://medium.com/p/c01b84eee67a)

## Features

- 📌: **Node.js-like API:** Write C++ code in a syntax and structure similar to Node.js, making it easier to learn and use.
- 📌: **Embedded-compatible:** Compatible with several devices like Arduino UNO | Esp8266 | Esp32 | Stm32
- 📌: **High-performance:** Leverage the speed and efficiency of C++ for demanding applications.
- 📌: **Scalability:** Build applications that can handle large workloads and grow with your needs.
- 📌: **Open-source:** Contribute to the project's development and customize it to your specific requirements.

## Bateries Included

- 📌: Include a **build-in JSON** parser / stringify system.
- 📌: Include a **build-in RegExp** engine for processing text strings.
- 📌: Include a **build-in System** that make every object **Async Task** safety.
- 📌: Include a **Smart Pointer** base **Garbage Collector** to avoid **Memory Leaks**.
- 📌: Include support for **Reactive Programming** based on **Events** and **Observers**.
- 📌: Include an **Event Loop** that can handle multiple events and tasks on a single thread.

## Examples

### Hello world
```cpp
#include <nodepp.h>

using namespace nodepp;

void onMain() {
    console::enable(9600);
    console::log("Hello World!");
}
```

### Coroutines
```cpp
#include <nodepp.h>

using namespace nodepp;

void onMain() {

    ptr_t<uchar> IO ({ 2, 3, 4, 5 });
    for( auto x: IO ){ pinMode( x, OUTPUT ); }

    process::add( coroutine::add( COROUTINE(){
        static uchar pin = 0;
    coBegin

        while( true ){
            digitalWrite( pin, LOW );
            pin = ( pin + 1 ) % IO.size();
            digitalWrite( pin, HIGH );
        coDelay( 300 ); }

    coFinish
    }));

}
```

### Events
```cpp
#include <nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

event_t<> ev;

void onMain(){

    pinMode( 13, OUTPUT );

    ev.on([](){
        static bool b=0; b=!b;
        digitalWrite( 13, b );
    });

    ev.emit();

}
```

### Timer
```cpp
#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void onMain(){

    pinMode( 13, OUTPUT );    

    timer::interval([=](){
        static bool b=0; b=!b;
        digitalWrite( 13, b );
    }, 1000 );

}
```

### Promises
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

### More Examples [here](https://nodeppofficial.github.io/nodepp-doc/guide.html)

## Learn By Projects

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

## Nodepp Supports Other Platforms Too
- 🔗: [NodePP for Window | Linux | Mac | Bsd ](https://github.com/NodeppOfficial/nodepp)
- 🔗: [NodePP for Arduino](https://github.com/NodeppOfficial/nodepp-arduino)
- 🔗: [Nodepp for WASM](https://github.com/NodeppOfficial/nodepp-wasm)

## Contribution

If you want to contribute to **Nodepp**, you are welcome to do so! You can contribute in several ways:

- ☕ Buying me a Coffee
- 📢 Reporting bugs and issues
- 📝 Improving the documentation
- 📌 Adding new features or improving existing ones
- 🧪 Writing tests and ensuring compatibility with different platforms
- 🔍 Before submitting a pull request, make sure to read the contribution guidelines.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/edbc_repo)

## License
**Nodepp-arduino** is distributed under the MIT License. See the LICENSE file for more details.
