namespace TEST { namespace PTR {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | ptr initialization 1", [](){
            ptr_t<uint> arr ({ 10, 50, 90, 20 });
            if ( arr.size() != 4 ){ TEST_FAIL(); }
            if ( arr[0]     !=10 ){ TEST_FAIL(); }
            if ( arr[1]     !=50 ){ TEST_FAIL(); }
            if ( arr[2]     !=90 ){ TEST_FAIL(); }
            if ( arr[3]     !=20 ){ TEST_FAIL(); } 
            if ( arr[4]     !=10 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 1 | ptr initialization 2", [](){
            ptr_t<uint> arr ( new uint(1000) );
            if ( *arr != 1000 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 12 | ptr clearing", [](){
            ptr_t<uint> arr ({ 10, 20, 30 });  arr = nullptr;
            if ( !arr.null() ){ TEST_FAIL(); } TEST_DONE();
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