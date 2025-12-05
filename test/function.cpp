#include "../src/nodepp/function.h"

namespace TEST { namespace FUNCTION {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | function initialization 1", [](){
            function_t<int> clb ([=](){ return 1; });
            if ( clb.empty() ){ TEST_FAIL(); }
            if ( clb() != 1  ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | function initialization 2", [](){
            function_t<int,int> clb ([=]( int x ){ return x; });
            if ( clb.empty() ){ TEST_FAIL(); }
            if ( clb(1) != 1 ){ TEST_FAIL(); } TEST_DONE();
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