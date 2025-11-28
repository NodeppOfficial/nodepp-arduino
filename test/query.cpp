#include "../src/nodepp/query.h"

namespace TEST { namespace QUERY {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | query initialization", [](){
            query_t query = nodepp::query::parse( "?var1=10&var2=20&var3=30" );
            if ( query.size() != 3 )/**/{ TEST_FAIL(); }
            if ( query["var1"] != "10" ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | query searching", [](){
            query_t query ({
                { "var1", "10" },
                { "var2", "20" },
                { "var3", "30" }
            });

            if ( !query.has("var1") ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 3 | query parsing", [](){
            string_t out = query::format( query_t({
                { "var1", "10" },
                { "var2", "20" },
                { "var3", "30" }
            }) );
            if( out!="?var1=10&var2=20&var3=30" ){ TEST_FAIL(); } TEST_DONE();
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