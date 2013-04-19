// ======================================================================================
// File         : test_memmory.c
// Author       : Wu Jie 
// Last Change  : 04/19/2013 | 10:59:20 AM | Friday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 4096

int main (void) {
    int i = 0;
    void *buffer[BUF_SIZE];

    ex_sdk_init ();

    i = 0;
    while ( i < BUF_SIZE ) {
        buffer[i] = ex_malloc( sizeof(int) * rand() );
        ++i;
    }

    // i = 0;
    // while ( i < BUF_SIZE ) {
    //     buffer[i] = ex_realloc( buffer[i], sizeof(int) * rand() );
    //     ++i;
    // }

    i = 0;
    while ( i < BUF_SIZE ) {
        ex_free(buffer[i]);
        ++i;
    }

    ex_sdk_deinit ();
    return 0;
}
