-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/05/2013 | 14:43:22 PM | Tuesday,February
-- Description  : 
-- ======================================================================================

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function module_add ( _module, _moduleName, _fileName )
    -- NOTE: in MacOSX, fopen() can not open short path unless it is an app package
    local lib = dofile ( string.format( ex_c.fsys_app_dir() .. "builtin/modules/%s/%s.lua", 
                                        _moduleName, 
                                        _fileName ) )
    -- for each var in lib, add to _module
    assert ( type(lib) == "table" )
    for k, v in pairs(lib) do
        _module[k] = v
    end
end

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local __M = {}
_G["ex"] = __M
package.loaded["ex"] = __M 

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
