-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/05/2013 | 14:43:22 PM | Tuesday,February
-- Description  : 
-- ======================================================================================

local function module_add ( _module, _moduleName, _fileName )
    local lib = dofile ( string.format( "builtin/modules/%s/%s.lua", 
                                        _moduleName, 
                                        _fileName ) )
    -- for each var in lib, add to _module
    assert ( type(lib) == "table" )
    for k, v in pairs(lib) do
        _module[k] = v
    end
end

local __M = {}
_G["ex"] = __M
package.loaded["ex"] = __M 

-- module_add( __M, "ex", "core" )
module_add( __M, "ex", "debug" )
module_add( __M, "ex", "class" )
module_add( __M, "ex", "math/vec2f" )

__M.math = {}
module_add( __M.math, "ex", "math/math" )
module_add( __M.math, "ex", "math/ease" )

return __M
