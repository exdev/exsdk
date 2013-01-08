// ======================================================================================
// File         : msgbox.c
// Author       : Wu Jie 
// Last Change  : 06/27/2010 | 11:38:43 AM | Sunday,June
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
 
#define BUF_SIZE 1024

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_message_box ( int _msgType, const char *_caption, const char *_expr,  ... )
{
    //
    int result = -1;
    int ret;
    char *buffer = NULL;
    char buf[BUF_SIZE];

#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    uint type = MB_OK;
#endif

    // keep get va string until success 
    EX_GET_VA_STRING_WITH_RESULT( buf, BUF_SIZE-1, _expr, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
    buffer = buf;
    if ( result == -1 ) {
        char *dyn_buf = NULL;
        int buffer_count = BUF_SIZE * 2;

        // keep get va string until success 
        do {
            dyn_buf = (char *)ex_realloc_nomng( dyn_buf, buffer_count * sizeof(char) );
            EX_GET_VA_STRING_WITH_RESULT( dyn_buf, buffer_count-1, _expr, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
            buffer_count *= 2;
        } while ( result == -1 );
        buffer = dyn_buf;
    }
    buffer[result] = '\0';


#if (EX_PLATFORM == EX_WIN32) || (EX_PLATFORM == EX_XENON)
    if ( _msgType == EX_MSG_BOX_FAILED )
        type = MB_ABORTRETRYIGNORE|MB_ICONWARNING; // TODO: should be "Skip, Break, Ignore"
    else if ( _msgType == EX_MSG_BOX_ERROR )
        type = MB_ABORTRETRYIGNORE|MB_ICONERROR;
    else if ( _msgType == EX_MSG_BOX_WARNING )
        type = MB_ICONWARNING;

    ret = MessageBox( NULL, buffer, _caption, type );
#endif

    // release buffer we allocate
    if ( buffer != buf )
        ex_free_nomng ( buffer );

    //
    return ret;
}


