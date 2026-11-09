#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/test.h>

using namespace nodepp;

namespace TEST { namespace HTTP {

    void TEST_RUNNER(){
        ptr_t<uint> totl ( 0UL );
        ptr_t<uint> done ( 0UL );
        ptr_t<uint> err  ( 0UL );
        ptr_t<uint> skp  ( 0UL );

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | HTTP Fetch (Promise)", [](){
            do{ ptr_t<int> x = new int(0);

                fetch_t args;
                        args.url    = os::resolve_origin( "/" );
                        args.method = "GET";

                http::fetch( args )

                .then([=]( http_t cli ){
                    if( cli.status==200 ){ *x = 1; }
                    else /*------------*/{ *x = 2; }
                })

                .fail([=]( except_t ){ *x = -1; });

                while( *x==0 ){ process::next(); }
                switch( *x ){
                    case 1 : TEST_DONE(); break;
                    case 2 : TEST_FAIL(); break;
                    default: TEST_SKIP(); break;
                }

                        TEST_FAIL();
            } while(0); TEST_FAIL();
        });

        TEST_ADD( test, "TEST 2 | HTTP Fetch (await)", [](){
            do{ ptr_t<int> x = new int(0);

                fetch_t args;
                        args.url    = os::resolve_origin( "/" );
                        args.method = "GET";

                auto fetch = http::fetch( args ).await();

                if( !fetch.has_value() )/*---*/{ TEST_SKIP(); }
                if( fetch.value().status==200 ){ TEST_DONE(); }

                        TEST_FAIL();
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