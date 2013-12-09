-- ======================================================================================
-- File         : init.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:32:41 PM | Sunday,February
-- Description  : 
-- ======================================================================================

curModulePath = ""
curModuleName = ""
curModule = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function module_add ( _fileName, _subName )
    local mod = curModule
    if _subName ~= nil then
        mod = curModule[_subName]
        if mod == nil or type(mod) ~= "table" then 
            mod = {}
            curModule[_subName] = mod
        end
    end

    local lib = ex_c.lua_dofile ( string.format( "%s%s/%s", 
                                                 curModulePath,
                                                 curModuleName, 
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
    curModulePath = _path
    curModuleName = _moduleName

    if _isglobal then
        curModule = _G
    else
        curModule = {}
        _G[_moduleName] = curModule
        package.loaded[_moduleName] = curModule 
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

-- module_load( "builtin/modules/", "ui" )
module_load( "builtin/modules/", "wiz" )

-- module_load( "builtin/modules/", "gamelib" )

-- nil the internal value
curModulePath = nil
curModuleName = nil
curModule = nil
