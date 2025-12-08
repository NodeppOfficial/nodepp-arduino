#include <nodepp.h>

using namespace nodepp;

void onMain() {
    Serial.begin(9600);
    console::log("Hello World!");
}
