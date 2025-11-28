#include "../src/nodepp/promise.h"

namespace TEST { namespace TASK {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | async task testing", [](){
                ptr_t<int> x = new int(0); 
                ptr_t<int> y = new int(3);

                process::add( coroutine::add( COROUTINE(){
                coBegin

                    while( *y>0 ){ *x += 10; *y-=1; coNext; }
                    
                coFinish
                }));

             while( *y!=0 ){ process::next(); }
                if( *x != 30 ){ TEST_FAIL();  } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | sync task testing", [](){
                ptr_t<int> x = new int(0); 
                ptr_t<int> y = new int(3);

                process::await( coroutine::add( COROUTINE(){
                coBegin

                    while( *y>0 ){ *x += 10; *y-=1; coNext; }
                    
                coFinish
                }));

                if( *x != 30 ){ TEST_FAIL(); } TEST_DONE();
        });

        #ifdef NODEPP_ALLOW_EXCEPTION
        TEST_ADD( test, "TEST 3 | task resolver testing", [](){
                ptr_t<int> x = new int(0); 
                ptr_t<int> y = new int(3);

                promise::resolve( coroutine::add( COROUTINE(){
                coBegin

                    while( *y>0 ){ *x += 10; *y-=1; coNext; }
                    
                coFinish
                })).emit();
                
             while( *y!=0 ){ process::next(); }
                if( *x != 30 ){ TEST_FAIL (); } TEST_DONE();
        });
        #endif

        test.onClose.once([=](){
            console::log("\nRESULT | total:", *totl, "| passed:", *done, "| error:", *err, "| skipped:", *skp );
        });

        test.onDone([=](){ (*done)++; (*totl)++; });
        test.onFail([=](){ (*err)++;  (*totl)++; });
        test.onSkip([=](){ (*skp)++;  (*totl)++; });

        TEST_AWAIT( test );

    }

}}