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

-- TODO { 
-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.open ( _self, _path, _name )
    -- wiz_c.open_app(_path)
    wiz.mount( _name )
    wiz.dofile( "wiz://bundle@%s/init.lua", _name ) -- FIXME NOTE: right now we only allow one app running.

    if _self.onInit ~= nil then
        _self.onInit()
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.close ( _self, _name )
    if _self.onClose ~= nil then
        _self.onClose()
    end

    wiz.unmount( _name )
    -- wiz_c.close_app()
end
-- } TODO end 

-- ------------------------------------------------------------------ 
-- Desc: 
-- path can recognized by ex_fsys
-- ------------------------------------------------------------------ 

function wiz.fsysPath (_path)
    local list = _path:split("://",true)
    local proxy, relate_path = table.unpack(list)
    local fpath = _path;

    -- process http, https, .. first 
    if proxy == "wiz" then
        -- for example wiz://foo/bar => __wiz__/foo/bar
        fpath = path.join( "__wiz__", relate_path ), relate_path
    elseif proxy == "http" then
        -- TODO
    end

    return fpath, relate_path;
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- *full*path can recognized by operating system
-- ------------------------------------------------------------------ 

function wiz.osPath (_path)
    local fpath, relate_path = wiz.fsysPath(_path)
    if ex_c.fsys_exists(fpath) then
        return path.join( ex_c.fsys_os_dir(fpath), relate_path )
    end

    error ( "Can't get the real path by %s", _path )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.exists ( _path )
    local fpath = wiz.fsysPath(_path)
    return ex_c.fsys_exists( fpath )
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

    return ex_c.fsys_dofile (fpath)
end
