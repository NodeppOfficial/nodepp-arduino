/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_SERIAL
#define NODEPP_SERIAL

/*────────────────────────────────────────────────────────────────────────────*/

#include "event.h"
#include "generator.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class serial_t {
protected:

    void kill() const noexcept { 
        obj->state |= FILE_STATE::KILL;
        Serial.end(); 
    }

    bool is_state( uchar value ) const noexcept {
        if( obj->state & value ){ return true; }
    return false; }

    void set_state( uchar value ) const noexcept {
    if( obj->state & KILL ){ return; }
        obj->state = value;
    }

    enum FILE_STATE {
        UNKNOWN = 0b00000000,
        OPEN    = 0b00000001,
        CLOSE   = 0b00000010,
        KILL    = 0b00000100,
        REUSE   = 0b00001000,
        DISABLE = 0b00001110
    };

protected:

    struct NODE {
        uchar        state    = FILE_STATE::OPEN;
        ulong        range[2] = { 0, 0 };
        int          feof     = 1;
        ptr_t<char>  buffer;
        string_t     borrow;
    };  ptr_t<NODE> obj;

public:

    event_t<>          onUnpipe;
    event_t<>          onResume;
    event_t<except_t>  onError;
    event_t<>          onDrain;
    event_t<>          onClose;
    event_t<>          onOpen;
    event_t<>          onPipe;
    event_t<string_t>  onData;

    /*─······································································─*/

    virtual ~serial_t() noexcept { if( obj.count()>1 ){ return; } free(); }

    /*─······································································─*/

    serial_t( const uchar& port, const ulong& _size=CHUNK_SIZE ) : obj( new NODE() ) {
        Serial.begin( port ); set_buffer_size( _size );
    }
    
    serial_t( const ulong& _size=CHUNK_SIZE ) noexcept : obj( new NODE() ) { 
        set_buffer_size( _size ); 
    }

    /*─······································································─*/

    bool     is_closed() const noexcept { return is_state(FILE_STATE::DISABLE) || is_feof(); }
    bool       is_feof() const noexcept { return obj->feof <= 0 && obj->feof != -2; }
    bool  is_available() const noexcept { return !is_closed(); }

    /*─······································································─*/

    void  resume() const noexcept { if(is_state(FILE_STATE::OPEN )){ return; } set_state(FILE_STATE::OPEN ); onResume.emit(); }
    void    stop() const noexcept { if(is_state(FILE_STATE::REUSE)){ return; } set_state(FILE_STATE::REUSE); onDrain .emit(); }
    void   reset() const noexcept { if(is_state(FILE_STATE::KILL )){ return; } resume(); pos(0); }
    void   flush() const noexcept { obj->buffer.fill(0); }

    /*─······································································─*/

    void close() const noexcept {
        if( is_state (FILE_STATE::DISABLE) ){ return; }
            set_state( FILE_STATE::CLOSE ); DONE:;
    onDrain.emit(); free(); }

    /*─······································································─*/

    void   set_range( ulong /*unused*/, ulong /*unused*/ ) const noexcept { }
    ulong* get_range() const noexcept { return nullptr; }
    int       get_fd() const noexcept { return 1; }

    /*─······································································─*/

    void   set_borrow( const string_t& brr ) const noexcept { obj->borrow = brr; }
    ulong  get_borrow_size() const noexcept { return obj->borrow.size(); }
    char*  get_borrow_data() const noexcept { return obj->borrow.data(); }
    void        del_borrow() const noexcept { obj->borrow.clear(); }
    string_t&   get_borrow() const noexcept { return obj->borrow; }

    /*─······································································─*/

    ulong   get_buffer_size() const noexcept { return obj->buffer.size(); }
    char*   get_buffer_data() const noexcept { return obj->buffer.data(); }
    ptr_t<char>& get_buffer() const noexcept { return obj->buffer; }

    /*─······································································─*/

    ulong size() const noexcept { return -1; }

    /*─······································································─*/

    virtual ulong set_buffer_size( ulong _size ) const noexcept {
        obj->buffer = ptr_t<char>( _size ); return _size;
    }

    /*─······································································─*/

    virtual void free() const noexcept {
        
        if( is_state( FILE_STATE::REUSE ) && obj.count()>1 ){ resume(); return; }
        if( is_state( FILE_STATE::KILL  ) ){ return; }
        if(!is_state( FILE_STATE::CLOSE ) ){ kill(); onDrain.emit(); } else { kill(); }
       
        onUnpipe.clear(); onResume.clear();
        onError .clear(); onData  .clear();
        onOpen  .clear(); onPipe  .clear(); onClose.emit();
        
    }

    /*─······································································─*/

    ulong pos( ulong _pos ) const noexcept { return 0; }
    ulong pos() const noexcept { return 0; }

    /*─······································································─*/

    char read_char() const noexcept { return read(1)[0]; }

    string_t read_until( string_t ch ) const noexcept {
        auto gen = generator::file::until();
        while( gen( this, ch ) == 1 )
             { process::next(); }
        return gen.data;
    }

    string_t read_until( char ch ) const noexcept {
        auto gen = generator::file::until();
        while( gen( this, ch ) == 1 )
             { process::next(); }
        return gen.data;
    }

    string_t read_line() const noexcept {
        auto gen = generator::file::line();
        while( gen( this ) == 1 )
             { process::next(); }
        return gen.data;
    }

    /*─······································································─*/

    string_t read( ulong size=CHUNK_SIZE ) const noexcept {
        auto gen = generator::file::read();
        while( gen( this, size ) == 1 )
             { process::next(); }
        return gen.data;
    }

    ulong write( const string_t& msg ) const noexcept {
        auto gen = generator::file::write();
        while( gen( this, msg ) == 1 )
             { process::next(); }
        return gen.data;
    }

    /*─······································································─*/

    virtual int _read ( char* bf, const ulong& sx ) const noexcept { return __read ( bf, sx ); }
    virtual int _write( char* bf, const ulong& sx ) const noexcept { return __write( bf, sx ); }

    /*─······································································─*/

    virtual int __read( char* bf, const ulong& sx ) const noexcept {
        if( is_closed() ){ return -1; } if( sx==0 ){ return 0; }
        if(!Serial.available() ){ return -2; } 

        char x = 0; obj->feof = 0;

        do { x = Serial.read();
        if ( sx==obj->feof ){ break; }
        if ( x == -1 )      { break; }
             bf[obj->feof] = x;
             obj->feof++;
        } while( true );

        Serial.flush(); return obj->feof;
    }

    virtual int __write( char* bf, const ulong& sx ) const noexcept {
        if( is_closed() ){ return -1; } if( sx==0 ){ return 0; }
        if(!Serial.availableForWrite() ){ return -2; }
        obj->feof= Serial.write( bf, sx );
        Serial.flush(); return obj->feof;
    }

    /*─······································································─*/

    bool _write_( char* bf, const ulong& sx, ulong& sy ) const noexcept {
        if( sx==0 || is_closed() ){ return 1; } while( sy < sx ) {
            int c = __write( bf+sy, sx-sy );
            if( c <= 0 && c != -2 )          { return 0; }
            if( c >  0 ){ sy += c; continue; } return 1;
        }   return 0;
    }

    bool _read_( char* bf, const ulong& sx, ulong& sy ) const noexcept {
        if( sx==0 || is_closed() ){ return 1; } while( sy < sx ) {
            int c = __read( bf+sy, sx-sy );
            if( c <= 0 && c != -2 )          { return 0; }
            if( c >  0 ){ sy += c; continue; } return 1;
        }   return 0;
    }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif