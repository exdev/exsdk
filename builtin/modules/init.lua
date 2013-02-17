-- ======================================================================================
-- File         : init.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:32:41 PM | Sunday,February
-- Description  : 
-- ======================================================================================

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function module_add ( _module, _moduleName, _fileName )
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
