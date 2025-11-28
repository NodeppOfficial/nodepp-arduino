#include "../src/nodepp.h"
#include "../src/nodepp/test.h"

using namespace nodepp;

#include "test/any.cpp"
#include "test/ptr.cpp"
#include "test/map.cpp"
#include "test/task.cpp"
#include "test/loop.cpp"
#include "test/wait.cpp"
#include "test/tuple.cpp"
#include "test/event.cpp"
#include "test/query.cpp"
#include "test/array.cpp"
#include "test/queue.cpp"
#include "test/variant.cpp"
#include "test/promise.cpp"
#include "test/function.cpp"
#include "test/observer.cpp"
#include "test/optional.cpp"
#include "test/expected.cpp"

void onMain(){ 
    
    TEST::ANY     ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::PTR     ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::MAP     ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::TASK    ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::LOOP    ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::WAIT    ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::TUPLE   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::EVENT   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::QUERY   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::ARRAY   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::QUEUE   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::VARIANT ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::PROMISE ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::FUNCTION::TEST_RUNNER(); conio::log("\n---\n");
    TEST::OBSERVER::TEST_RUNNER(); conio::log("\n---\n");
    TEST::EXPECTED::TEST_RUNNER(); conio::log("\n---\n");
    TEST::OPTION  ::TEST_RUNNER(); conio::log("\n---\n");

}