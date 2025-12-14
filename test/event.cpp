
#include "../src/nodepp/event.h"

namespace TEST { namespace EVENT {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | event initialization 1", [](){
            ptr_t<int> x = new int(0);
            event_t<> event; event.on([=](){ *x=1; });
            event.emit();
            
            if ( event.empty() ){ TEST_FAIL(); }
            if ( *x==0 )/*----*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | event initialization 2", [](){
            ptr_t<int> x = new int(0);
            event_t<int> event; event.on([=]( int y ){ *x=y; });
            event.emit(1);
             
            if ( event.empty() ){ TEST_FAIL(); }
            if ( *x==0 )/*----*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 3 | once execution", [](){
            ptr_t<int> x = new int(0);
            event_t<> event; event.once([=](){ *x+=1; });
            event.emit(); event.emit(); event.emit();
            if ( *x!=1 )/**/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 4 | on execution", [](){
            ptr_t<int> x = new int(0);
            event_t<> event; event.on([=](){ *x+=1; });
            event.emit(); event.emit(); event.emit();
            if ( event.empty() ){ TEST_FAIL(); }
            if ( *x!=3 )/*----*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 5 | skipping", [](){
            ptr_t<int> x = new int(0);
            event_t<> event; event.on([=](){ *x+=1; });
            event.stop();   event.emit(); 
            event.resume(); event.emit(); event.emit();
            if ( event.empty() ){ TEST_FAIL(); }
            if ( *x!=2 )/*----*/{ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 6 | stopping", [](){
            ptr_t<int> x = new int(0);
            event_t<> event; event.on([=](){ *x+=1; });
            event.stop(); event.emit(); 
            event.emit(); event.emit();
            if ( event.empty() ){ TEST_FAIL(); }
            if ( *x!=0 )/*----*/{ TEST_FAIL(); } TEST_DONE();
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