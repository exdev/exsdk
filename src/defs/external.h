// ======================================================================================
// File         : external.h
// Author       : Wu Jie 
// Last Change  : 01/05/2013 | 15:15:19 PM | Saturday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef EXTERNAL_H_1277550673
#define EXTERNAL_H_1277550673
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// platform include
///////////////////////////////////////////////////////////////////////////////

#if (EX_PLATFORM == EX_WIN32)

    // if use memory manager and in debug version
    #if ( EX_USE_SYSTEM_MEMORY || (EX_USE_MEMORY_MANAGER && EX_DBG_WITH_CRT) ) && defined (EX_DEBUG)
        #define _CRTDBG_MAP_ALLOC
        // #define _CRTDBG_MAP_ALLOC_NEW // not really helpful!

        #include <crtdbg.h>
    #endif

    #include <windows.h>
    #include <malloc.h> 
    #include <time.h>
    #include <intrin.h>

    // // to use the sse intrins in gcc, please add -msse compile flag in makefile of this project
    // #include <xmmintrin.h>  // for type __m128

	#include <gl/gl.h>
	#include <gl/glu.h>
	#include "GL/glut.h"

#elif (EX_PLATFORM == EX_LINUX)

    #include <malloc.h> 
    #include <io.h>
    #include <endian.h>    /* attempt to define endianness */

    // to use the sse intrins in gcc, please add -msse compile flag in makefile of this project
    #include <xmmintrin.h>  // for type __m128

#elif (EX_PLATFORM == EX_MACOSX)

    #include <unistd.h> 
    #include <pthread.h>
    #include <signal.h>
    #include <semaphore.h>
    #include <errno.h>
    #include <sys/time.h>

	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
    #include <libkern/OSAtomic.h>

#elif (EX_PLATFORM == EX_IOS)

    #include <unistd.h> 
    #include <pthread.h>
    #include <signal.h>
    #include <semaphore.h>
    #include <errno.h>
    #include <sys/time.h>

    #include <OpenGLES/ES1/gl.h>
    #include <OpenGLES/ES1/glext.h>

#endif

///////////////////////////////////////////////////////////////////////////////
// compiler include
///////////////////////////////////////////////////////////////////////////////

#if ( EX_COMPILER == EX_MSVC ) // msvc

    #ifndef MAX_PATH
    #define MAX_PATH 260
    #endif

#elif ( EX_COMPILER == EX_GCC ) // gcc

    #ifndef CHAR_BIT
    #define CHAR_BIT __CHAR_BIT__
    #endif

    #ifndef MAX_PATH
    #define MAX_PATH 260
    #endif

#endif

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h> 
#include <setjmp.h>
#include <wchar.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////
// 3rd-library
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

///////////////////////////////////////////////////////////////////////////////
// windows re-define
///////////////////////////////////////////////////////////////////////////////

#if (EX_PLATFORM == EX_WIN32)
    #define snprintf _snprintf
#endif

// #################################################################################
#endif // END EXTERNAL_H_1277550673
// #################################################################################


