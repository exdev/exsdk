-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/05/2013 | 14:43:22 PM | Tuesday,February
-- Description  : 
-- ======================================================================================

wiz = wiz or {}

return {
    name = "wiz",
    files = {
        -- basic
        "base/wiz.lua",
        "base/bundle.lua",

        -- dom
        "dom/node.lua",
        "dom/document.lua",
        "dom/xmlparser.lua",
        "dom/css.lua",

        -- renderer
        "dom/style.lua",
        "dom/renderer.lua",

        -- window
        "base/window.lua",

        -- importer
        "importer/importer.lua",
        "importer/textureImporter.lua",
        "importer/bitmapfontImporter.lua",
        "importer/fontImporter.lua",
    }
}
