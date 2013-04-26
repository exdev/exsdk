-- ======================================================================================
-- File         : app.lua
-- Author       : Wu Jie 
-- Last Change  : 02/18/2013 | 11:22:52 AM | Monday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local platform = ex_c.platform
__M.platform = platform

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local cwd = ex_c.fsys_app_dir()
__M.cwd = cwd

-- ------------------------------------------------------------------ 
-- Desc: the arguments will be set by exsdk through ex_lua_init_app_table()
-- ------------------------------------------------------------------ 

local arguments = {}
__M.arguments = arguments

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local open_project = function ( _self, _path )
    -- if we have project open, close it first
    if project.cwd ~= nil and project.cwd ~= "" then
        app:close_project ( project.cwd )
    end

    ex_c.open_project(_path)
    project.cwd = ex_c.fsys_writedir()

    if project.exists("init.lua") then
        ex_c.lua_dofile ( project.fsys_path("init.lua") )
    end

    if _self.on_init ~= nil then
        _self.on_init()
    end
end
__M.open_project = open_project

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local close_project = function ( _self )
    if _self.on_close ~= nil then
        _self.on_close()
    end
    ex_c.close_project()
    project.cwd = ""
end
__M.close_project = close_project

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
