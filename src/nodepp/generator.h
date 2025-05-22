/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#define NODEPP_GENERATOR

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER) && defined(NODEPP_GENERATOR)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    GENERATOR( timer ){ public:

        template< class V, class... T > 
        coEmit( V func, ulong time, const T&... args ){
        gnStart
            coDelay( time ); if( func(args...)<0 )
                   { coEnd; } coGoto(0); 
        gnStop
        }

        template< class V, class... T > 
        coEmit( V func, ulong* time, const T&... args ){
        gnStart
            coDelay( *time ); if( func(args...)<0 )
                   { coEnd; } coGoto(0); 
        gnStop
        }

    };
    
    /*─······································································─*/

    GENERATOR( utimer ){ public:

        template< class V, class... T > 
        coEmit( V func, ulong time, const T&... args ){
        gnStart
            coUDelay( time ); if( func(args...)<0 )
                    { coEnd; } coGoto(0);
        gnStop
        }

        template< class V, class... T > 
        coEmit( V func, ulong* time, const T&... args ){
        gnStart
            coUDelay( *time ); if( func(args...)<0 )
                    { coEnd; } coGoto(0);
        gnStop
        }

    };

}}  
#undef NODEPP_GENERATOR
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_PROMISE) && defined(NODE_PROMISE) && defined(NODEPP_GENERATOR)
    #define  GENERATOR_PROMISE
namespace nodepp { namespace _promise_ {

    GENERATOR( resolve ){ public:

        template< class T, class U, class V > 
        coEmit( ptr_t<bool> state, const T& func, const U& res, const V& rej ){
        gnStart
            func( res, rej ); coWait( *state==1 );
        gnStop
        }

        template< class T, class U > 
        coEmit( ptr_t<bool> state, const T& func, const U& res ){
        gnStart
            func( res ); coWait( *state==1 );
        gnStop
        }

    };

}}  
#undef NODEPP_GENERATOR
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_FILE) && defined(NODEPP_FILE) && defined(NODEPP_GENERATOR)
    #define  GENERATOR_FILE
namespace nodepp { namespace _file_ {

    GENERATOR( read ){ 
    private:  
        ulong    d; 
        ulong*   r; 
        
    public: 
        string_t data ;
        int      state; 

    template< class T > coEmit( T* str, ulong size=CHUNK_SIZE ){
        if( str->is_closed() ){ return -1; }
    gnStart state=0; d=0; data.clear(); str->flush();

        if(!str->is_available() ){ coEnd; } r = str->get_range();
        if(!str->get_borrow().empty() ){ data = str->get_borrow(); }

          if ( r[1] != 0  ){ auto pos = str->pos(); d = r[1]-r[0];
          if ( pos < r[0] ){ str->del_borrow(); str->pos( r[0] ); }
        elif ( pos >=r[1] ){ coEnd; } }
        else { d = str->get_buffer_size(); }

        if( data.empty() ) do { coNext;
            state=str->_read( str->get_buffer_data(), min(d,size) );
        } while ( state==-2 );
        
        if( state > 0 ){
            data  = string_t( str->get_buffer_data(), (ulong) state );
        }   state = min( data.size(), size ); str->del_borrow();

        str->set_borrow( data.splice( size, data.size() ) );
        
    gnStop
    }};
    
    /*─······································································─*/

    GENERATOR( write ){ 
    private:
        string_t b ;

    public:
        ulong    data ; 
        int      state;
        
    template< class T > coEmit( T* str, const string_t& msg ){
        if( str->is_closed() ){ return -1; }
    gnStart state=0; data=0; str->flush();

        if(!str->is_available() || msg.empty() ){ coEnd; }
        if( b.empty() ){ b = msg; }
        
        do { /*coNext;*/ do { coNext;
             state=str->_write( b.data()+data, b.size()-data );
        } while ( state==-2 ); if( state>0 ){ data += state; }
        } while ( state>=0 && data<b.size() ); b.clear();

    gnStop
    }};

    /*─······································································─*/

    GENERATOR( until ){ 
    private:
        _file_::read _read;
        uint sop=0, pos=0;
        string_t    s;

    public: 
        string_t  data ;  
        ulong     state; 

    template< class T > coEmit( T* str, string_t ch ){
        if( str->is_closed() ){ return -1; }
    gnStart s.clear(); data.clear(); str->flush();
            state=0; sop=0; pos=0;

        while( str->is_available() ){
        while( _read(str) == 1 ){ coNext;}
           if( _read.state<= 0 ){ break; } state=0; s+=_read.data;
        while( state < s.size() ){ auto x=s[ state ];
           if( pos>=ch.size() ) { pos=0; break; }
         elif( ch[pos] == x )   { pos++; }
         else                   { pos=0; sop++; state=sop; continue; } state++; }
           if( state<=s.size() ){ break; } sop = state + 1;
        }      str->set_borrow(s); state -= pos;

        ptr_t<int> results ({
            memcmp( str->get_borrow().slice(state-ch.size()).get(), ch.get(), ch.size() ),
            memcmp( str->get_borrow().get(), ch.get(), ch.size() )
        });

        if( results[1]==0 ){
                 data = str->get_borrow().splice( 0, ch.size() );
        } elif( results[0]==0 ){
                 data = str->get_borrow().splice( 0, state-ch.size() );
        } else { data = str->get_borrow().splice( 0, state ); }

        state = data.size();
    
    gnStop
    }

    template< class T > coEmit( T* str, char ch ){
        if( str->is_closed() ){ return -1; }
    gnStart state=1; s.clear(); data.clear(); str->flush();

        while( str->is_available() ){
        while( _read(str) == 1 ){ coNext; }
           if( _read.state<= 0 ){ break; } state = 1; s += _read.data; 
          for( auto &x: s )     { if( x == ch ){ break; } state++; }
           if( state<=s.size() ){ break; }
        }      str->set_borrow(s);

        data = str->get_borrow().splice( 0, state );
    
    gnStop
    }};

    /*─······································································─*/

    GENERATOR( line ){ 
    private:
        _file_::read _read;
        string_t     s;

    public: 
        string_t  data ;  
        ulong     state; 

    template< class T > coEmit( T* str ){
        if( str->is_closed() ){ return -1; }
    gnStart state=1; s.clear(); data.clear(); str->flush();

        while( str->is_available() ){
        while( _read(str) == 1 ){ coNext; }
           if( _read.state<= 0 ){ break; } state = 1; s += _read.data; 
          for( auto &x: s )     { if( x == '\n' ){ break; } state++; }
           if( state<=s.size() ){ break; }
        }      str->set_borrow(s);

        data = str->get_borrow().splice( 0, state );
    
    gnStop
    }};

}}
#undef NODEPP_GENERATOR
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_STREAM) && defined(NODEPP_STREAM) && defined(NODEPP_GENERATOR)
    #define  GENERATOR_STREAM 
namespace nodepp { namespace _stream_ {

    GENERATOR( duplex ){ 
    private:

        _file_::write _write1, _write2;
        _file_::read  _read1 , _read2;

    public:

        template< class T, class V > coEmit( const T& inp, const V& out ){
            if( inp.is_closed() || out.is_closed() ){ return -1; }
        gnStart inp.onPipe.emit(); out.onPipe.emit(); coYield(1);

            while( inp.is_available() && out.is_available() ){
            while( _read1(&inp) ==1 )            { coGoto(2); }
               if( _read1.state <=0 )            { break;  }
            while( _write1(&out,_read1.data)==1 ){ coNext; }
               if( _write1.state<=0 )            { break;  }
                    inp.onData.emit( _read1.data );
            }       inp.close(); out.close();
            
            coEnd; coYield(2);

            while( inp.is_available() && out.is_available() ){
            while( _read2(&out) ==1 )            { coGoto(1); }
               if( _read2.state <=0 )            { break;  }
            while( _write2(&inp,_read2.data)==1 ){ coNext; }
               if( _write2.state<=0 )            { break;  }
                    out.onData.emit( _read2.data );
            }       out.close(); inp.close();

        gnStop
        }

    };
    
    /*─······································································─*/

    GENERATOR( pipe ){ 
    private:

        _file_::write _write;
        _file_::read  _read;

    public:

        template< class T > coEmit( const T& inp ){
            if( inp.is_closed() ){ return -1; }
        gnStart inp.onPipe.emit();
            while( inp.is_available() ){
            while( _read(&inp)==1 ){ coNext; }
               if( _read.state<=0 ){ break;  }
                    inp.onData.emit( _read.data );
            }       inp.close(); 
        gnStop
        }

        template< class T, class V > coEmit( const T& inp, const V& out ){
            if( inp.is_closed() || out.is_closed() ){ return -1; }
        gnStart inp.onPipe.emit(); out.onPipe.emit();
            while( inp.is_available() && out.is_available() ){
            while( _read(&inp) ==1 )           { coNext; }
               if( _read.state <=0 )           { break;  }
            while( _write(&out,_read.data)==1 ){ coNext; }
               if( _write.state<=0 )           { break;  }
                    inp.onData.emit( _read.data );
            }       inp.close(); out.close();
        gnStop
        }

    };
    
    /*─······································································─*/

    GENERATOR( until ){ 
    private:

        _file_::write _write;
        _file_::until  _read;

    public:

        template< class T, class U > 
        coEmit( const T& inp, const U& val ){
            if( inp.is_closed() ){ return -1; }
        gnStart inp.onPipe.emit();
            while( inp.is_available() ){
            while( _read(&inp,val)==1 ){ coNext; } 
               if( _read.state    <=0 ){ break;  }
                   inp.onData.emit( _read.data );
            }      inp.close(); 
        gnStop
        }

        template< class T, class V, class U > 
        coEmit( const T& inp, const V& out, const U& val ){
            if( inp.is_closed() || out.is_closed() ){ return -1; }
        gnStart inp.onPipe.emit(); out.onPipe.emit();
            while( inp.is_available() && out.is_available() ){
            while( _read(&inp,val)==1 )        { coNext; } 
               if( _read.state    <=0 )        { break;  }
            while( _write(&out,_read.data)==1 ){ coNext; }
               if( _write.state<=0 )           { break;  }
                    inp.onData.emit( _read.data );
            }       inp.close(); out.close();
        gnStop
        }

    };
    
    /*─······································································─*/

    GENERATOR( line ){ 
    private:

        _file_::write _write;
        _file_::line  _read;

    public:

        template< class T > coEmit( const T& inp ){
            if( inp.is_closed() ){ return -1; }
        gnStart inp.onPipe.emit();
            while( inp.is_available() ){
            while( _read(&inp)==1 ){ coNext; } 
               if( _read.state<=0 ){ break;  }
                   inp.onData.emit( _read.data );
            }      inp.close(); 
        gnStop
        }

        template< class T, class V > coEmit( const T& inp, const V& out ){
            if( inp.is_closed() || out.is_closed() ){ return -1; }
        gnStart inp.onPipe.emit(); out.onPipe.emit();
            while( inp.is_available() && out.is_available() ){
            while( _read(&inp)==1 )            { coNext; } 
               if( _read.state<=0 )            { break;  }
            while( _write(&out,_read.data)==1 ){ coNext; }
               if( _write.state<=0 )           { break;  }
                    inp.onData.emit( _read.data );
            }       inp.close(); out.close();
        gnStop
        }

    };
    
}}
#undef NODEPP_GENERATOR
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_POLL) && defined(NODEPP_SOCKET) && defined(NODEPP_GENERATOR)
    #define  GENERATOR_POLL
namespace nodepp { namespace _poll_ {

    GENERATOR( poll ){ public:

        template< class V, class T, class U > 
        coEmit( V ctx, T str, U cb ){
            if( ctx.is_closed() ){ return -1; }
        gnStart coNext;
            str->onSocket.emit( ctx ); cb(ctx);
        gnStop
        }

    };

}}  
#undef NODEPP_GENERATOR
#endif
