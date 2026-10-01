/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_ARDUINO_STREAM
#define NODEPP_ARDUINO_STREAM

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { template< class T > class stream_t {
protected:

    void kill() const noexcept { 
        obj->state |= STATE::FS_STATE_KILL; 
    }

    bool is_state( uchar_16 value ) const noexcept {
        if( obj->state & value ){ return true; }
    return false; }

    void set_state( uchar_16 value ) const noexcept {
    if( obj->state & STATE::FS_STATE_KILL ){ return; }
        obj->state = value;
    }

    enum STATE : uchar_16 {
         FS_STATE_UNKNOWN = 0b000000000,
         FS_STATE_OPEN    = 0b000000001,
         FS_STATE_REUSE   = 0b001000000,
         FS_STATE_CLOSE   = 0b000000010,
         FS_STATE_READING = 0b000010000,
         FS_STATE_WRITING = 0b000100000,
         FS_STATE_WAITING = 0b010000000,
         FS_STATE_KILL    = 0b000000100,
         FS_STATE_STOP    = 0b000001000,
         FS_STATE_DISABLE = 0b000001110,
         FS_STATE_SERVER  = 0b100000000
    };

protected:

    struct NODE {

        uchar_16 state = STATE::FS_STATE_CLOSE;
        uchar_64 tag   = 0UL; T fd, pd = 0UL;
        len_t range[2] = { 0, 0 };
        ptr_t<char> buffer; string_t borrow;

        ulong timeout = 0UL;

        generator::file::until _until;
        generator::file::line  _line ;
        generator::file::read  _read ;
        generator::file::write _write;

       ~NODE(){ fd.end(); }
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

   ~stream_t() noexcept { if( obj.count()>1 && !is_closed() ){ return; } free(); }
    
    stream_t( const T& fd, const ulong& _size=NODEPP_CHUNK_SIZE ) noexcept : obj( new NODE() ) { 
        obj->fd    = fd; set_buffer_size( _size ); 
        obj->state = STATE::FS_STATE_OPEN;
    }

    stream_t() noexcept : obj( new NODE() ){}

    /*─······································································─*/

    ulong set_timeout( ulong time ) const noexcept {
        if( time == 0 ){ obj->timeout = 0; return 0; }
        obj->timeout = process::millis() + time; 
        return time;
    }

    ulong get_timeout() const noexcept {
        return obj->timeout==0 ? process::millis() : obj->timeout;
    }

    /*─······································································─*/

    void  resume() const noexcept { if(!is_state(STATE::FS_STATE_STOP )){ return; } onResume .emit(); obj->state &=~ STATE::FS_STATE_STOP; }
    void    stop() const noexcept { if( is_state(STATE::FS_STATE_STOP )){ return; } onDrain  .emit(); obj->state |=  STATE::FS_STATE_STOP; }
    void   reset() const noexcept { if( is_state(STATE::FS_STATE_KILL )){ return; } resume(); pos(0); }
    void   flush() const noexcept { obj->buffer.fill(0); }

    /*─······································································─*/

    bool    is_closed() const noexcept { return is_state(STATE::FS_STATE_DISABLE); }
    bool  is_reusable() const noexcept { return is_state(STATE::FS_STATE_REUSE  ); }
    bool   is_stopped() const noexcept { return is_state(STATE::FS_STATE_STOP   ); }
    bool   is_waiting() const noexcept { return is_state(STATE::FS_STATE_WAITING); }
    bool is_available() const noexcept { return !is_closed(); }

    /*─······································································─*/

    void close() const noexcept {
        if( is_state ( STATE::FS_STATE_DISABLE )){ return; } onDrain.emit(); 
        if( is_state ( STATE::FS_STATE_REUSE   )){ return; }
            set_state( STATE::FS_STATE_CLOSE   );
    free(); }

    /*─······································································─*/

    void   set_range( len_t x, len_t y ) const noexcept { obj->range[0] = x; obj->range[1] = y; }
    len_t* get_range() /*-------------*/ const noexcept { return obj->range; }

    /*─······································································─*/

    void set_reusable( bool mode ) const noexcept { 
    switch( (int) mode ){
        case 1 : obj->state |=  STATE::FS_STATE_REUSE; break;
        default: obj->state &=~ STATE::FS_STATE_REUSE; break;
    }}

    /*─······································································─*/

    T&        get_fd() const noexcept { return &obj->fd; }
    uchar_64&    tag() const noexcept { return obj->tag; }
    uchar_64& get_pd() const noexcept { return obj->pd ; }

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

    ulong set_buffer_size( ulong _size ) const noexcept {
        obj->buffer = ptr_t<char>( _size ); return _size;
    }

    /*─······································································─*/

    void free() const noexcept {

        if( is_state( STATE::FS_STATE_STOP  ) && obj.count()>1 ){ return; }
        if( is_state( STATE::FS_STATE_KILL  ) ){ return; } kill();
        if(!is_state( STATE::FS_STATE_CLOSE | STATE::FS_STATE_STOP ) )
          { onDrain.emit(); }

        onClose .emit (); onDrain .clear();

        onUnpipe.clear(); onResume.clear();
        onError .clear(); onData  .clear();
        onOpen  .clear(); /*-------------*/
        onPipe  .clear(); onClose .clear();

    }

    /*─······································································─*/

    virtual len_t pos( len_t _pos ) const noexcept { return 0; }

    virtual len_t size() /*------*/ const noexcept { return 0; }
    
    virtual len_t pos() /*-------*/ const noexcept { return 0; }

    /*─······································································─*/

    char read_char() const noexcept { return read(1)[0]; }

    string_t read_until( string_t ch ) const noexcept {
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

    string_t read( ulong size=NODEPP_CHUNK_SIZE ) const noexcept {
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
        if( process::millis() > get_timeout() || is_closed() )
          { return -1; } if ( sx==0 ) { return 0; }
        
        if(!obj->fd.available() ){ 
            obj->state |= STATE::FS_STATE_WAITING; return -2; 
        }   obj->state &=~STATE::FS_STATE_WAITING;

        char x = 0; ulong y = 0;

        do { x = obj->fd.read();
        if ( sx== y || x ==-1 ){ break; }
             bf[y] = x; y++;
        } while( true );

        obj->fd.flush(); return (int) y;
    }

    virtual int __write( char* bf, const ulong& sx ) const noexcept {
        if( process::millis() > get_timeout() || is_closed() )
          { return -1; } if ( sx==0 ) { return 0; }

        if(!obj->fd.availableForWrite() ){ 
            obj->state |= STATE::FS_STATE_WAITING; return -2; 
        }   obj->state &=~STATE::FS_STATE_WAITING;

        auto c = obj->fd.write( bf, sx );
        obj->fd.flush(); return c;

    }

    /*─······································································─*/

    int _write_( char* bf, const ulong& sx, ulong* sy ) const noexcept {
    if( sx==0 || is_closed() ){ return -1; } while( *sy<sx ) {
        int c = __write( bf + *sy, sx - *sy );
        if( c==-2 ) /*--*/ { return -2; }
        if( c > 0 ){ *sy+= c; continue; } 
    break; } return *sy; }

    int _read_( char* bf, const ulong& sx, ulong* sy ) const noexcept {
    if( sx==0 || is_closed() ){ return -1; } while( *sy<sx ) {
        int c = __read( bf + *sy, sx - *sy );
        if( c==-2 ) /*--*/ { return -2; }
        if( c > 0 ){ *sy+= c; continue; } 
    break; } return *sy; }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/