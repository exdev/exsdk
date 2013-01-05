// ======================================================================================
// File         : mathdef.h
// Author       : Wu Jie 
// Last Change  : 11/25/2010 | 16:49:41 PM | Thursday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATHDEF_H_1290674983
#define MATHDEF_H_1290674983
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
//  config macros
///////////////////////////////////////////////////////////////////////////////

//! @addtogroup Math
//! @{

// ------------------------------------------------------------------
/*!
 @def EX_MATRIX_ORDER
 @details

 Set the matrix order to column major or row major. 
 @par options:
 - EX_MATRIX_COLUMN_MAJOR (default)
 - EX_MATRIX_ROW_MAJOR

 @par EX_MATRIX_COLUMN_MAJOR:
 Each row of the matrix is stored in a single constant register 
 the column major matrix can multiply by column easily, as vec * r1

 Layer out for register pack:

     \f$
       \left|\begin{array}{ c c c c }
       r0 & r1 & r2 & r3 \\
       -- & -- & -- & -- \\
       m_{00} & m_{01} & m_{02} & m_{03} \\
       m_{10} & m_{11} & m_{12} & m_{13} \\
       m_{20} & m_{21} & m_{22} & m_{23} \\
       m_{30} & m_{31} & m_{32} & m_{33}
       \end{array} \right|
     \f$

 Layer out for geometry meanning:

     \f$
       \left|\begin{array}{ c c c c c }
       I & | & m_{00} & m_{01} & m_{02} & m_{03} \\
       J & | & m_{10} & m_{11} & m_{12} & m_{13} \\
       K & | & m_{20} & m_{21} & m_{22} & m_{23} \\
       T & | & m_{30} & m_{31} & m_{32} & m_{33}
       \end{array} \right|
     \f$

 When we doing a transform calculation with column major matrix, 
 the transform order is from left to right as below:
 @code
 vec * mat1 * mat2
 @endcode

 @par EX_MATRIX_ROW_MAJOR:
 Each row of the matrix is stored in a single constant register
 the row major matrix can multiply by row easily, as r1 * vec

 Layer out for register pack:

     \f$
       \left|\begin{array}{ c c c c c }
       r0 & | & m_{00} & m_{01} & m_{02} & m_{03} \\
       r1 & | & m_{10} & m_{11} & m_{12} & m_{13} \\
       r3 & | & m_{20} & m_{21} & m_{22} & m_{23} \\
       r3 & | & m_{30} & m_{31} & m_{32} & m_{33}
       \end{array} \right|
     \f$

 Layer out for geometry meanning:

     \f$
       \left|\begin{array}{ c c c c }
       I & J & K & T \\
       -- & -- & -- & -- \\
       m_{00} & m_{01} & m_{02} & m_{03} \\
       m_{10} & m_{11} & m_{12} & m_{13} \\
       m_{20} & m_{21} & m_{22} & m_{23} \\
       m_{30} & m_{31} & m_{32} & m_{33}
       \end{array} \right|
     \f$
      
 When we doing a transform calculation with column major matrix, 
 the transform order is from left to right as below:
 @code
 mat2 * mat1 * vec 
 @endcode

 @warning
 Don't modify this macro, currently the engine just support column major calculate
*/// ------------------------------------------------------------------

#define EX_MATRIX_COLUMN_MAJOR 1
#define EX_MATRIX_ROW_MAJOR    2

#define EX_MATRIX_ORDER EX_MATRIX_COLUMN_MAJOR

// ------------------------------------------------------------------
/*!
 @def EX_MULTIPLY_ORDER

 The EX_MULTIPLY_ORDER defines the order to transform a vector by multiplying.
 You needn't define the macro, it depends on the order of the matrix.
 if the matrix is column major, the multiply order is left to right.
 if the matrix is row major, the multiply order is right to left.

 @par EX_MULTIPLY_LEFT_TO_RIGHT
 @code
 vec_b = vec_a * mat1 * mat2 * mat3 * ...
 vec_b = vec_a * quad1 * quad2 * quad3 * ...
 @endcode

 vector express in math:

 \f$
   vec = 
   \left[\begin{array}{ c c c c c }
   v_{0} & v_{1} & v_{2} & v_{3} & ...
   \end{array} \right]
 \f$

 @par EX_MULTIPLY_RIGHT_TO_LEFT
 @code
 vRot = ... * mat3 * mat2 * mat1 * vec
 vRot = ... * quad3 * quad2 * quad1 * vec
 @endcode

 vector express in math:

 \f$
   vec = 
   \left[\begin{array}{ c }
   v_{0} \\
   v_{1} \\
   v_{2} \\
   v_{3} \\
   ...
   \end{array} \right]
 \f$
*/// ------------------------------------------------------------------

#define EX_MULTIPLY_LEFT_TO_RIGHT 1
#define EX_MULTIPLY_RIGHT_TO_LEFT 2

#if ( EX_MATRIX_ORDER == EX_MATRIX_COLUMN_MAJOR )
    #define EX_MULTIPLY_ORDER EX_MULTIPLY_LEFT_TO_RIGHT
#elif ( EX_MATRIX_ORDER == EX_MATRIX_ROW_MAJOR ) 
    #define EX_MULTIPLY_ORDER EX_MULTIPLY_RIGHT_TO_LEFT
#endif

// ------------------------------------------------------------------
/*!
 @def EX_COORDINATE_SYSTEM
 defines which coordinate system we will use.
 @par options:
 - EX_COORDINATE_LEFT_HANDED (default)
 - EX_COORDINATE_RIGHT_HANDED

 @par EX_COORDINATE_LEFT_HANDED
    
 @code
          Y 
           ^   Z
           | / 
           |/
            -----> X      
 @endcode

 @par EX_COORDINATE_RIGHT_HANDED

 @code
          Y 
           ^   
           |  
           |
          / -----> X      
         /
       Z
 @endcode
*/// ------------------------------------------------------------------

#define EX_COORDINATE_LEFT_HANDED  1
#define EX_COORDINATE_RIGHT_HANDED 2

#define EX_COORDINATE_SYSTEM EX_COORDINATE_LEFT_HANDED

// ------------------------------------------------------------------
/*!
 @def EX_ANGLE_UNIT
 @par options:
 - EX_ANGLE_RADIANS (default)
 - EX_ANGLE_DEGREE

 @par EX_ANGLE_RADIANS
 use radians express angle, range at [ 0.0 - 2pi ]

 @par EX_ANGLE_DEGREE
 use degree express angle, range at [ 0.0 - 360.0 ]

 @note
 cause most c/cpp math function like sinf,cosf... use radians as input value. 
 if we use the degree, then we need one more calculation to transform the input.
*/// ------------------------------------------------------------------

#define EX_ANGLE_RADIANS 1
#define EX_ANGLE_DEGREE  2

#define EX_ANGLE_UNIT EX_ANGLE_RADIANS

// ------------------------------------------------------------------
/*!
 @def EX_ROTATE_METHOD
 @par options:
 - EX_ROTATE_CW (default)
 - EX_ROTATE_CCW

 @par EX_ROTATE_CW 

 Angles are measured clockwise when looking along the rotation axis toward the "origin".
 As know as Left-Hand Rotate ( use thumb as axis, other finger as rotation )

 @par EX_ROTATE_CCW 

 Angles are measured counter clockwise when looking along the rotation axis toward the "origin".
 As know as Right-Hand Rotate ( use thumb as axis, other finger as rotation )
*/// ------------------------------------------------------------------

#define EX_ROTATE_CW   1
#define EX_ROTATE_CCW  2

#define EX_ROTATE_METHOD EX_ROTATE_CW

// ------------------------------------------------------------------
/*
            Operation       |  Result
   -------------------------+------------
             n / +-infinity |     0
              +-nonzero / 0 | +-infinity
    +-infinity * +-infinity | +-infinity
        infinity + infinity |   infinity
        infinity - infinity |    NaN
    +-infinity / +-infinity |    NaN
             +-infinity * 0 |    NaN
                  +-0 / +-0 |    NaN
*/// ------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
//  value defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
/*!
 @def EX_PI
 @details pi 

 @def EX_INV_PI
 @details 1/pi 

 @def EX_TWO_PI
 @details 2*pi 

 @def EX_HALF_PI
 @details pi/2 
*/// ------------------------------------------------------------------

#define EX_PI               (3.1415926535897932)
#define EX_INV_PI			(0.31830988618)
#define EX_TWO_PI           (6.2831853071795864)
#define EX_HALF_PI			(1.57079632679)

// ------------------------------------------------------------------
/*!
 @def EX_MIN(_a,_b)
 @details get minimux value of a and b.

 @def EX_MAX(_a,_b)
 @details get maximux value of a and b.
*/// ------------------------------------------------------------------

#define EX_MIN(_a,_b) (_a) < (_b) ? (_a) : (_b)
#define EX_MAX(_a,_b) (_a) > (_b) ? (_a) : (_b)

// ------------------------------------------------------------------ 
/*! 
 @def EX_SET_NAN(_v)
 set value to NaN
*/// ------------------------------------------------------------------ 

#define EX_SET_NAN(_v) (*(uint32*)&(_v)=EX_UINT32_MAX)

// ------------------------------------------------------------------ 
/*! 
 @def EX_IS_NAN(_v)
 check if the value is NaN
*/// ------------------------------------------------------------------ 

#define EX_IS_NAN(_v) ((_v)!=(_v))

//! @}

// #################################################################################
#endif // END MATHDEF_H_1290674983
// #################################################################################


