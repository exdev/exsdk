// ======================================================================================
// File         : str_op.c
// Author       : Wu Jie 
// Last Change  : 02/20/2013 | 11:45:47 AM | Wednesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char * ex_str_replace ( const char *_path, char _from, char _to ) {
    char *p;

    p = (char *)_path;
    while ( *p != '\0' ) {
        if ( *p == _from ) {
            *p = _to;
        }
        ++p;
    }

    return _path;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_str_simplify_path ( const char *_path ) {
    char *cur;
    char *t;
    int isrooted;
    char *very_start = (char *)_path;
    char *start;

    if (!*_path)
        return;

    if ((isrooted = _path[0] == '/'))
        very_start++;

    /* Before   After
     *  /foo/   /foo
     *  /foo/../../bar  /bar
     *  /foo/./blah/..  /foo
     *  .    .
     *  ..    ..
     *  ./foo   foo
     *  foo/../../../bar  ../../bar
     */

    for ( cur = t = start = very_start; ;  ) {
        /* treat multiple '/'s as one '/' */
        while (*t == '/')
            t++;

        if (*t == '\0') {
            if (cur == _path)
                /* convert empty _path to dot */
                *cur++ = '.';
            *cur = '\0';
            break;
        }

        if (t[0] == '.') {
            if (!t[1] || t[1] == '/') {
                t += 1;
                continue;
            } else if (t[1] == '.' && (!t[2] || t[2] == '/')) {
                if (!isrooted && cur == start) {
                    if (cur != very_start)
                        *cur++ = '/';
                    *cur++ = '.';
                    *cur++ = '.';
                    start = cur;
                } else if (cur != start)
                    while (--cur > start && *cur != '/')
                        ;
                t += 2;
                continue;
            }
        }

        if (cur != very_start)
            *cur++ = '/';

        /* find/copy next component of pathname */
        while (*t && *t != '/')
            *cur++ = *t++;
    }
}
