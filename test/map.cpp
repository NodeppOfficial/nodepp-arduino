#include "../src/nodepp/map.h"

namespace TEST { namespace MAP {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | map initialization", [](){
            map_t<string_t, int> map ({
                { "var1", 10 },
                { "var2", 20 },
                { "var3", 30 },
            });
            if ( map.size() != 3 )
               { TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | map searching", [](){
            map_t<string_t, int> map ({
                { "var1", 10 },
                { "var2", 20 },
                { "var3", 30 },
            });
            if ( !map.has("var1") )
               { TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | map indexation", [](){
            map_t<string_t, int> map ({
                { "var1", 10 },
                { "var2", 20 },
                { "var3", 30 },
            }); map["var4"] = 40;

            if ( !map.has("var4") )
               { TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 4 | map deindexation", [](){
            map_t<string_t, int> map ({
                { "var1", 10 },
                { "var2", 20 },
                { "var3", 30 },
            }); map.erase("var2");
            if ( map.has("var2") )
               { TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 4 | map clearing", [](){
            map_t<string_t, int> map ({
                { "var1", 10 },
                { "var2", 20 },
                { "var3", 30 },
            }); map.clear();
            if ( !map.empty() )
               { TEST_FAIL(); } TEST_DONE();
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