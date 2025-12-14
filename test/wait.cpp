#include "../src/nodepp/wait.h"

namespace TEST { namespace WAIT {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | wait initialization 1", [](){
                  ptr_t<int> x = new int(0);
                  wait_t<string_t> wait; wait.on("test",[=](){ *x=1; });
                  wait.emit("test");
             if ( wait.empty() ){ TEST_FAIL(); }
             if ( *x==0 )/*---*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | wait initialization 2", [](){
                  ptr_t<int> x = new int(0);
                  wait_t<string_t,int> wait; wait.on("test",[=]( int y ){ *x=y; });
                  wait.emit("test",1);
             if ( wait.empty() ){ TEST_FAIL(); }
             if ( *x==0 )/*---*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 3 | once execution", [](){
                  ptr_t<int> x = new int(0);
                  wait_t<string_t> wait; wait.once("test",[=](){ *x+=1; });
                  wait.emit("test"); wait.emit("test"); wait.emit("test");
             if ( *x!=1 )/*--*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 4 | on execution", [](){
                  ptr_t<int> x = new int(0);
                  wait_t<string_t> wait; wait.on("test",[=](){ *x+=1; });
                  wait.emit("test"); wait.emit("test"); wait.emit("test");
             if ( wait.empty() ){ TEST_FAIL(); }
             if ( *x!=3 )/*---*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 5 | skipping", [](){
                  ptr_t<int> x = new int(0);
                  wait_t<string_t> wait; wait.on("test",[=](){ *x+=1; });
                  wait.stop();   wait.emit("test"); 
                  wait.resume(); wait.emit("test"); wait.emit("test");
             if ( wait.empty() ){ TEST_FAIL(); }
             if ( *x!=2 )/*---*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 6 | stopping", [](){
                  ptr_t<int> x = new int(0);
                  wait_t<string_t> wait; wait.on("test",[=](){ *x+=1; });
                  wait.stop();       wait.emit("test"); 
                  wait.emit("test"); wait.emit("test");
             if ( wait.empty() ){ TEST_FAIL(); }
             if ( *x!=0 )/*---*/{ TEST_FAIL(); } TEST_DONE();
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