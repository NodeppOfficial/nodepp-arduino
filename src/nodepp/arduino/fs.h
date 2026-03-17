/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_ARDUINO_FS
#define NODEPP_ARDUINO_FS

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace fs {

    inline file_t readable( const string_t& path, const ulong& _size=CHUNK_SIZE ){ return file_t( path, "r", _size ); }
    inline file_t writable( const string_t& path, const ulong& _size=CHUNK_SIZE ){ return file_t( path, "w", _size ); }

    /*─······································································─*/

    inline bool exists_file( const string_t& path ){
        FILE* fp = fopen( path.get(), "r" );
        if( fp == nullptr ){ return 0; }
        fclose(fp); /*----*/ return 1;
    }

    /*─······································································─*/

    inline promise_t<string_t,except_t> read_file( const string_t& path ){
    return promise_t<string_t,except_t> ([=]( 
        res_t<string_t> res,  rej_t<except_t> rej
    ){

        if( !exists_file( path ) ){ rej( "file not found" ); return; }

        auto rd1 = type::bind( generator::file::read() );
        auto fl1 = type::bind( file_t( path, "r" ) );
        auto bff = ptr_t<string_t>( 0UL );

        process::add( coroutine::add( COROUTINE(){
        coBegin

            while( fl1->is_available() ){
                
                coWait( (*rd1)( &fl1 ) == 1 );
                if( rd1->state==0 ){ break; }

               *bff += rd1->data;

            coNext; } res( *bff );

        coFinish
        }));

    }); }

    /*─······································································─*/

    inline promise_t<ulong,except_t> write_file( const string_t& path, const string_t& message ){
    return promise_t<ulong,except_t> ([=]( 
        res_t<ulong> res, rej_t<except_t> rej
    ){
        
        if( !exists_file( path ) ){ rej( "file not found" ); return; }

        auto rd1 = type::bind( generator::file::write() );
        auto fl1 = type::bind( file_t( path, "w" ) );
        auto bff = ptr_t<ulong>( 0UL, 0UL );

        process::add( coroutine::add( COROUTINE(){
        coBegin

            while( fl1->is_available() ){
                
                coWait( (*rd1)( &fl1, message ) == 1 );
                if( rd1->state==0 ){ break; }

               *bff += rd1->state;

            coNext; } res( *bff );

        coFinish
        }));

    }); }

    /*─······································································─*/

    inline promise_t<ulong,except_t> append_file( const string_t& path, const string_t& message ){
    return promise_t<ulong,except_t> ([=]( 
        res_t<ulong> res,  rej_t<except_t> rej
    ){
        
        if( !exists_file( path ) ){ rej( "file not found" ); return; }

        auto rd1 = type::bind( generator::file::write() );
        auto fl1 = type::bind( file_t( path, "a+" ) );
        auto bff = ptr_t<ulong>( 0UL, 0UL );

        process::add( coroutine::add( COROUTINE(){
        coBegin

            while( fl1->is_available() ){
                
                coWait( (*rd1)( &fl1, message ) == 1 );
                if( rd1->state==0 ){ break; }

               *bff += rd1->state;

            coNext; } res( *bff );

        coFinish
        }));

    }); }

    /*─······································································─*/

    inline int copy_file( const string_t& src, const string_t& des ){
        if( !exists_file( src ) ){ return -1; } 
        stream::pipe( file_t( src, "r" ), file_t( des, "w" ) ); 
    return 1; }

    /*─······································································─*/

    inline int rename_file( const string_t& oname, const string_t& nname ) {
        if( oname.empty() || nname.empty() ){ return -1; }
        return rename( oname.c_str(), nname.c_str() );
    }

    /*─······································································─*/

    inline int move_file( const string_t& oname, const string_t& nname ) {
        if( oname.empty() || nname.empty() ){ return -1; }
        return rename_file( oname, nname );
    }

    /*─······································································─*/

    inline int remove_file( const string_t& path ){
        if( path.empty() ){ return -1; }
        return remove( path.c_str() );
    }

    /*─······································································─*/

    inline int create_file( const string_t& path ){
        if( path.empty() ){ return -1; }
        file_t( path,"w+"); return  1;
    }

    /*─······································································─*/

    inline ulong file_size( const string_t& path ){
        if( exists_file( path ) ){
            return file_t( path, "r" ).size();
        }   return 0;
    }

    /*─······································································─*/

    inline bool is_file( const string_t& path ){ return exists_file(path); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/