// ======================================================================================
// File         : mathtypes.h
// Author       : Wu Jie 
// Last Change  : 01/08/2013 | 22:13:14 PM | Tuesday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATHTYPES_H_1357654396
#define MATHTYPES_H_1357654396
// #################################################################################

// ------------------------------------------------------------------ 
/*! 
 @struct ex_vec2f_t
 @details
 
 The data of vector2 is construct by an union structure with float elements.\n
 The vector2 can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c }
   x & y
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c }
   v_{0}, v_{1}
   \end{array} \right]
 \f$

 @note you can use: 

 @code
 ex_vec2f_t v = { 1.0f, 1.0f }; 
 @endcode

 to initialize a vector.  
*/// ------------------------------------------------------------------ 

typedef struct ex_vec2f_t {
    union {
        struct { float x, y; }; // end struct
        float data[2];
    };
} ex_vec2f_t;


// ------------------------------------------------------------------ 
/*! 
 @struct ex_vec3f_t
 @details
 
 The data of vector3 is construct by an union structure with float elements.\n
 The vector3 can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c c }
   x & y & z
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c c }
   v_{0}, v_{1}, v_{2}
   \end{array} \right]
 \f$

 @note you can use: 

 @code
 ex_vec3f_t v = { 1.0f, 1.0f, 1.0f }; 
 @endcode

 to initialize a vector.  
*/// ------------------------------------------------------------------ 

typedef struct ex_vec3f_t {
    union {
        struct { float r, g, b; }; // end struct
        struct { float x, y, z; }; // end struct
        float data[3];
    };
} ex_vec3f_t;

// ------------------------------------------------------------------ 
/*! 
 @struct ex_vec4f_t
 @details
 
 The data of vector4 is construct by an union structure with float elements.\n
 The vector4 can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c c c }
   x & y & z & w
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c c }
   v_{0}, v_{1}, v_{2}, v_{3}
   \end{array} \right]
 \f$

 @note you can use: 

 @code
 ex_vec4f_t v = { 1.0f, 1.0f, 1.0f, 1.0f }; 
 @endcode

 to initialize a vector.  
*/// ------------------------------------------------------------------ 

typedef struct ex_vec4f_t {
    union {
        struct { float r, g, b, a; }; // end struct
        struct { float x, y, z, w; }; // end struct
        float data[4];
    };
} ex_vec4f_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

typedef struct ex_vec3i_t {
    union {
        struct { int x, y, z; }; // end struct
        float data[4];
    };
} ex_vec3i_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

typedef struct ex_vec4i_t {
    union {
        struct { int x, y, z, w; }; // end struct
        float data[4];
    };
} ex_vec4i_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

typedef struct ex_vec3u_t {
    union {
        struct { uint8 r, g, b; }; // end struct
        struct { uint8 x, y, z; }; // end struct
        float data[4];
    };
} ex_vec3u_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

typedef struct ex_vec4u_t {
    union {
        struct { uint8 r, g, b, a; }; // end struct
        struct { uint8 x, y, z, w; }; // end struct
        float data[4];
    };
} ex_vec4u_t;

// ------------------------------------------------------------------ 
/*! 
 @struct ex_mat22f_t
 @details
 
 The data of matrix 2x2 is construct by an union structure with float elements.\n
 The matrix can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c }
   m_{00} & m_{01} \\
   m_{10} & m_{11}
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c }
   m_{00}, m_{01}, m_{10}, m_{11}
   \end{array} \right]
 \f$
*/// ------------------------------------------------------------------ 

typedef struct ex_mat22f_t {
    union {
        struct { 
            float m00, m01;
            float m10, m11;
        }; // end struct
        float m[4];
    };
} ex_mat22f_t;

// ------------------------------------------------------------------ 
/*! 
 @struct ex_mat33f_t
 @details
 
 The data of matrix 3x3 is construct by an union structure with float elements.\n
 The matrix can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c c }
   m_{00} & m_{01} & m_{02} \\
   m_{10} & m_{11} & m_{12} \\
   m_{20} & m_{21} & m_{22}
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c c c c c c c c }
   m_{00}, m_{01}, m_{02}, m_{10}, m_{11}, m_{12}, m_{20}, m_{21}, m_{22}
   \end{array} \right]
 \f$
*/// ------------------------------------------------------------------ 

typedef struct ex_mat33f_t {
    union {
        struct { 
            float m00, m01, m02;
            float m10, m11, m12;
            float m20, m21, m22;
        }; // end struct
        float m[9];
    };
} ex_mat33f_t;

// ------------------------------------------------------------------ 
/*! 
 @struct ex_mat44f_t
 @details
 
 The data of matrix 4x4 is construct by an union structure with float elements.\n
 The matrix can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c c c }
   m_{00} & m_{01} & m_{02} & m_{03} \\
   m_{10} & m_{11} & m_{12} & m_{13} \\
   m_{20} & m_{21} & m_{22} & m_{23} \\
   m_{30} & m_{31} & m_{32} & m_{33}
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c c c c c c c c c c c c c c c}
   m_{00}, m_{01}, m_{02}, m_{03}, m_{10}, m_{11}, m_{12}, m_{13}, 
   m_{20}, m_{21}, m_{22}, m_{23}, m_{30}, m_{31}, m_{32}, m_{33}
   \end{array} \right]
 \f$
*/// ------------------------------------------------------------------ 

typedef struct ex_mat44f_t {
    union {
        struct { 
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        }; // end struct
        float m[16];
    };
} ex_mat44f_t;

// #################################################################################
#endif // END MATHTYPES_H_1357654396
// #################################################################################


