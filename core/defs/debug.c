// ======================================================================================
// File         : debug.c
// Author       : Wu Jie 
// Last Change  : 11/16/2010 | 13:25:02 PM | Tuesday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 1024
static bool __initialized = false;

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __short_funcname ( char _short_name[], const char *_function_name, int _len ) {
    int len; 

    len = strlen(_function_name); 
    if ( len > _len-1 ) { 
        memcpy ( _short_name, _function_name, sizeof(char)*(_len-4) ); 
        _short_name[_len-4] = '.'; 
        _short_name[_len-3] = '.'; 
        _short_name[_len-2] = '.'; 
        _short_name[_len-1] = '\0'; 
    } else { 
        strncpy( _short_name, _function_name, len ); 
        _short_name[len] = '\0';
    } 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_log_init () {
    ex_assert ( __initialized == false );

    if ( __initialized )
        return -1;

    // __log_file = ex_text_fopen( "log.txt", false );

    //
    __initialized = true;
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_log_deinit () {
    ex_assert ( __initialized );

    if ( __initialized == false )
        return;

    // if ( __log_file ) {
    //     ex_text_fclose(__log_file);
    //     __log_file = NULL;
    // }
    __initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_log_initialized () {
    return __initialized;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_log ( const char *_fmt, ... ) {
    int     result = -1;
    char    buf[BUF_SIZE];
    char   *buffer = NULL;

    // keep get va string until success 
    // NOTE: the buffer_count-1 will leave 1 character for '\n' and 1 character for null terminal
    EX_GET_VA_STRING_WITH_RESULT( buf, BUF_SIZE-2, _fmt, &result );
    buffer = buf;

    // if we can't use BUF_SIZE store it. 
    if ( result == -1 ) {
        char *dyn_buf = NULL;
        int buffer_count = BUF_SIZE*2;

        do {
            dyn_buf = (char *)ex_realloc_nomng( dyn_buf, buffer_count * sizeof(char) );
            // NOTE: the buffer_count-1 will leave 1 character for '\n' and 1 character for null terminal
            EX_GET_VA_STRING_WITH_RESULT( dyn_buf, buffer_count-2, _fmt, &result );
            buffer_count *= 2;
        } while ( result == -1 );
        buffer = dyn_buf;
    }
    buffer[result] = '\n';
    buffer[result+1] = '\0';

    // print on stdout, also write to log file
    printf( "%s", buffer ); 
    fflush(stdout);
    // NOTE: it is possible we log things before log system intialized
    // if ( __log_file )
    //     ex_text_fwrite( __log_file, buffer, result+2 );

    // if we use dynamic buffer, free it
    if ( buffer != buf )
        ex_free_nomng ( buffer );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void __assert_failed ( const char *_file_name, 
                       const char *_function_name, 
                       size_t _line_nr, 
                       const char *_expr )
{
    int     result = -1;
    char    short_name[64];

    // short the function name
    __short_funcname( short_name, _function_name, 64 );

    //
    ex_log ( "Assert Failed!\n"
             "|- expression: %s\n"
             "|- filename: %s\n"
             "|- line: %d\n"
             "|- function: %s\n",
             _expr, _file_name, (int)_line_nr, short_name );
}

