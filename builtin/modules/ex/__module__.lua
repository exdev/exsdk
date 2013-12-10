-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

ex = ex or {}

return {
    name = "ex",
    files = {
        -- general
        "defs.lua",

        -- basic classes
        "classes/vec2f.lua",
        "classes/rect.lua",
        "classes/color4f.lua",
        "classes/texture.lua",
        "classes/bitmapfont.lua",
        "classes/font.lua",

        -- paint classes
        "classes/painter.lua",
    }
}
