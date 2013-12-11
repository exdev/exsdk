-- ======================================================================================
-- File         : wiz.lua
-- Author       : Wu Jie 
-- Last Change  : 05/07/2013 | 16:56:37 PM | Tuesday,May
-- Description  : 
-- ======================================================================================

local __M = wiz

--/////////////////////////////////////////////////////////////////////////////
-- events
--/////////////////////////////////////////////////////////////////////////////

-- onInit
-- onClose
-- onExit

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

local openApp = function ( _self, _path )
    wiz_c.open_app(_path)
    wiz.dofile("init.lua") -- FIXME NOTE: right now we only allow one app running.

    if _self.onInit ~= nil then
        _self.onInit()
    end
end
__M.openApp = openApp

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local closeApp = function ( _self )
    if _self.onClose ~= nil then
        _self.onClose()
    end
    wiz_c.close_app()
end
__M.closeApp = closeApp

-- ------------------------------------------------------------------ 
-- Desc: 
-- path can recognized by ex_fsys
-- ------------------------------------------------------------------ 

local function fsysPath (_path)
    return path.join("__app__",_path)
end
__M.fsysPath = fsysPath

-- ------------------------------------------------------------------ 
-- Desc: 
-- *full*path can recognized by operating system
-- ------------------------------------------------------------------ 

local function sysPath (_path)
    local fpath = fsysPath(_path)
    if ex_c.fsys_exists(fpath) then
        return path.join( ex_c.fsys_realdir(fpath), _path )
    end

    error ( "Can't get the real path by %s", _path )
end
__M.sysPath = sysPath

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function exists ( _path )
    return ex_c.fsys_exists( fsysPath(_path) )
end
__M.exists = exists

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function filesIn (_path)
    local fpath = fsysPath(_path)
    if ex_c.fsys_exists(fpath) then
        return ex_c.fsys_files_in(fpath)
    end

    error ( "Can't get the files at path %s", _path )
end
__M.filesIn = filesIn

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function dofile (_path)
    local fpath = fsysPath(_path)
    if ex_c.fsys_exists(fpath) == false then
        error ( "File not found %s", _path )
    end

    return ex_c.dofile (fpath)
end
__M.dofile = dofile

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
