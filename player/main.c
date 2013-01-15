// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 01/05/2013 | 17:44:08 PM | Saturday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include <assert.h>

#if ( EX_PLATFORM == EX_MACOSX )
    #define main _al_mangled_main
#endif

int main (void) {
    printf ( "Hello World!\n" );

    ex_mem_init ();

    // ex_malloc ( sizeof (char) * 1024 );

    ex_mem_deinit ();

    return 0;
}

