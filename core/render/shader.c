// ======================================================================================
// File         : shader.c
// Author       : Wu Jie 
// Last Change  : 03/25/2013 | 11:35:04 AM | Monday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include "exsdk.h"
#include "gl/gl_inc.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static GLuint __compile_shader ( GLenum _type, const char *_buf ) {
    GLint compiled = 0;
    GLuint shader = 0;

    // Create the shader object
    shader = glCreateShader(_type);
    if ( shader == 0 ) {
        ex_set_error ( "[shader] Error: failed to create shader" );
        return 0;
    }
    
    // Load the shader source
    glShaderSource(shader, 1, &_buf, NULL);
    
    // Compile the shader
    glCompileShader(shader);
    
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if ( !compiled ) {
        GLint infoLen = 0;
        glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
        
        if ( infoLen > 1 ) {
            char *infoLog = ex_malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
            ex_set_error( "[shader] Compile error: %s", infoLog  );            
            ex_free(infoLog);
        }
        
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint ex_shader_load ( const char *_vbuf, const char *_fbuf ) {
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint programHandle = 0;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = __compile_shader ( GL_VERTEX_SHADER, _vbuf );
    if ( vertexShader == 0 )
        return 0;
    
    fragmentShader = __compile_shader ( GL_FRAGMENT_SHADER, _fbuf );
    if ( fragmentShader == 0 ) {
        glDeleteShader(vertexShader);
        return 0;
    }
    
    // Create the program object
    programHandle = glCreateProgram();
    if ( programHandle == 0 )
        return 0;
    
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    
    // Link the program
    glLinkProgram(programHandle);
    
    // Check the link status
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
    
    if ( !linked ) {
        GLint infoLen = 0;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &infoLen);
        
        if ( infoLen > 1 ) {
            char * infoLog = ex_malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programHandle, infoLen, NULL, infoLog);
            ex_set_error( "[shader] Link error: %s", infoLog  );            
            ex_free(infoLog);
        }
        
        glDeleteProgram(programHandle );
        return 0;
    }
    
    // Free up no longer needed shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return (uint)programHandle;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// GLuint programHandle = ex_shader_load ( ... );
// _positionSlot = glGetAttribLocation(programHandle, "vPosition");
// glBindAttribLocation(programHandle, index, attributeName);
