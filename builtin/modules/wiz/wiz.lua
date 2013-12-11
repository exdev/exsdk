-- ======================================================================================
-- File         : wiz.lua
-- Author       : Wu Jie 
-- Last Change  : 05/07/2013 | 16:56:37 PM | Tuesday,May
-- Description  : 
-- ======================================================================================

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

wiz.platform = ex_c.platform

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

wiz.cwd = ex_c.fsys_app_dir()

-- ------------------------------------------------------------------ 
-- Desc: the arguments will be set by exsdk through __lua_wiz_init()
-- ------------------------------------------------------------------ 

wiz.arguments = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.openApp ( _self, _path )
    wiz_c.open_app(_path)
    wiz.dofile("init.lua") -- FIXME NOTE: right now we only allow one app running.

    if _self.onInit ~= nil then
        _self.onInit()
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.closeApp ( _self )
    if _self.onClose ~= nil then
        _self.onClose()
    end
    wiz_c.close_app()
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- path can recognized by ex_fsys
-- ------------------------------------------------------------------ 

function wiz.fsysPath (_path)
    return path.join("__app__",_path)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- *full*path can recognized by operating system
-- ------------------------------------------------------------------ 

function wiz.sysPath (_path)
    local fpath = wiz.fsysPath(_path)
    if ex_c.fsys_exists(fpath) then
        return path.join( ex_c.fsys_realdir(fpath), _path )
    end

    error ( "Can't get the real path by %s", _path )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.exists ( _path )
    return ex_c.fsys_exists( wiz.fsysPath(_path) )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.filesIn (_path)
    local fpath = wiz.fsysPath(_path)
    if ex_c.fsys_exists(fpath) then
        return ex_c.fsys_files_in(fpath)
    end

    error ( "Can't get the files at path %s", _path )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.dofile (_path)
    local fpath = wiz.fsysPath(_path)
    if ex_c.fsys_exists(fpath) == false then
        error ( "File not found %s", _path )
    end

    return ex_c.dofile (fpath)
end
