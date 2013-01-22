// ======================================================================================
// File         : fsys.c
// Author       : Wu Jie 
// Last Change  : 01/21/2013 | 15:45:59 PM | Monday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

// physfs
#include <physfs.h>

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#define __PHYSFS_CHECK(_expr) \
    if ( (_expr) == 0 ) { \
        ex_log ( "PhysFS Error: %s", PHYSFS_getLastError() ); \
        return -1; \
    }

static char __main_bundle_path[MAX_PATH]; 

///////////////////////////////////////////////////////////////////////////////
// fsys
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_init ( const char *_media_path ) {
    char path[MAX_PATH];
    const char *app_path = NULL;

    __PHYSFS_CHECK( PHYSFS_init(".") ); // NOTE: we write like this to prevent compile error 
    PHYSFS_permitSymbolicLinks(1); // yes, we permit symbolic links

#if (EX_PLATFORM == EX_IOS)
    app_path = ex_fsys_main_bundle_path();
#else
    app_path = ex_fsys_app_dir();
#endif

    ex_log ( "user dir: %s", ex_fsys_user_dir() );
    ex_log ( "app dir: %s", app_path );

    // NOTE: this must be done before ex_log_init, so that log.txt can be open in the corrent path.

    if ( _media_path ) {

        // if the media_path exists, use it. if not, try to search it in the app/ directory
        if ( ex_os_exists (_media_path) == false ) {
            strncpy ( path, app_path, MAX_PATH );
            strcat ( path, _media_path );
        }
        else {
            strncpy ( path, _media_path, MAX_PATH );
        }

        //
        if ( ex_os_exists (path) ) {

            // set write dir
            if ( ex_fsys_set_write_dir(path) != 0 )
                return -1;
            ex_log("set write dir: %s", path );

            // mount the write dir 
            // NOTE: set write dir doesn't means you mount it.
            if ( ex_fsys_mount( path, NULL, true ) != 0 )
                return -1;
            ex_log("mount dir: %s", path );
        }
        else {
            ex_error ( "can't find the media path %s", _media_path );
            return -1;
        }
    }
    else if ( app_path ) {
        // we add app/ as the default write directory
        strncpy ( path, app_path, MAX_PATH );

        // NOTE: set write dir doesn't means you mount it.
        // we mount the app/ directory below
        if ( ex_fsys_set_write_dir(path) != 0 )
            return -1;
        ex_log("set default write dir: %s", path );
    }
    else {
        ex_error ( "can't set a write directory" );
        return -1;
    }

    // if ~/.exsdk/ exists we add it as the primary builtin search directory
    if ( ex_fsys_user_dir() ) {
        strncpy ( path, ex_fsys_user_dir(), MAX_PATH );
        strcat ( path, ".exsdk/" );
        if ( ex_os_exists(path) && ex_os_isdir(path) ) {
            if ( ex_fsys_mount( path, NULL, true ) != 0 )
                return -1;
            ex_log("mount dir: %s", path );
        }
    }

    // if app/ exists, we add it as the second builtin search directory.
    if ( app_path ) {
        strncpy ( path, app_path, MAX_PATH );
        if ( ex_fsys_mount( path, NULL, true ) != 0 )
            return -1;
        ex_log("mount dir: %s", path );
    }

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_fsys_deinit () {
    PHYSFS_deinit();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_fsys_initialized () {
    return PHYSFS_isInit();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_fsys_free_list( void *_list ) {
    PHYSFS_freeList(_list);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_fsys_set_main_bundle_path ( const char *_path ) {
    strncpy( __main_bundle_path, _path, MAX_PATH );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char *ex_fsys_main_bundle_path () { return __main_bundle_path; }

///////////////////////////////////////////////////////////////////////////////
// os
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// defines
extern int __PHYSFS_platformExists( const char * );
extern int __PHYSFS_platformIsSymLink( const char * );
extern int __PHYSFS_platformIsDirectory( const char * );
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_os_exists ( const char *_path ) {
    return __PHYSFS_platformExists(_path);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_os_isdir ( const char *_path ) {
    return __PHYSFS_platformIsDirectory(_path);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_os_issymlink ( const char *_path ) {
    return __PHYSFS_platformIsSymLink(_path);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_os_isfile ( const char *_path ) {
    if ( __PHYSFS_platformExists(_path) == false ) {
        return false;
    }
    return (__PHYSFS_platformIsSymLink(_path) || __PHYSFS_platformIsDirectory(_path)) ? false : true;
}

