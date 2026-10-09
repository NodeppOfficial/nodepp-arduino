#include <nodepp/nodepp.h>
#include <nodepp/expected.h>
#include <nodepp/test.h>

using namespace nodepp;

namespace TEST { namespace EXPECTED {

    void TEST_RUNNER(){
        ptr_t<uint> totl ( 0UL );
        ptr_t<uint> done ( 0UL );
        ptr_t<uint> err  ( 0UL );
        ptr_t<uint> skp  ( 0UL );

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | expected -> done", [](){
            do {
                expected_t<int,string_t> x ( 10 );
                if( !x.has_value() ){ TEST_FAIL(); }
                        TEST_DONE();
            } while(0); TEST_FAIL();
        });

        TEST_ADD( test, "TEST 2 | expected -> error", [](){
            do {
                expected_t<int,string_t> x ( "something went wrong" );
                if( x.has_value() ){ TEST_FAIL(); }
                        TEST_DONE();
            } while(0); TEST_FAIL();
        });

        test.onClose.once([=](){
            console::log("\nRESULT | total:", *totl, "| passed:", *done, "| error:", *err, "| skipped:", *skp );
        });

        test.onDone([=](){ (*done)++; (*totl)++; });
        test.onFail([=](){ (*err) ++; (*totl)++; });
        test.onSkip([=](){ (*skp) ++; (*totl)++; });

        TEST_AWAIT( test );

    }

}}