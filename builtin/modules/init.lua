-- ======================================================================================
-- File         : init.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:32:41 PM | Sunday,February
-- Description  : 
-- ======================================================================================

cur_module_path = ""
cur_module_name = ""
cur_module = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function module_add ( _fileName, _subName )
    local mod = cur_module
    if _subName ~= nil then
        mod = cur_module[_subName]
        if mod == nil or type(mod) ~= "table" then 
            mod = {}
            cur_module[_subName] = mod
        end
    end

    local lib = ex_c.lua_dofile ( string.format( "%s%s/%s", 
                                                 cur_module_path,
                                                 cur_module_name, 
                                                 _fileName ) )
    -- for each var in lib, add to _module
    assert ( type(lib) == "table" )
    for k, v in pairs(lib) do
        mod[k] = v
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function module_load ( _path, _moduleName, _isglobal )
    cur_module_path = _path
    cur_module_name = _moduleName

    if _isglobal then
        cur_module = _G
    else
        cur_module = {}
        _G[_moduleName] = cur_module
        package.loaded[_moduleName] = cur_module 
    end

    ex_c.lua_dofile( string.format( "%s%s/__module__.lua", 
                                    _path, 
                                    _moduleName ) )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

-- init lpeg
lpeg.locale(lpeg) -- adds locale entries into 'lpeg' table

-- load the builtin modules
module_load( "builtin/modules/", "base", true )
module_load( "builtin/modules/", "ex" )
module_load( "builtin/modules/", "ui" )
module_load( "builtin/modules/", "editor" )

-- nil the internal value
cur_module_path = nil
cur_module_name = nil
cur_module = nil
