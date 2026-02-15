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
        obj->state |= STATE::FS_STATE_KILL;
        Serial.end(); 
    }

    bool is_state( uchar value ) const noexcept {
        if( obj->state & value ){ return true; }
    return false; }

    void set_state( uchar value ) const noexcept {
    if( obj->state & STATE::FS_STATE_KILL ){ return; }
        obj->state = value;
    }

    enum STATE {
         FS_STATE_UNKNOWN = 0b00000000,
         FS_STATE_OPEN    = 0b00000001,
         FS_STATE_CLOSE   = 0b00000010,
         FS_STATE_READING = 0b00010000,
         FS_STATE_WRITING = 0b00100000,
         FS_STATE_KILL    = 0b00000100,
         FS_STATE_REUSE   = 0b00001000,
         FS_STATE_DISABLE = 0b00001110
    };

protected:

    struct NODE {

        ulong       range[2] = { 0, 0 };
        int         feof     = 1;
        uchar       state    = STATE::FS_STATE_OPEN;

        ptr_t<char> buffer; string_t borrow;
        generator::file::until _until;
        generator::file::line  _line ;
        generator::file::read  _read ;
        generator::file::write _write;
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

    serial_t( const uchar& port, const ulong& _size=CHUNK_SIZE ) noexcept : obj( new NODE() ) {
        Serial.begin( port ); set_buffer_size( _size );
    }

   ~serial_t() noexcept { if( obj.count()>1 && !is_closed() ){ return; } free(); }
    
    serial_t( const ulong& _size=CHUNK_SIZE ) noexcept : obj( new NODE() ) { 
        set_buffer_size( _size ); 
    }

    /*─······································································─*/

    bool     is_closed() const noexcept { return is_state(STATE::FS_STATE_DISABLE) || is_feof(); }
    bool       is_feof() const noexcept { return obj->feof <= 0 && obj->feof != -2; }
    bool    is_waiting() const noexcept { return obj->feof == -2; }
    bool  is_available() const noexcept { return !is_closed(); }

    /*─······································································─*/

    void  resume() const noexcept { if(is_state(STATE::FS_STATE_OPEN )){ return; } set_state(STATE::FS_STATE_OPEN ); onResume.emit(); }
    void    stop() const noexcept { if(is_state(STATE::FS_STATE_REUSE)){ return; } set_state(STATE::FS_STATE_REUSE); onDrain .emit(); }
    void   reset() const noexcept { if(is_state(STATE::FS_STATE_KILL )){ return; } resume(); pos(0); }
    void   flush() const noexcept { obj->buffer.fill(0); }

    /*─······································································─*/

    void close() const noexcept {
        if( is_state ( STATE::FS_STATE_DISABLE ) ){ return; }
            set_state( STATE::FS_STATE_CLOSE   );
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

    ulong set_buffer_size( ulong _size ) const noexcept {
        obj->buffer = ptr_t<char>( _size ); return _size;
    }

    /*─······································································─*/

    void free() const noexcept {

        if( is_state( STATE::FS_STATE_REUSE ) && !is_feof() && obj.count()>1 ){ return; }
        if( is_state( STATE::FS_STATE_KILL  ) ) /*-------*/ { return; } 
        if(!is_state( STATE::FS_STATE_CLOSE | STATE::FS_STATE_REUSE ) )
          { kill(); onDrain.emit(); } else { kill(); }
       
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
        while( obj->_until( this, ch ) == 1 )
             { process::next(); }
        return obj->_until.data;
    }

    string_t read_until( char ch ) const noexcept {
        while( obj->_until( this, ch ) == 1 )
             { process::next(); }
        return obj->_until.data;
    }

    string_t read_line() const noexcept {
        while( obj->_line( this ) == 1 )
             { process::next(); }
        return obj->_line.data;
    }

    /*─······································································─*/

    string_t read( ulong size=CHUNK_SIZE ) const noexcept {
        while( obj->_read( this, size ) == 1 )
             { process::next(); }
        return obj->_read.data;
    }

    ulong write( const string_t& msg ) const noexcept {
        while( obj->_write( this, msg ) == 1 )
             { process::next(); }
        return obj->_write.data;
    }

    /*─······································································─*/

    virtual int _read ( char* bf, const ulong& sx ) const noexcept { return __read ( bf, sx ); }
    virtual int _write( char* bf, const ulong& sx ) const noexcept { return __write( bf, sx ); }

    /*─······································································─*/

    virtual int __read( char* bf, const ulong& sx ) const noexcept {
        if( is_closed() ){ return -1; } if( sx==0 ){ return 0; }
        if(!Serial.available() ){ obj->feof=-2; return -2; }

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
        if( is_closed() ){ return -1; } if( sx==0 )/**/{ return 0; }
        if(!Serial.availableForWrite() ){ obj->feof=-2; return -2; }
        obj->feof= Serial.write( bf, sx );
        Serial.flush(); return obj->feof;
    }

    /*─······································································─*/

    int _write_( char* bf, const ulong& sx, ulong* sy ) const noexcept {
        if( sx==0 || is_closed() ){ return -1; } while( *sy<sx ) {
            int c = __write( bf + *sy, sx - *sy );
            if( c <= 0 && c != -2 ) /*----*/ { return -2; }
            if( c >  0 ){ *sy+= c; continue; } break/**/;
        }   return sx;
    }

    int _read_( char* bf, const ulong& sx, ulong* sy ) const noexcept {
        if( sx==0 || is_closed() ){ return -1; } while( *sy<sx ) {
            int c = __read( bf + *sy, sx - *sy );
            if( c <= 0 && c != -2 ) /*----*/ { return -2; }
            if( c >  0 ){ *sy+= c; continue; } break/**/;
        }   return sx;
    }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif