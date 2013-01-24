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

#if ( EX_PLATFORM == EX_MACOSX )
    #define main _al_mangled_main
#endif

int main (void) {

    // init 
    if ( !ex_sdk_init() ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    // main-loop 
    // ex_malloc ( sizeof (char) * 1024 );

    // deinits 
    ex_sdk_deinit ();

    return 0;
}

