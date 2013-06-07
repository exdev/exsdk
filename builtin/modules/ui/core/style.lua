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
-- default computed style
-- NOTE: this is not the table for element.style, it is for element.computed_style
-- ------------------------------------------------------------------ 

local default = {
    -- font
    font_style = "normal",
    font_size = 16,
    font_family = { "Bitstream Vera Sans Mono", "Times New Roman" },

    -- margin
    margin_top = 0,
    margin_right = 0,
    margin_bottom = 0,
    margin_left = 0,

    -- padding
    padding_top = 0,
    padding_right = 0,
    padding_bottom = 0,
    padding_left = 0,

    -- border
    border_style = "none",
    border_size_top = 0,
    border_size_right = 0,
    border_size_bottom = 0,
    border_size_left = 0,
    border_color = { 0, 0, 0, 255 },

    -- text
    text_decoration = "none",
    text_overflow = "clip",
    text_outline_thickness = 0,
    text_outline_color = { 0, 0, 0, 255 },
    text_shadow_offset_x = 0,
    text_shadow_offset_y = 0,
    text_shadow_color = { 0, 0, 0, 255 },

    -- size
    width = 0,
    height = 0,
    min_width = 0,
    min_height = 0,
    max_width = 0,
    max_height = 0,

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
__M.setup_font = setup_font

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local calc_content_size = function ( _style, _content, _x, _y, _w )
    local tname = typename (_content)
    if tname == "string" then 
        local font = setup_font(_style)

        TODO ( "return the xoffset and height" )
        return 0,font.height
    elseif tname == "texture" then
        TODO ( "return the xoffset and height" )
    end
end
__M.calc_content_size = calc_content_size

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
