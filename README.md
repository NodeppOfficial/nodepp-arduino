# Nodepp-Arduino

Nodepp is a groundbreaking open-source project that simplifies C++ application development by bridging the gap between the language's raw power and the developer-friendly abstractions of Node.js. By providing a high-level API, Nodepp empowers developers to write C++ code in a familiar, Node.js-inspired style.

One of the standout features of Nodepp is its 100% asynchronous architecture, powered by an internal Event Loop. This design efficiently manages Nodepp’s tasks, enabling you to develop scalable and concurrent applications with minimal code. Experience the power and flexibility of Nodepp as you streamline your development process and create robust applications effortlessly!

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

## Hello world
```cpp
#include <nodepp.h>

using namespace nodepp;

void onMain() {
    console::enable(9600);
    console::log("Hello World!");
}
```

## Events
```cpp
#include <nodepp/nodepp.h>
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

// note that we are using onMain() instead of main()
```

## Timer
```cpp
#include <nodepp/nodepp.h>
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


### More Examples [here](https://github.com/NodeppOfficial/Nodepp/tree/main/examples)

## Compatibility
- 🔗: [NodePP for Window | Linux | Mac | Bsd ](https://github.com/NodeppOfficial/nodepp)
- 🔗: [NodePP for Arduino](https://github.com/NodeppOfficial/nodepp-arduino)
- 🔗: [Nodepp for ESP32](https://github.com/NodeppOfficial/nodepp-ESPXX)
- 🔗: [Nodepp for WASM](https://github.com/NodeppOfficial/nodepp-wasm)
 
## FAQ
- 🔗 : [/r/Nodepp/](https://www.reddit.com/r/Nodepp/comments/1eaq1pu/faq_ask_anything_about_nodepp/)
  
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

**Nodepp** is distributed under the MIT License. See the LICENSE file for more details.
