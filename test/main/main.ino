#include <nodepp.h>
#include <nodepp/test.h>

using namespace nodepp;

#include "./files/url.cpp"
#include "./files/any.cpp"
#include "./files/ptr.cpp"
#include "./files/map.cpp"
#include "./files/json.cpp"
#include "./files/task.cpp"
#include "./files/path.cpp"
#include "./files/loop.cpp"
#include "./files/tuple.cpp"
#include "./files/event.cpp"
#include "./files/query.cpp"
#include "./files/array.cpp"
#include "./files/queue.cpp"
#include "./files/regex.cpp"
#include "./files/cookie.cpp"
#include "./files/string.cpp"
#include "./files/promise.cpp"
#include "./files/listener.cpp"
#include "./files/observer.cpp"
#include "./files/function.cpp"
#include "./files/optional.cpp"
#include "./files/expected.cpp"
#include "./files/coroutine.cpp"

void onMain(){ 
    
    TEST::URL     ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::ANY     ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::PTR     ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::MAP     ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::TASK    ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::PATH    ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::LOOP    ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::LISTENER::TEST_RUNNER(); conio::log("\n---\n");
    TEST::TUPLE   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::COOKIE  ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::EVENT   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::QUERY   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::JSON    ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::ARRAY   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::QUEUE   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::REGEX   ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::STRING  ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::PROMISE ::TEST_RUNNER(); conio::log("\n---\n");
    TEST::COROUTINE::TEST_RUNNER(); conio::log("\n---\n");
    TEST::FUNCTION::TEST_RUNNER(); conio::log("\n---\n");
    TEST::OBSERVER::TEST_RUNNER(); conio::log("\n---\n");
    TEST::EXPECTED::TEST_RUNNER(); conio::log("\n---\n");
    TEST::OPTION  ::TEST_RUNNER(); conio::log("\n---\n");

}
