-- ======================================================================================
-- File         : __init__.lua
-- Author       : Wu Jie 
-- Last Change  : 12/10/2013 | 22:14:35 PM | Tuesday,December
-- Description  : 
-- ======================================================================================

-- NOTE: this file will be called in c

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function load_module ( _path )
    local m = ex_c.lua_dofile( string.format( "%s/__module__.lua", _path ) )

    for i=1,#m.files do
        ex_c.lua_dofile( string.format( "%s/%s", _path, m.files[i] ) )
    end

    if m.name ~= nil then
        package.loaded[m.name] = _G[m.name]
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

-- init lpeg
lpeg.locale(lpeg) -- adds locale entries into 'lpeg' table

-- init builtin modules
load_module( "builtin/modules/base" )
load_module( "builtin/modules/ex" )

-- init wiz 
-- load_module( "builtin/modules/ui" )
load_module( "builtin/modules/wiz" )

-- init game engine
-- load_module( "builtin/modules/gamelib" )
