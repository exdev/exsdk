-- ======================================================================================
-- File         : style.lua
-- Author       : Wu Jie 
-- Last Change  : 05/03/2013 | 16:47:26 PM | Friday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

__M.fonts = {} -- font family -> font

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

-- rect filed
__M.top = 1
__M.right = 2
__M.bottom = 3
__M.left = 4

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local default = {
    -- font
    font_family = { "Bitstream Vera Sans Mono", "Times New Roman" },
    font_style = ui.font_style.normal,
    font_decoration = ui.font_decoration.none,
    font_size = 16,
    font_outline_style = ui.font_outline_style.none,
    font_outline_thickness = 1,

    -- box
    border  = { 0, 0, 0, 0 }, -- top, right, bottom, left. NOTE: -1 means the element is not defined
    margin  = { 0, 0, 0, 0 }, -- top, right, bottom, left. NOTE: -1 means the element is not defined
    padding = { 0, 0, 0, 0 }, -- top, right, bottom, left. NOTE: -1 means the element is not defined

    color   = { 0, 0, 0, 1 }, -- red, gree, blue, alpha.   NOTE: -1 means the element is not defined

    -- size
    width = "auto",
    height = "auto",
    min_width = 1,
    min_height = 1,
}
__M.default = default

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local apply = function ( _elment )
end
__M.apply = apply

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse = function ( _context )
    -- TODO: parse from the context (json or css)? and return a style table.
end
__M.parse = parse

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local draw = function ( _style, _rect, _content )
    local tname = typename (_content)
    if tname == "string" then 
        if _content == "" then 
            return
        end

        local font = nil
        for i=1,#_style.font_family do
            font = ui.style.fonts[_style.font_family[i]]
            if font ~= nil then 
                break 
            end
        end
        assert ( font ~= nil )

        local color = _style.color
        ex.canvas.color = ex.color4f( color[1], color[2], color[3], color[4] )

        local x = _rect[1] + _style.border[ui.style.left] + _style.padding[ui.style.left]
        local y = _rect[2] + _style.border[ui.style.top] + _style.padding[ui.style.top]

        font.size = _style.font_size
        ex.canvas.draw_text( _content, font, x, y ) 
    end
end
__M.draw = draw

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
