-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

local __M = {}
_G["ex"] = __M
package.loaded["ex"] = __M 

-- generic
__M.path = {}
module_add( __M.path, "ex", "path" )

-- basic module
module_add( __M, "ex", "core" )
module_add( __M, "ex", "debug" )
module_add( __M, "ex", "class" )

-- math module
__M.math = {}
module_add( __M.math, "ex", "math/math" )
module_add( __M.math, "ex", "math/ease" )

-- basic classes
module_add( __M, "ex", "math/vec2f" )

return __M
