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

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local default = {
    -- font
    font_style = "normal",
    font_size = { "px", 16 },
    font_family = { "Bitstream Vera Sans Mono", "Times New Roman" },

    -- margin
    margin_top = { "px", 0 },
    margin_right = { "px", 0 },
    margin_bottom = { "px", 0 },
    margin_left = { "px", 0 },

    -- padding
    padding_top = { "px", 0 },
    padding_right = { "px", 0 },
    padding_bottom = { "px", 0 },
    padding_left = { "px", 0 },

    -- border
    border_style = "none",
    border_size_top = { "px", 0 },
    border_size_right = { "px", 0 },
    border_size_bottom = { "px", 0 },
    border_size_left = { "px", 0 },
    border_color = { 0, 0, 0, 255 },

    -- text
    text_decoration = "none",
    text_overflow = "clip",
    text_outline_thickness = { "px", 0 },
    text_outline_color = { 0, 0, 0, 255 },
    text_shadow_offset_x = { "px", 0 },
    text_shadow_offset_y = { "px", 0 },
    text_shadow_color = { 0, 0, 0, 255 },

    -- size
    width = { "auto" },
    height = { "auto" },
    min_width = { "auto" },
    min_height = { "auto" },
    max_width = { "auto" },
    max_height = { "auto" },

    -- background
    background_color = { 255, 255, 255, 0 },

    -- misc
    white_space = "normal",
    color = { 0, 0, 0, 255 },
    display = "block",
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

    local x, y, w, h 
        = _rect[1], _rect[2], _rect[3], _rect[4]

    local margin_R, margin_T, margin_B, margin_L 
        = _style.margin_right, _style.margin_top, _style.margin_bottom, _style.margin_left

    local border_R, border_T, border_B, border_L 
        = _style.border_size_right, _style.border_size_top, _style.border_size_bottom, _style.border_size_left

    local padding_R, padding_T, padding_B, padding_L 
        = _style.padding_right, _style.padding_top, _style.padding_bottom, _style.padding_left


    x = x + margin_L
    y = y + margin_T
    w = w - margin_L - margin_R
    h = h - margin_T - margin_B

    -- draw border
    local color = ex.color4f.from_rgba_8888(_style.border_color)
    ex.canvas.color = color
    ex.canvas.draw_rect_4( x, y, w, h,
                           border_T, border_R, border_B, border_L ) 

    x = x + border_L + padding_L
    y = y + border_T + padding_T
    w = w - border_L - border_R - padding_L - padding_R
    h = h - border_T - border_B - padding_T - padding_B

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
