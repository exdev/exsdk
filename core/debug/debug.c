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

#define BUF_SIZE 1024

typedef struct __error_info_t {
    char message[BUF_SIZE];
    const char *file_name; 
    size_t line_nr; 
    const char *function_name; 
} __error_info_t;

///////////////////////////////////////////////////////////////////////////////
// static
///////////////////////////////////////////////////////////////////////////////

// static ex_text_file_t *__log_file = NULL;
static bool __initialized = false;
static ex_list_t __error_stack;

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

static void __push_error ( const char *_msg, 
                           const char *_file_name,  
                           size_t _line_nr,
                           const char *_function_name )
{
    __error_info_t errorInfo;
    strncpy ( errorInfo.message, _msg, BUF_SIZE );
    errorInfo.message[BUF_SIZE-1] = '\0';
    errorInfo.file_name = _file_name;
    errorInfo.line_nr = _line_nr;
    errorInfo.function_name = _function_name;

    if ( ex_list_count( &__error_stack ) > 10 )
        ex_list_pop_front ( &__error_stack );
    ex_list_append ( &__error_stack, &errorInfo );
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: NOTE: only available in core.c 
// ------------------------------------------------------------------ 

void __init_error_stack () {
    ex_list_init( &__error_stack,
                  sizeof(__error_info_t),
                  __ex_list_alloc_nomng, 
                  __ex_list_realloc_nomng,
                  __ex_list_dealloc_nomng );
} 

// ------------------------------------------------------------------ 
// Desc: NOTE: only available in core.c 
// ------------------------------------------------------------------ 

void __deinit_error_stack () {
    ex_list_deinit ( &__error_stack ); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_log_init () {

    // if the log system already initialized, don't init it second times.
    if ( __initialized ) {
        ex_warning ( "log system already initialized" );
        return 1;
    }

    // __log_file = ex_text_fopen( "log.txt", false );

    //
    __initialized = true;
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_log_deinit () {
    if ( __initialized ) {
        // if ( __log_file ) {
        //     ex_text_fclose(__log_file);
        //     __log_file = NULL;
        // }
        __initialized = false;
    }
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

void ex_show_last_error () {
    ex_list_node_t *node = ex_list_tail ( &__error_stack );
    __error_info_t *info = (__error_info_t *)node->value;
    ex_log ( "Last Error\n"
             "|- message: %s\n"
             "|- filename: %s\n"
             "|- line: %d\n"
             "|- function: %s\n",
             info->message, info->file_name, info->line_nr, info->function_name );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

bool __assert_failed ( bool *_do_hw_break, 
                       const char *_file_name, 
                       const char *_function_name, 
                       size_t _line_nr, 
                       const char *_expr,
                       const char *_msg, 
                       ... )
{
    int     result = -1;
    char    short_name[64];
    int     mbResult = -1;
    char    buf[BUF_SIZE];
    char   *buffer = NULL;

    EX_GET_VA_STRING_WITH_RESULT( buf, BUF_SIZE-1, _msg, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
    buffer = buf;
    if ( result == -1 ) {
        char *dyn_buf = NULL;
        int buffer_count = BUF_SIZE * 2;

        // keep get va string until success 
        do {
            dyn_buf = (char *)ex_realloc_nomng( dyn_buf, buffer_count * sizeof(char) );
            EX_GET_VA_STRING_WITH_RESULT( dyn_buf, buffer_count-1, _msg, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
            buffer_count *= 2;
        } while ( result == -1 );
        buffer = dyn_buf;
    }
    buffer[result] = '\0';


    // short the function name
    __short_funcname( short_name, _function_name, 64 );

    //
    ex_log ( "Assert Failed!\n"
             "|- message: %s\n"
             "|- expression: %s\n"
             "|- filename: %s\n"
             "|- line: %d\n"
             "|- function: %s\n",
             buffer, _expr, _file_name, (int)_line_nr, short_name );
    mbResult = ex_message_box( EX_MSG_BOX_FAILED, "Assert Failed", 
                            "Assert Failed!\n"
                            "|- message: %s\n" 
                            "|- expression: %s\n" 
                            "|- filename: %s\n"
                            "|- line: %d\n"
                            "|- function: %s\n",
                            buffer, _expr, _file_name, (int)_line_nr, short_name );

    // if we use dynamic buffer, free it
    if ( buffer != buf )
        ex_free_nomng ( buffer );

    //
#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    (*_do_hw_break) = (mbResult != IDIGNORE);
    return (mbResult == IDRETRY);
#else
    (*_do_hw_break) = true;
    return true;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __log_error ( const char *_file_name, 
                   const char *_function_name, 
                   size_t _line_nr, 
                   const char *_msg, 
                   ... )
{
    int     result = -1;
    char    short_name[64];
    char    buf[BUF_SIZE];
    char   *buffer = NULL;

    EX_GET_VA_STRING_WITH_RESULT( buf, BUF_SIZE-1, _msg, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
    buffer = buf;
    if ( result == -1 ) {
        char *dyn_buf = NULL;
        int buffer_count = BUF_SIZE * 2;

        // keep get va string until success 
        do {
            dyn_buf = (char *)ex_realloc_nomng( dyn_buf, buffer_count * sizeof(char) );
            EX_GET_VA_STRING_WITH_RESULT( dyn_buf, buffer_count-1, _msg, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
            buffer_count *= 2;
        } while ( result == -1 );
        buffer = dyn_buf;
    }
    buffer[result] = '\0';

    // short the function name
    __short_funcname( short_name, _function_name, 64 );

    //
    ex_log ( "Error!\n"
             "|- message: %s\n"
             "|- filename: %s\n"
             "|- line: %d\n"
             "|- function: %s\n",
             buffer, _file_name, (int)_line_nr, short_name );
    __push_error ( buffer, _file_name, _line_nr, short_name );

    // if we use dynamic buffer, free it
    if ( buffer != buf )
        ex_free_nomng ( buffer );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __log_warning ( const char *_file_name, 
                     const char *_function_name, 
                     size_t _line_nr, 
                     const char *_msg, 
                     ... )
{
    int     result = -1;
    char    short_name[64];
    char    buf[BUF_SIZE];
    char   *buffer = NULL;

    EX_GET_VA_STRING_WITH_RESULT( buf, BUF_SIZE-1, _msg, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
    buffer = buf;
    if ( result == -1 ) {
        char *dyn_buf = NULL;
        int buffer_count = BUF_SIZE * 2;

        // keep get va string until success 
        do {
            dyn_buf = (char *)ex_realloc_nomng( dyn_buf, buffer_count * sizeof(char) );
            EX_GET_VA_STRING_WITH_RESULT( dyn_buf, buffer_count-1, _msg, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
            buffer_count *= 2;
        } while ( result == -1 );
        buffer = dyn_buf;
    }
    buffer[result] = '\0';

    // short the function name
    __short_funcname( short_name, _function_name, 64 );

    //
    ex_log ( "Warning!\n"
             "|- message: %s\n"
             "|- filename: %s\n"
             "|- line: %d\n"
             "|- function: %s\n",
             buffer, _file_name, (int)_line_nr, short_name );

    // if we use dynamic buffer, free it
    if ( buffer != buf )
        ex_free_nomng ( buffer );
}

