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
        ex_log ( "[fsys] Error: %s", PHYSFS_getLastError() ); \
        return -1; \
    }

static char __main_bundle_path[MAX_PATH]; 

///////////////////////////////////////////////////////////////////////////////
// fsys
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_init () {
    char path[MAX_PATH];
    const char *app_path = NULL;
    const char *usr_path = NULL;

    __PHYSFS_CHECK( PHYSFS_init(".") ); // NOTE: we write like this to prevent compile error 
    PHYSFS_permitSymbolicLinks(1); // yes, we permit symbolic links

#if (EX_PLATFORM == EX_IOS)
    app_path = ex_fsys_main_bundle_path();
#else
    app_path = ex_fsys_app_dir();
#endif
    usr_path = ex_fsys_user_dir();

    ex_log ( "[fsys] User Dir: %s", usr_path );
    ex_log ( "[fsys] Application Dir: %s", app_path );

    // if ~/.exsdk/ exists we add it as the secondly primary search directory
    if ( usr_path ) {
        strncpy ( path, usr_path, MAX_PATH );
        strcat ( path, ".exsdk/" );

        //
        if ( ex_os_exists(path) && ex_os_isdir(path) ) {
            if ( ex_fsys_mount( path, NULL, true ) != 0 )
                return -1;
            ex_log ("[fsys] Mount dir: %s", path );
        }
    }

    // if app/ exists, we add it as the secondly search directory.
    if ( app_path ) {
        strncpy ( path, app_path, MAX_PATH );
        // strcat ( path, "builtin/" );

        // NOTE: set write dir doesn't means you mount it.
        if ( ex_fsys_set_write_dir(path) != 0 )
            return -1;
        ex_log ( "[fsys] Set default write dir: %s", path  );

        //
        if ( ex_fsys_mount( path, NULL, true ) != 0 )
            return -1;
        ex_log ( "[fsys] Mount dir: %s", path  );
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

const char *ex_fsys_main_bundle_path () { return __main_bundle_path; }
const char *ex_fsys_app_dir () { return PHYSFS_getBaseDir(); }
const char *ex_fsys_user_dir () { return PHYSFS_getUserDir(); }
const char *ex_fsys_write_dir () { return PHYSFS_getWriteDir(); }
const char *ex_fsys_realdir ( const char *_path ) { return PHYSFS_getRealDir(_path); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_fsys_set_main_bundle_path ( const char *_path ) {
    strncpy( __main_bundle_path, _path, MAX_PATH );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_set_write_dir ( const char *_new_dir ) { 
    __PHYSFS_CHECK( PHYSFS_setWriteDir(_new_dir) );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_mount ( const char *_dir, const char *_mount_point, bool _append ) {
    __PHYSFS_CHECK( PHYSFS_mount ( _dir, _mount_point, _append ) );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_unmount ( const char *_dir ) {
#if 0
    __PHYSFS_CHECK( PHYSFS_unmount(_dir) );
    return 0;
#else
    __PHYSFS_CHECK( PHYSFS_removeFromSearchPath(_dir) );
    return 0;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char *ex_fsys_mount_point ( const char *_dir ) {
    return PHYSFS_getMountPoint ( _dir );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_mkdir ( const char *_dir ) {
    __PHYSFS_CHECK( PHYSFS_mkdir(_dir) );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_rmdir ( const char *_dir, bool _force ) {
    if ( ex_fsys_isdir (_dir) ) {
        // TODO: if force, remove all the files in the directory, then delete it.
        // if not, check if the directory is empty and delete it.

        __PHYSFS_CHECK( PHYSFS_delete(_dir) );
        return 0;
    }

    ex_log ( "[fsys] Error: %s is not a directory", _dir );
    return -1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_rm ( const char *_filename ) {
    if ( ex_fsys_isfile (_filename) ) {
        __PHYSFS_CHECK( PHYSFS_delete(_filename) );
        return 0;
    }

    ex_log ( "[fsys] Error: %s is not a file", _filename );
    return -1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

char **ex_fsys_mounts () { return PHYSFS_getSearchPath (); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

char **ex_fsys_files_in ( const char *_path ) {
    return PHYSFS_enumerateFiles(_path); 
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

bool ex_fsys_isdir ( const char *_path ) {
#if 0
    PHYSFS_Stat stat;
    if ( PHYSFS_stat( _path, &stat ) == 0 ) {
        ex_error ( "error: %s", PHYSFS_getLastError() );
        return false;
    }
    return (stat.filetype == PHYSFS_FILETYPE_DIRECTORY);
#else
    return PHYSFS_isDirectory(_path);
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_fsys_isfile ( const char *_path ) {
#if 0
    PHYSFS_Stat stat;
    if ( PHYSFS_stat( _path, &stat ) == 0 ) {
        ex_error ( "error: %s", PHYSFS_getLastError() );
        return false;
    }
    return (stat.filetype == PHYSFS_FILETYPE_REGULAR);
#else
    return !PHYSFS_isDirectory(_path);
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_fsys_issymlink ( const char *_path ) {
#if 0
    PHYSFS_Stat stat;
    if ( PHYSFS_stat( _path, &stat ) == 0 ) {
        ex_error ( "error: %s", PHYSFS_getLastError() );
        return false;
    }
    return (stat.filetype == PHYSFS_FILETYPE_SYMLINK);
#else
    return PHYSFS_isSymbolicLink(_path);
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_fsys_exists( const char *_path ) {
    return PHYSFS_exists(_path);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_fsys_file_exists( const char *_path ) {
    return ex_fsys_exists(_path) && ex_fsys_isfile(_path);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_fsys_dir_exists( const char *_path ) {
    return ex_fsys_exists(_path) && ex_fsys_isdir(_path);
}

///////////////////////////////////////////////////////////////////////////////
// file io
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_file_t *ex_fsys_fopen_r ( const char *_filename ) {
    return PHYSFS_openRead(_filename);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_file_t *ex_fsys_fopen_w ( const char *_filename ) {
    return PHYSFS_openWrite(_filename);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_file_t *ex_fsys_fopen_a ( const char *_filename ) {
    return PHYSFS_openAppend(_filename);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_fclose ( ex_file_t *_file ) {
    return PHYSFS_close(_file);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_fseek ( ex_file_t *_file, size_t _pos ) {
    return PHYSFS_seek(_file,_pos);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_fsys_fsize ( ex_file_t *_file ) {
    return (size_t)PHYSFS_fileLength(_file);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_fsys_ftell ( ex_file_t *_file ) {
    return (size_t)PHYSFS_tell(_file);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_fsys_fread ( ex_file_t *_file, void *_buf, uint64 _size ) {
#if 0
    return (size_t)PHYSFS_readBytes( _file, _buf, _size );
#else
    return (size_t)PHYSFS_read( _file, _buf, 1, (uint)_size );
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_fsys_fwrite ( ex_file_t *_file, const void *_buf, uint64 _size ) {
#if 0
    return (size_t)PHYSFS_writeBytes( _file, _buf, _size );
#else
    return (size_t)PHYSFS_write( _file, _buf, 1, (uint)_size );
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_fflush ( ex_file_t *_file ) {
    return PHYSFS_flush(_file);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_fsys_feof ( ex_file_t *_file ) {
    return PHYSFS_eof(_file);
}

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

