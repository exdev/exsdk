-- ======================================================================================
-- File         : asset_db.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:35:52 PM | Sunday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local path_to_asset = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function fsys_path (_path)
    return path.join("__project__",_path)
end
__M.fsys_path = fsys_path

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

local function fullpath (_path)
    local fpath = fsys_path(_path)
    if ex_c.fsys_exists(fpath) then
        return path.join( ex_c.fsys_realdir(fpath), _path )
    end

    error ( "Can't get the real path by %s", _path )
end
__M.fullpath = fullpath

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

local function get_importer ( _path )
    if exists (_path) == false then
        error ( "Can't find file at " .. _path )
    end

    if path.is ( _path, {".bmp", ".jpg", ".png", ".tga"} ) then
        return editor.texture_importer(_path)
    elseif path.is( _path, {".bft"} ) then
        return editor.bitmapfont_importer(_path)
    elseif path.is( _path, {".ttf"} ) then
        return editor.font_importer(_path)
    end
end
__M.get_importer = get_importer

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function import ( _path )
    local importer = get_importer(_path)
    local asset = nil
    if importer then
        asset = importer:exec()
    end

    if asset then
        path_to_asset[_path] = asset
    end

    return asset
end
__M.import = import

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function load ( _path )
    local asset = path_to_asset[_path]
    if asset == nil then
        print ( "[asset_db] load file: " .. _path )
        return import(_path)
    end
    return asset
end
__M.load = load

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
