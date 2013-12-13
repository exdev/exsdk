-- ======================================================================================
-- File         : assets.lua
-- Author       : Wu Jie 
-- Last Change  : 11/19/2013 | 10:49:25 AM | Tuesday,November
-- Description  : 
-- ======================================================================================

wiz.assets = wiz.assets or {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local pathToAsset = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function getImporter ( _path )
    if wiz.exists (_path) == false then
        error ( "Can't find file at " .. _path )
    end

    if path.is ( _path, {".bmp", ".jpg", ".png", ".tga"} ) then
        return wiz.textureImporter(_path)
    elseif path.is( _path, {".bft"} ) then
        return wiz.bitmapfontImporter(_path)
    elseif path.is( _path, {".ttf"} ) then
        return wiz.fontImporter(_path)
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.load ( _path )
    -- check if we have cache
    local asset = pathToAsset[_path]
    if asset ~= nil then
        return asset
    end

    -- import asset through path
    print ( "[assets] load file: " .. _path )
    local importer = getImporter(_path)
    if importer then
        asset = importer:exec()
    end

    -- cache asset
    if asset then
        pathToAsset[_path] = asset
    end

    return asset
end

