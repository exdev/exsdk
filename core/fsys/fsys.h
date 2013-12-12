// ======================================================================================
// File         : fsys.h
// Author       : Wu Jie 
// Last Change  : 01/21/2013 | 15:26:22 PM | Monday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FSYS_H_1358753184
#define FSYS_H_1358753184
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define EX_SEEK_SET	0 // Seek from the beginning of data
#define EX_SEEK_CUR	1 // Seek relative to current read point
#define EX_SEEK_END	2 // Seek relative to the end of data

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

typedef void ex_file_t;

///////////////////////////////////////////////////////////////////////////////
// file sys
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_fsys_init ();
extern void ex_fsys_deinit ();
extern bool ex_fsys_initialized ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// for iPhone:
//     //get the main bundle path
//     NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
//     NSString *path = [[[NSBundle mainBundle] bundlePath]stringByAppendingPathComponent:@""];
//     path = [path stringByAppendingString:@"/"];
//     const char *c_path = [path UTF8String];
       
//     // set the main bundle path
//     ex_fsys_set_main_bundle_path(c_path);

extern const char *ex_fsys_main_bundle_path (); // main bundle path in iOS device
extern const char *ex_fsys_app_dir (); // current application's directory
extern const char *ex_fsys_user_dir (); // current user's home directory
extern const char *ex_fsys_write_dir ();

// So, if you look for "maps/level1.map", 
// and C:\mygame is in your search path and C:\mygame\maps\level1.map exists, 
// then "C:\mygame" is returned.
extern const char *ex_fsys_realdir ( const char *_path );

extern void ex_fsys_set_main_bundle_path ( const char *_path );
extern int ex_fsys_set_write_dir ( const char *_new_dir );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_fsys_mount ( const char *_dir, const char *_mount_point, bool _append );
extern int ex_fsys_unmount ( const char *_dir );
extern const char *ex_fsys_mount_point ( const char *_dir );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_fsys_mkdir ( const char *_path );
extern int ex_fsys_rmdir ( const char *_path, bool _force );
extern int ex_fsys_rm ( const char *_path );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// Example:
//     char **file_list, i;
//     file_list = ex_fsys_files_in("your/search/path/");
//     for ( i = file_list; *i != NULL; ++i ) {
//     }
//     ex_fsys_free_list(file_list); // DO NOT FORGET!

extern char **ex_fsys_mounts (); // NOTE: needs call ex_fsys_free_list(file_list); after
extern char **ex_fsys_files_in ( const char *_path ); // NOTE: needs call ex_fsys_free_list(file_list); after
extern void ex_fsys_free_list ( void *_list );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern bool ex_fsys_isdir ( const char *_path );
extern bool ex_fsys_isfile ( const char *_path );
extern bool ex_fsys_issymlink ( const char *_path );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern bool ex_fsys_exists ( const char *_path );
extern bool ex_fsys_file_exists ( const char *_path );
extern bool ex_fsys_dir_exists ( const char *_path );

///////////////////////////////////////////////////////////////////////////////
// file io
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
/* "r" = reading, file must exist */
/* "w" = writing, truncate existing, file may not exist */
/* "r+"= reading or writing, file must exist            */
/* "a" = writing, append file may not exist             */
/* "a+"= append + read, file may not exist              */
/* "w+" = read, write, truncate. file may not exist     */
// ------------------------------------------------------------------ 

// extern ex_file_t *ex_fopen ( const char *_filename, const char *_mode ); 

extern ex_file_t *ex_fsys_fopen_r ( const char *_filename ); 
extern ex_file_t *ex_fsys_fopen_w ( const char *_filename ); 
extern ex_file_t *ex_fsys_fopen_a ( const char *_filename ); 
extern int ex_fsys_fclose ( ex_file_t *_file ); 

extern int ex_fsys_fseek ( ex_file_t *_file, size_t _pos ); 
extern size_t ex_fsys_fsize ( ex_file_t *_file ); 
extern size_t ex_fsys_ftell ( ex_file_t *_file ); 

extern size_t ex_fsys_fread ( ex_file_t *_file, void *_buf, uint64 _size );
extern size_t ex_fsys_fwrite ( ex_file_t *_file, const void *_buf, uint64 _size );
extern int ex_fsys_fflush ( ex_file_t *_file ); 
extern int ex_fsys_feof ( ex_file_t *_file ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern const char *ex_os_getcwd ();
extern void ex_os_setcwd ( const char *_path );

extern bool ex_os_exists ( const char *_path );
extern bool ex_os_isdir ( const char *_path );
extern bool ex_os_issymlink ( const char *_path );
extern bool ex_os_isfile ( const char *_path );

extern ex_file_t *ex_os_fopen ( const char *_path, const char *_mode );
extern int ex_os_fclose ( ex_file_t *_file );

extern int ex_os_fseek ( ex_file_t *_file, size_t _pos );
extern size_t ex_os_fsize ( ex_file_t *_file ); 
extern size_t ex_os_ftell ( ex_file_t *_file ); 

extern size_t ex_os_fread ( ex_file_t *_file, void *_buf, uint64 _size );
extern size_t ex_os_fwrite ( ex_file_t *_file, const void *_buf, uint64 _size );

// #################################################################################
#endif // END FSYS_H_1358753184
// #################################################################################


