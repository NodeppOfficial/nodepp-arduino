/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_PATH
#define NODEPP_PATH

/*────────────────────────────────────────────────────────────────────────────*/

#if false // _KERNEL_ == NODEPP_KERNEL_WINDOWS

#define PATH_SEP  MEMSTR( "\\\\" )
#define PATH_ROOT MEMSTR( "c:\\\\" )
#define PATH_ONE  MEMSTR( "[^\\\\]+" )
#define PATH_SEL  MEMSTR( "/+|\\\\+" )
#define PATH_BEG  MEMSTR( "\\w:\\\\" )
#define PATH_PEG  MEMSTR( "^\\w:\\\\" )

#else

#define PATH_SEP  MEMSTR( "/" )
#define PATH_ROOT MEMSTR( "./" )
#define PATH_ONE  MEMSTR( "[^/]+" )
#define PATH_BEG  MEMSTR( "/" )
#define PATH_PEG  MEMSTR( "^/" )
#define PATH_SEL  MEMSTR( "/+|\\\\+" ) 

#endif

/*────────────────────────────────────────────────────────────────────────────*/

#include "regex.h"
#include "map.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { struct path_t {
    string_t type;
    string_t path;
    string_t root;
    string_t base;
    string_t name;
    string_t dir;
    string_t ext;
};}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace _path_ { 
inline map_t<string_t,string_t>& mimetype() {
static map_t<string_t,string_t>  out ({

    { MEMSTR( "txt" ) , MEMSTR( "text/plain" ) },
    { MEMSTR( "text" ), MEMSTR( "text/plain" ) },

    { MEMSTR( "otf" ),  MEMSTR( "font/otf" ) },
    { MEMSTR( "ttf" ),  MEMSTR( "font/ttf" ) },
    { MEMSTR( "woff" ), MEMSTR( "font/woff" )  },
    { MEMSTR( "woff2" ),MEMSTR( "font/woff2" ) },

    { MEMSTR( "oga" ),  MEMSTR( "audio/ogg" ) },
    { MEMSTR( "aac" ),  MEMSTR( "audio/aac" ) },
    { MEMSTR( "wav" ),  MEMSTR( "audio/wav" ) },
    { MEMSTR( "mp3" ),  MEMSTR( "audio/mpeg" ) },
    { MEMSTR( "opus" ), MEMSTR( "audio/opus" ) },
    { MEMSTR( "weba" ), MEMSTR( "audio/webm" ) },

    { MEMSTR( "ogv" ),  MEMSTR( "video/ogg" ) },
    { MEMSTR( "mp4" ),  MEMSTR( "video/mp4" ) },
    { MEMSTR( "ts" ),   MEMSTR( "video/mp2t" ) },
    { MEMSTR( "webm" ), MEMSTR( "video/webm" ) },
    { MEMSTR( "mpeg" ), MEMSTR( "video/mpeg" ) },
    { MEMSTR( "avi" ),  MEMSTR( "video/x-msvideo" ) },

    { MEMSTR( "c" ),    MEMSTR( "text/X-C" ) },
    { MEMSTR( "css" ),  MEMSTR( "text/css" ) },
    { MEMSTR( "csv" ),  MEMSTR( "text/csv" ) },
    { MEMSTR( "html" ), MEMSTR( "text/html" ) },
    { MEMSTR( "scss" ), MEMSTR( "text/scss" ) },
    { MEMSTR( "cpp" ),  MEMSTR( "text/X-CPP" ) },
    { MEMSTR( "ics" ),  MEMSTR( "text/calendar" ) },
    { MEMSTR( "js" ),   MEMSTR( "text/javascript" ) },
    { MEMSTR( "xml" ),  MEMSTR( "application/xhtml+xml" ) },

    { MEMSTR( "bmp" ),  MEMSTR( "image/bmp" ) },
    { MEMSTR( "gif" ),  MEMSTR( "image/gif" ) },
    { MEMSTR( "png" ),  MEMSTR( "image/png" ) },
    { MEMSTR( "jpg" ),  MEMSTR( "image/jpeg" ) },
    { MEMSTR( "jpeg" ), MEMSTR( "image/jpeg" ) },
    { MEMSTR( "webp" ), MEMSTR( "image/webp" ) },
    { MEMSTR( "svg" ),  MEMSTR( "image/svg+xml" ) },
    { MEMSTR( "ico" ),  MEMSTR( "image/vnd.microsoft.icon" ) },

    { MEMSTR( "url" ),  MEMSTR( "application/x-www-form-urlencoded" ) },

    { MEMSTR( "zip" ),  MEMSTR( "application/zip" ) },
    { MEMSTR( "gz" ),   MEMSTR( "application/gzip" ) },
    { MEMSTR( ".h" ),   MEMSTR( "application/x-.h" ) },
    { MEMSTR( "json" ), MEMSTR( "application/json" ) },
    { MEMSTR( "wasm" ), MEMSTR( "application/wasm" ) },
    { MEMSTR( "tar" ),  MEMSTR( "application/x-tar" ) },
    { MEMSTR( "rar" ),  MEMSTR( "application/vnd.rar" ) },
    { MEMSTR( "7z" ),   MEMSTR( "application/x-7z-compressed" ) },
    { MEMSTR( "m3u8" ), MEMSTR( "application/vnd.apple.mpegurl" ) },
    { MEMSTR( "exe" ),  MEMSTR( "application/vnd.microsoft.portable-executable" ) },

    { MEMSTR( "pdf" ),  MEMSTR( "application/pdf" ) },
    { MEMSTR( "doc" ),  MEMSTR( "application/msword" ) },
    { MEMSTR( "vsd" ),  MEMSTR( "application/vnd.visio" ) },
    { MEMSTR( "xls" ),  MEMSTR( "application/vnd.ms-excel" ) },
    { MEMSTR( "ppt" ),  MEMSTR( "application/vnd.ms-powerpoint" ) },
    { MEMSTR( "swf" ),  MEMSTR( "application/x-shockwave-fla.h" ) },
    { MEMSTR( "ods" ),  MEMSTR( "application/vnd.oasis.opendocument.spreadsheet" ) },
    { MEMSTR( "odp" ),  MEMSTR( "application/vnd.oasis.opendocument.presentation" ) },
    { MEMSTR( "odt" ),  MEMSTR( "application/vnd.oasis.opendocument.presentation" ) },
    { MEMSTR( "xlsx" ), MEMSTR( "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" ) },
    { MEMSTR( "docx" ), MEMSTR( "application/vnd.openxmlformats-officedocument.wordprocessingml.document" ) },
    { MEMSTR( "pptx" ), MEMSTR( "application/vnd.openxmlformats-officedocument.presentationml.presentation" ) }

}); return out; }}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace path {

    inline string_t normalize( string_t path ){
        static regex_t reg0 = regex_t( PATH_SEL );
        auto sec = reg0.split( path );
        queue_t<string_t> nsec; ulong y=0;

        for ( ulong x=0; x<sec.size(); ++x ){
         if ( sec[x] == ".." ){
              nsec.push( sec[x] );
              ++y; continue;
            } break;
        }

        for ( ulong x=y; x<sec.size(); ++x ){
         if ( sec[x] == ".." && !nsec.empty() ){
              nsec.pop(); continue;
            } nsec.push( sec[x] );
        }

        return array_t<string_t>( nsec.data() ).join( PATH_SEP );
    }

    /*─······································································─*/

    inline bool is_absolute( const string_t& path ){ 
        static regex_t reg3 = regex_t( PATH_PEG );
        return reg3.test(path); 
    }

    /*─······································································─*/

    inline string_t extname( const string_t& path ){ string_t m;
        regex_t reg( MEMSTR( "\\.\\w+$" ) ); if( !reg.test( path ) )
          { return m; } return reg.match( path ).slice(1);
    }

    /*─······································································─*/

    inline string_t mimetype( const string_t& path ){
        string_t ext = extname( path ); if( ext.empty() )
        { return ext; } if( !_path_::mimetype().has( ext ) )
        { return string::format( MEMSTR( "aplication/%s" ), ext.c_str()); }
          return _path_::mimetype()[ ext ];
    }

    inline string_t mimetype( const path_t& path ){
        if( path.ext.empty() ) { return path.ext; }
        if( !_path_::mimetype().has( path.ext ) )
          { return string::format( MEMSTR( "aplication/%s" ), path.ext.c_str()); }
            return _path_::mimetype()[ path.ext ];
    }

    /*─······································································─*/

    inline string_t dirname( const string_t& path ){
        static regex_t reg0 = regex_t( PATH_SEL );
        auto vec = reg0.split( path );
        vec.pop(); return vec.join( PATH_SEP );
    }

    /*─······································································─*/

    inline string_t basename( const string_t& path ){
        static regex_t reg1 = regex_t( PATH_ONE );
        auto vec = reg1.match_all( path );
        if ( vec.empty() ){ return nullptr; }
        return vec[ vec.last() ];
    }

    /*─······································································─*/

    inline string_t basename( const string_t& path, const string_t& del ){
        static regex_t reg1 = regex_t( PATH_ONE );
        auto vec = reg1.match_all( path );
        if ( vec.empty() ){ return nullptr; }
        return regex::replace( vec[ vec.last() ], del, "" );
    }

    /*─······································································─*/

    inline string_t format( path_t& obj ) { string_t _path;

        if( !obj.path.empty() ){ return obj.path;   }

        if( !obj.root.empty() ){ _path += obj.root ; }
        else                   { _path += PATH_ROOT; }

        if( !obj.dir .empty() ){ _path += obj.dir;  }
        if( !obj.base.empty() ){ _path += obj.base; }

        else {
          if ( !obj.name.empty() ){ _path += obj.name + string::to_string("."); }
          if ( !obj.ext .empty() ){ _path += obj.ext; }
        }

        return _path;
    }

    /*─······································································─*/

    inline path_t parse( const string_t& path ) { path_t out;
        static regex_t reg2 = regex_t( PATH_PEG );

        if( reg2.test( path ) ) out.root = PATH_BEG ;
        else /*--------------*/ out.root = PATH_ROOT;

        out.path = path;
        out.ext  = extname ( path );
        out.dir  = dirname ( path );
        out.base = basename( path );
        out.type = mimetype( path );
        out.name = basename( path, "\\."+out.ext );

        return out;
    }

    /*─······································································─*/

    inline string_t relative( const string_t& path_a, const string_t& path_b ){
        static regex_t reg0 = regex_t( PATH_SEL );

        auto secA = reg0.split( path::normalize(path_a) );
        auto secB = reg0.split( path::normalize(path_b) );
        auto sec  = queue_t<string_t>(); ulong y=0;

        for ( ulong x=0; x<secA.size() && x<secB.size(); ++x ){
         if ( secA[x]==secB[x] ){ ++y; continue; } break;
        }

        for ( ulong x=y; x<secA.size(); ++x ){ sec.push(    ".." ); }
        for ( ulong x=y; x<secB.size(); ++x ){ sec.push( secB[x] ); }

        return array_t<string_t>( sec.data() ).join( PATH_SEP );
    }

    /*─······································································─*/

    inline string_t push( const string_t& path, const string_t& dir ){
        static regex_t reg0 = regex_t( PATH_SEL );
        auto sec = reg0.split( path::normalize(path) );
             sec.push( dir ); /*---------------------*/
             return path::normalize( sec.join( PATH_SEP ) );
    }

    inline string_t unshift( const string_t& path, const string_t& dir ){
        static regex_t reg0 = regex_t( PATH_SEL );
        auto sec = reg0.split( path::normalize(path) );
             sec.unshift( dir ); /*------------------*/
             return path::normalize( sec.join( PATH_SEP ) );
    }

    /*─······································································─*/

    inline string_t pop( const string_t& path ){
        static regex_t reg0 = regex_t( PATH_SEL );
        auto sec = reg0.split( path::normalize(path) );
             sec.pop(); return sec.join( PATH_SEP );
    }

    inline string_t shift( const string_t& path ){
        static regex_t reg0 = regex_t( PATH_SEL );
        auto sec = reg0.split( path::normalize(path) );
             sec.shift(); return sec.join( PATH_SEP );
    }

    /*─······································································─*/

    inline array_t<string_t> split( const string_t& path ){
        static regex_t reg0 = regex_t( PATH_SEL );
        return reg0.split( path::normalize(path) );
    }

    template< class T, ulong N >
    string_t join( string_t (& value)[N] ){
      return array_t<string_t>( N, value ).join("/");
    }

    template< class T, class... V >
    string_t join( const T& argc, const V&... args ){
      return normalize( string::join( PATH_SEP, argc, args... ) );
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#undef PATH_ROOT
#undef PATH_SEP
#undef PATH_ONE
#undef PATH_BEG
#undef PATH_PEG
#undef PATH_SEL

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/
