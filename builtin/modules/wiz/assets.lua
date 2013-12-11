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

function wiz.assets.getImporter ( _path )
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

function wiz.assets.import ( _path )
    local importer = wiz.assets.getImporter(_path)
    local asset = nil
    if importer then
        asset = importer:exec()
    end

    if asset then
        pathToAsset[_path] = asset
    end

    return asset
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.assets.load ( _path )
    local asset = pathToAsset[_path]
    if asset ~= nil then
        return asset
    end

    --
    print ( "[assets] load file: " .. _path )
    asset = wiz.assets.import(_path)

    return asset
end

