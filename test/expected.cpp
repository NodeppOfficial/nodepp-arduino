#include "../src/nodepp/expected.h"

namespace TEST { namespace EXPECTED {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | expected -> done", [](){
            expected_t<int,string_t> x ( 10 );
            if  ( !x.has_value() )
                { TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | expected -> error", [](){
            expected_t<int,string_t> x ( "something went wrong" );
            if( x.has_value() ){ TEST_FAIL(); } TEST_DONE();
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