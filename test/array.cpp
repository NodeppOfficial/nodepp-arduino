namespace TEST { namespace ARRAY {

    void TEST_RUNNER(){
        ptr_t<uint> totl = new uint(0);
        ptr_t<uint> done = new uint(0);
        ptr_t<uint> err  = new uint(0);
        ptr_t<uint> skp  = new uint(0);

        auto test = TEST_CREATE();

        TEST_ADD( test, "TEST 1 | array initialization", [](){
            array_t<uint> arr ({ 10, 50, 90, 20 });
            if ( arr.size() != 4 ){ TEST_FAIL(); }
            if ( arr[0]     !=10 ){ TEST_FAIL(); }
            if ( arr[1]     !=50 ){ TEST_FAIL(); }
            if ( arr[2]     !=90 ){ TEST_FAIL(); }
            if ( arr[3]     !=20 ){ TEST_FAIL(); } 
            if ( arr[4]     !=10 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 2 | array sorting", [](){
            array_t<uint> arr ({ 10, 50, 90, 20 });
            arr = arr.sort([=]( int a, int b ){ return a<=b; });
            if ( arr.size() != 4 ){ TEST_FAIL(); }
            if ( arr[0]     !=10 ){ TEST_FAIL(); }
            if ( arr[1]     !=20 ){ TEST_FAIL(); }
            if ( arr[2]     !=50 ){ TEST_FAIL(); }
            if ( arr[3]     !=90 ){ TEST_FAIL(); } 
            if ( arr[4]     !=10 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 3 | array pop", [](){
            array_t<uint> arr ({ 10, 50, 90, 20 }); arr.pop();
            if ( arr.size() != 3 ){ TEST_FAIL(); }
            if ( arr[3]     !=10 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 4 | array shift", [](){
            array_t<uint> arr ({ 10, 50, 90, 20 }); arr.shift();
            if ( arr.size() != 3 ){ TEST_FAIL(); }
            if ( arr[3]     !=50 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 5 | array unshift", [](){
            array_t<uint> arr ({ 10, 50, 90, 20 }); arr.unshift( 5 );
            if ( arr.size() != 5 ){ TEST_FAIL(); }
            if ( arr[0]     != 5 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 6 | array push", [](){
            array_t<uint> arr ({ 10, 50, 90, 20 }); arr.push( 5 );
            if ( arr.size() != 5 ){ TEST_FAIL(); }
            if ( arr[4]     != 5 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 7 | array concatenation 1", [](){
            array_t<uint> arr1 ({ 10, 20, 30 }); 
            array_t<uint> arr2 ({ 40, 50, 60 }); 
            arr1.insert( -1, arr2.size(), arr2.get() );
            if ( arr1.size()!= 6 ){ TEST_FAIL(); }
            if ( arr1[0]    !=10 ){ TEST_FAIL(); }
            if ( arr1[5]    !=60 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 8 | array concatenation 2", [](){
            array_t<uint> arr1 ({ 10, 20, 30 }); 
            array_t<uint> arr2 ({ 40, 50, 60 }); 
            arr1.insert( 0, arr2.size(), arr2.get() );
            
            if ( arr1.size()!= 6 ){ TEST_FAIL(); }
            if ( arr1[0]    !=40 ){ TEST_FAIL(); }
            if ( arr1[5]    !=30 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 9 | array slicing", [](){
            array_t<uint> arr ({ 10, 20, 30, 40, 50 });
            auto tmp = arr.slice( 1, 3 );
            
            if ( tmp.empty() )/**/{ TEST_FAIL(); }
            if ( tmp.size() != 2 ){ TEST_FAIL(); }
            if ( arr.size() != 5 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 10 | array splicing 1", [](){
            array_t<uint> arr ({ 10, 20, 30, 40, 50 });
            auto tmp = arr.splice( 1, 3 );
            
            if ( tmp.empty() )/**/{ TEST_FAIL(); }
            if ( tmp.size() != 3 ){ TEST_FAIL(); }
            if ( arr.size() == 5 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 11 | array splicing 2", [](){
            array_t<uint> arr ({ 10, 20, 30, 40, 50 });
            arr.splice( 1, 3, { 2, 3, 4 } );
             
            if ( arr.empty() )/**/{ TEST_FAIL(); }
            if ( arr.size() != 5 ){ TEST_FAIL(); } TEST_DONE();
        });

        TEST_ADD( test, "TEST 12 | array clearing", [](){
            array_t<uint> arr ({ 10, 20, 30 }); arr.clear();
            if ( !arr.empty() ){ TEST_FAIL(); } TEST_DONE();
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