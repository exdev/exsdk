-- ======================================================================================
-- File         : assets.lua
-- Author       : Wu Jie 
-- Last Change  : 11/19/2013 | 10:49:25 AM | Tuesday,November
-- Description  : 
-- ======================================================================================

local __M = {}

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
__M.getImporter = getImporter

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function import ( _path )
    local importer = getImporter(_path)
    local asset = nil
    if importer then
        asset = importer:exec()
    end

    if asset then
        pathToAsset[_path] = asset
    end

    return asset
end
__M.import = import

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function load ( _path )
    local asset = pathToAsset[_path]
    if asset ~= nil then
        return asset
    end

    --
    print ( "[assets] load file: " .. _path )
    asset = import(_path)

    return asset
end
__M.load = load

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
