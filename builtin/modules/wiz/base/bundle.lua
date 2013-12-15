-- ======================================================================================
-- File         : bundle.lua
-- Author       : Wu Jie 
-- Last Change  : 12/15/2013 | 15:28:16 PM | Sunday,December
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

wiz.bundle = class ({
    __typename = "bundle",

    -- constructor & destructor
    __init = function ( _self, _name, _path )
        checkarg(_name,"string")

        _self.name = _name
        _self.path = _path
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    _pathToAsset = {},
    name = "unknown.com", 
    path = "./",

    --/////////////////////////////////////////////////////////////////////////////
    -- private
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _getImporter = function ( _self, _path )
        if _self:exists (_path) == false then
            error ( "Can't find file at " .. _path )
        end

        if path.is ( _path, {".bmp", ".jpg", ".png", ".tga"} ) then
            return wiz.textureImporter(_self,_path)
        elseif path.is( _path, {".bft"} ) then
            return wiz.bitmapfontImporter(_self,_path)
        elseif path.is( _path, {".ttf"} ) then
            return wiz.fontImporter(_self,_path)
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- public
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    load = function ( _self, _path )
        -- check if we have cache
        local asset = _self._pathToAsset[_path]
        if asset ~= nil then
            return asset
        end

        -- import asset through path
        print ( "[bundle] load file: " .. _path )
        local importer = _self:_getImporter(_path)
        if importer then
            asset = importer:exec()
        end

        -- cache asset
        if asset then
            _self._pathToAsset[_path] = asset
        end

        return asset
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- path can recognized by ex_fsys
    -- ------------------------------------------------------------------ 

    fsysPath = function ( _self, _path )
        return string.format( "__wiz__/%s/%s", _self.name, _path )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- *full*path can recognized by operating system
    -- ------------------------------------------------------------------ 

    osPath = function ( _self, _path )
        local fpath = _self:fsysPath(_path)
        if ex_c.fsys_exists(fpath) then
            return path.join( ex_c.fsys_os_dir(fpath), _path )
        end

        error ( "Can't get the real path by %s", _path )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    exists = function ( _self, _path )
        local fpath = _self:fsysPath(_path)
        return ex_c.fsys_exists( fpath )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    filesIn = function ( _self, _path )
        local fpath = _self:fsysPath(_path)
        if ex_c.fsys_exists(fpath) then
            return ex_c.fsys_files_in(fpath)
        end

        error ( "Can't get the files at path %s", _path )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    dofile = function ( _self, _path )
        -- HACK: I think use _ENV as sandbox would be better
        -- NOTE: overwrite the global bundle here, this will make sure the dofile will get the bundle
        bundle = _self

        local fpath = _self:fsysPath(_path)
        if ex_c.fsys_exists(fpath) == false then
            error ( "File not found %s", _path )
        end

        return ex_c.fsys_dofile (fpath)
    end,
})

