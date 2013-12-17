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
        "dom/element.lua",
        "dom/document.lua",
        "dom/parser.lua",

        -- window
        "base/window.lua",

        -- importer
        "importer/importer.lua",
        "importer/textureImporter.lua",
        "importer/bitmapfontImporter.lua",
        "importer/fontImporter.lua",
    }
}
