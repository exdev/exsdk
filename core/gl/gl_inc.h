// ======================================================================================
// File         : gl_inc.h
// Author       : Wu Jie 
// Last Change  : 01/08/2013 | 13:36:13 PM | Tuesday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef GL_INC_H_1357623374
#define GL_INC_H_1357623374
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// platform include
///////////////////////////////////////////////////////////////////////////////

#if (EX_PLATFORM == EX_WIN32)

    // NOTE: in Windows, we use glew instead
    // #include <GL/gl.h>
    // #include <GL/glu.h>
    #include <GL/glew.h>
    #include <GL/wglew.h>

	#include "GL/glut.h"

#elif (EX_PLATFORM == EX_LINUX)

	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>

#elif (EX_PLATFORM == EX_MACOSX)

	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>

#elif (EX_PLATFORM == EX_IOS)

    #include <OpenGLES/ES1/gl.h>
    #include <OpenGLES/ES1/glext.h>

#endif

// #################################################################################
#endif // END GL_INC_H_1357623374
// #################################################################################


