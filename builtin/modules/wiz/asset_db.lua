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

local function get_importer ( _path )
    if project.exists (_path) == false then
        error ( "Can't find file at " .. _path )
    end

    if path.is ( _path, {".bmp", ".jpg", ".png", ".tga"} ) then
        return wiz.texture_importer(_path)
    elseif path.is( _path, {".bft"} ) then
        return wiz.bitmapfont_importer(_path)
    elseif path.is( _path, {".ttf"} ) then
        return wiz.font_importer(_path)
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
