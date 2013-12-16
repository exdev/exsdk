-- ======================================================================================
-- File         : wiz.lua
-- Author       : Wu Jie 
-- Last Change  : 05/07/2013 | 16:56:37 PM | Tuesday,May
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: the arguments will be set by exsdk through __lua_wiz_init()
-- ------------------------------------------------------------------ 

wiz.arguments = {}
wiz.bundles = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.mount ( _path, _name )
    local path = path.join( os.cwd(), _path )
    local bundle = wiz.bundle( _name, path )

    --
    local old_bundle = wiz.bundles[_name]
    if old_bundle ~= nil then
        wiz.unmount(old_bundle)
    end
    wiz.bundles[_name] = bundle

    --
    ex_c.fsys_mount( path, string.format("__wiz__/%s",_name) )
    return bundle
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.unmount ( _bundle )
    checkarg ( _bundle, "bundle" )
    wiz.bundles[bundle.name] = nil
    ex_c.fsys_unmount( _bundle.path )
end

-- TODO: need a bundle table for this { 
-- -- ------------------------------------------------------------------ 
-- -- Desc: 
-- -- ------------------------------------------------------------------ 

-- function wiz.load ( _path )
--     local list = _path:split("://",true)
--     local proxy, relate_path = table.unpack(list)
--     local fpath = _path;

--     -- process http, https, .. first 
--     if proxy == "wiz" then
--         -- for example wiz://bundlename/foo/bar => __wiz__/bundlename/foo/bar
--         fpath = string.format( "__wiz__/%s", relate_path )
--     elseif proxy == "http" then
--         -- TODO
--     end

--     return fpath, relate_path;
-- end
-- } TODO end 
