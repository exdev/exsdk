-- ======================================================================================
-- File         : wiz.lua
-- Author       : Wu Jie 
-- Last Change  : 05/07/2013 | 16:56:37 PM | Tuesday,May
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
-- Desc: the arguments will be set by exsdk through __lua_wiz_init()
-- ------------------------------------------------------------------ 

local arguments = {}
__M.arguments = arguments

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local open_app = function ( _self, _path )
    wiz_c.open_app(_path)
    wiz.dofile("init.lua") -- FIXME NOTE: right now we only allow one app running.

    if _self.on_init ~= nil then
        _self.on_init()
    end
end
__M.open_app = open_app

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local close_app = function ( _self )
    if _self.on_close ~= nil then
        _self.on_close()
    end
    wiz_c.close_app()
end
__M.close_app = close_app

-- ------------------------------------------------------------------ 
-- Desc: 
-- path can recognized by ex_fsys
-- ------------------------------------------------------------------ 

local function fsys_path (_path)
    return path.join("__app__",_path)
end
__M.fsys_path = fsys_path

-- ------------------------------------------------------------------ 
-- Desc: 
-- *full*path can recognized by operating system
-- ------------------------------------------------------------------ 

local function sys_path (_path)
    local fpath = fsys_path(_path)
    if ex_c.fsys_exists(fpath) then
        return path.join( ex_c.fsys_realdir(fpath), _path )
    end

    error ( "Can't get the real path by %s", _path )
end
__M.sys_path = sys_path

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function exists ( _path )
    return ex_c.fsys_exists( fsys_path(_path) )
end
__M.exists = exists

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function files_in (_path)
    local fpath = fsys_path(_path)
    if ex_c.fsys_exists(fpath) then
        return ex_c.fsys_files_in(fpath)
    end

    error ( "Can't get the files at path %s", _path )
end
__M.files_in = files_in

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function dofile (_path)
    local fpath = fsys_path(_path)
    if ex_c.fsys_exists(fpath) == false then
        error ( "File not found %s", _path )
    end

    return ex_c.lua_dofile (fpath)
end
__M.dofile = dofile

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
