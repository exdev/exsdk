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
    __init = function ( self, name, path )
        checkarg(name,"string")
        checkarg(path,"string")

        self.name = name
        self.path = path
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

    _getImporter = function ( self, path )
        if self:exists (path) == false then
            error ( "Can't find file at " .. path )
        end

        if pathutil.is( path, {".bmp", ".jpg", ".png", ".tga"} ) then
            return wiz.textureImporter(self,path)
        elseif pathutil.is( path, {".bft"} ) then
            return wiz.bitmapfontImporter(self,path)
        elseif pathutil.is( path, {".ttf"} ) then
            return wiz.fontImporter(self,path)
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- public
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    load = function ( self, path )
        -- check if we have cache
        local asset = self._pathToAsset[path]
        if asset ~= nil then
            return asset
        end

        -- import asset through path
        print ( "[bundle] load file: " .. path )
        local importer = self:_getImporter(path)
        if importer then
            asset = importer:exec()
        end

        -- cache asset
        if asset then
            self._pathToAsset[path] = asset
        end

        return asset
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- path can recognized by ex_fsys
    -- ------------------------------------------------------------------ 

    fsysPath = function ( self, path )
        return string.format( "__wiz__/%s/%s", self.name, path )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- *full*path can recognized by operating system
    -- ------------------------------------------------------------------ 

    osPath = function ( self, path )
        local fpath = self:fsysPath(path)
        if ex_c.fsys_exists(fpath) then
            return ex_c.fsys_os_dir(fpath):join(path)
        end

        error ( "Can't get the real path by %s", path )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    exists = function ( self, path )
        local fpath = self:fsysPath(path)
        return ex_c.fsys_exists( fpath )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    filesIn = function ( self, path )
        local fpath = self:fsysPath(path)
        if ex_c.fsys_exists(fpath) then
            return ex_c.fsys_files_in(fpath)
        end

        error ( "Can't get the files at path %s", path )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    dofile = function ( self, path )
        -- HACK: I think use _ENV as sandbox would be better
        -- NOTE: overwrite the global bundle here, this will make sure the dofile will get the bundle
        bundle = self

        local fpath = self:fsysPath(path)
        if ex_c.fsys_exists(fpath) == false then
            error ( "File not found %s", path )
        end

        return ex_c.fsys_dofile (fpath)
    end,
})

