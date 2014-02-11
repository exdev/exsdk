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

function wiz.mount ( path, name, replace )
    local replace = (replace ~= nil) and replace or false
    local realPath = path
    if pathutil.isabsolute(path) == false then
        realPath = os.cwd():join( path )
    end

    local bundle = wiz.bundles[name]

    --
    if bundle ~= nil then
        if replace then
            wiz.unmount(bundle)

            -- do mount
            ex_c.fsys_mount( realPath, string.format("__wiz__/%s",name) )
            bundle = wiz.bundle(name)
            bundle:addPath(realPath)
            wiz.bundles[name] = bundle
        else
            -- do mount
            ex_c.fsys_mount( realPath, string.format("__wiz__/%s",name) )
            bundle:addPath(realPath)
        end
    else
        -- do mount
        ex_c.fsys_mount( realPath, string.format("__wiz__/%s",name) )
        bundle = wiz.bundle( name )
        bundle:addPath(realPath)
        wiz.bundles[name] = bundle
    end

    --
    return bundle
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function wiz.unmount ( bundle )
    checkarg ( bundle, "bundle" )

    -- unmount all
    for i=1,#bundle.paths do
        ex_c.fsys_unmount( bundle.paths[i] )
    end

    wiz.bundles[bundle.name] = nil
end

-- TODO: need a bundle table for this { 
-- -- ------------------------------------------------------------------ 
-- -- Desc: 
-- -- ------------------------------------------------------------------ 

-- function wiz.load ( path )
--     local list = path:split("://",true)
--     local proxy, relate_path = table.unpack(list)
--     local fpath = path;

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
