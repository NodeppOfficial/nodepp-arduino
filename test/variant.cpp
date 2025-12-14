#include "../src/nodepp/variant.h"

namespace TEST { namespace VARIANT {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | variant initialization string", [](){
            variant_t<string_t,uint,float> mem = "hello world";
            if ( !mem.has_value() )/*---------------*/{ TEST_FAIL(); }
            if ( mem.as<string_t>() != "hello world" ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | variant initialization uint", [](){
            variant_t<string_t,uint,float> mem = type::cast<uint>(10);
            if ( !mem.has_value() )    { TEST_FAIL(); }
            if ( mem.as<uint>() != 10 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 3 | variant initialization float", [](){
            variant_t<string_t,uint,float> mem = type::cast<float>(10);
            if ( !mem.has_value() )/*----*/{ TEST_FAIL(); }
            if ( mem.as<float>() != 10.0f ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 4 | variant error handling", [](){
            variant_t<string_t,uint,float> mem = object_t({ { "var1", 10 } });
            if ( !mem.has_value() )/*----------------------*/{ TEST_FAIL(); }
            if ( mem.as<object_t>()["var1"].as<int>() != 10 ){ TEST_FAIL(); } TEST_FAIL();
        });

        test.onClose.once([=](){
            console::log("\nRESULT | total:", *totl, "| passed:", *done, "| error:", *err, "| skipped:", *skp );
        });

        test.onDone([=](){ (*done)++; (*totl)++; });
        test.onFail([=](){ (*err)++;  (*totl)++; });
        test.onSkip([=](){ (*skp)++;  (*totl)++; });

        TEST_AWAIT( test );

    }

}}