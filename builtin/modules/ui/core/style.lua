-- ======================================================================================
-- File         : style.lua
-- Author       : Wu Jie 
-- Last Change  : 05/20/2013 | 09:38:01 AM | Monday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- TEMP { 
-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local setup_font = function ( _style )
    local font = nil
    for i=1,#_style.font_family do
        font = ui.fonts[_style.font_family[i]]
        if font ~= nil then 
            break 
        end
    end
    assert ( font ~= nil )

    -- TODO: _style.font_style
    font.size = _style.font_size

    return font
end
-- } TEMP end 

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
    font_size = 16,
    font_style = "normal", -- "normal", "italic", "oblique"

    -- text
    text_decoration = "none", -- "none", "underline", "overline", "through"
    text_outline = { 0, { 0, 0, 0, 255 } }, -- { thickness, color }
    text_shadow = { { 0, 0 }, { 0, 0, 0, 255 } }, -- { offset, color }
    white_space = "normal", -- "normal", "nowrap"
    text_overflow = "clip", -- "clip", "ellipsis" (...)

    -- box { top, right, bottom, left } -- can be number, "auto", "inherit" and nil.
    border  = { 0, 0, 0, 0 },
    margin  = { 0, 0, 0, 0 },
    padding = { 0, 0, 0, 0 },

    -- colors { red, gree, blue, alpha }
    color               = { 0, 0, 0, 255 }, 
    border_color        = { 0, 0, 0, 255 },
    background_color    = { 255, 255, 255, 0 },

    -- size
    width = "auto",
    height = "auto",
    min_width = "auto",
    min_height = "auto",
    max_width = "auto",
    max_height = "auto",

    -- display
    display = "block", -- block, inline-block, inline
    overflow = { "visible", "visible" }, -- "visible", "hidden", "scroll", "auto" 
}
__M.default = default

--/////////////////////////////////////////////////////////////////////////////
-- public functions
--/////////////////////////////////////////////////////////////////////////////


-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local draw = function ( _style, _rect, _content )
    local tname = typename (_content)

    local x, y, w, h = _rect[1], _rect[2], _rect[3], _rect[4]

    x = x + _style.margin[ui.style.left] 
    y = y + _style.margin[ui.style.top] 
    w = w - _style.margin[ui.style.left] - _style.margin[ui.style.right]
    h = h - _style.margin[ui.style.top] - _style.margin[ui.style.bottom] 

    -- draw border
    local color = ex.color4f.from_rgba_8888(_style.border_color)
    ex.canvas.color = color
    ex.canvas.draw_rect_4( x, y, w, h,
                           _style.border[1], _style.border[2], _style.border[3], _style.border[4] ) 

    x = x + _style.border[ui.style.left] + _style.padding[ui.style.left] 
    y = y + _style.border[ui.style.top] + _style.padding[ui.style.top] 
    w = w - _style.border[ui.style.left] - _style.border[ui.style.right] - _style.padding[ui.style.left] - _style.padding[ui.style.right]
    h = h - _style.border[ui.style.top] - _style.border[ui.style.bottom] - _style.padding[ui.style.top] - _style.padding[ui.style.bottom] 

    if tname == "string" then 
        if _content == "" then 
            return
        end

        local color = ex.color4f.from_rgba_8888(_style.color)
        ex.canvas.color = color

        local font = setup_font(_style)
        local text_done = false

        -- draw outline text
        if _style.text_outline[1] > 0 then 
            local color2 = ex.color4f.from_rgba_8888( _style.text_outline[2] )
            ex.canvas.draw_outline_text( _content, font, color, color2, _style.text_outline[1], x, y ) 
            text_done = true
        end

        -- draw shadow text
        local shadow_x, shadow_y = _style.text_shadow[1][1], _style.text_shadow[1][2] 
        if shadow_x > 0 or shadow_y > 0 then 
            local color2 = ex.color4f.from_rgba_8888( _style.text_shadow[2] )
            ex.canvas.draw_shadow_text( _content, font, color, color2, ex.vec2f(shadow_x, shadow_y), x, y ) 
            text_done = true
        end

        -- draw normal text
        if text_done == false then
            ex.canvas.draw_text( _content, font, x, y ) 
        end
    end
end
__M.draw = draw

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local content_height = function ( _style, _content )
    local tname = typename (_content)
    if tname == "string" then 
        local font = setup_font(_style)
        return font.height
    elseif tname == "texture" then
        TODO ( "please implement it" )
    end
end
__M.content_height = content_height

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local content_size = function ( _style, _content )
    local tname = typename (_content)
    if tname == "string" then 
        local font = setup_font(_style)

        TODO ( "please implement it" )
    elseif tname == "texture" then
        TODO ( "please implement it" )
    end
end
__M.content_size = content_size

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
