// ======================================================================================
// File         : shader.c
// Author       : Wu Jie 
// Last Change  : 03/25/2013 | 11:35:04 AM | Monday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include "gl/gl_inc.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static GLuint __shader_load ( const char *_utf8, GLenum _type ) {
    // Create the shader object
    GLuint shader = glCreateShader(_type);
    if (shader == 0) {
        NSLog(@"Error: failed to create shader.");
        return 0;
    }
    
    // Load the shader source
    const char * shaderStringUTF8 = [shaderString UTF8String];
    glShaderSource(shader, 1, &shaderStringUTF8, NULL);
    
    // Compile the shader
    glCompileShader(shader);
    
    // Check the compile status
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
        
        if (infoLen > 1) {
            char * infoLog = malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
            NSLog(@"Error compiling shader:\n%s\n", infoLog );            
            
            free(infoLog);
        }
        
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

GLuint ex_shader_load ( const char *_vpath, const char *_fpath ) {
    // Load the vertex/fragment shaders
    GLuint vertexShader = __shader_load ( GL_VERTEX_SHADER, _vpath );
    if (vertexShader == 0)
        return 0;
    
    GLuint fragmentShader = __shader_load ( GL_FRAGMENT_SHADER, _fpath );
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return 0;
    }
    
    // Create the program object
    GLuint programHandle = glCreateProgram();
    if (programHandle == 0)
        return 0;
    
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    
    // Link the program
    glLinkProgram(programHandle);
    
    // Check the link status
    GLint linked;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
    
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &infoLen);
        
        if (infoLen > 1){
            char * infoLog = malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programHandle, infoLen, NULL, infoLog);

            NSLog(@"Error linking program:\n%s\n", infoLog);            
            
            free(infoLog);
        }
        
        glDeleteProgram(programHandle );
        return 0;
    }
    
    // Free up no longer needed shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return programHandle;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// GLuint programHandle = ex_shader_load ( ... );
// _positionSlot = glGetAttribLocation(programHandle, "vPosition");
// glBindAttribLocation(programHandle, index, attributeName);

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

