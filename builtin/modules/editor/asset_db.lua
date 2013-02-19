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

local function exists ( _path )
    return ex_c.fsys_exists(_path)
end
__M.exists = exists

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function fullpath (_path)
    return path.join( path.translate(app.data_path,"/"), _path )
end
__M.fullpath = fullpath

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function get_importer ( _path )
    if exists (_path) == false then
        error ( "Can't find file at " .. _path )
    end

    if path.is ( _path, {".bmp", ".jpg", ".png", ".tga"} ) then
        return editor.texture_importer(_path)
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

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
