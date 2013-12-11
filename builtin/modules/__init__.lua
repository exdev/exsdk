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
    -- NOTE: you can not use path.join here, because the base module is not loaded yet
    local path = string.format( "%s/%s", ex_c.cwd, _path )
    local m = ex_c.dofile( string.format( "%s/__module__.lua", path ) )

    for i=1,#m.files do
        ex_c.dofile( string.format( "%s/%s", path, m.files[i] ) )
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
load_module( "base" )
load_module( "ex" )

-- init wiz 
-- load_module( "ui" )
load_module( "wiz" )

-- init game engine
-- load_module( "gamelib" )
