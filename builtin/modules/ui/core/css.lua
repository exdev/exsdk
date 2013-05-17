-- ======================================================================================
-- File         : css.lua
-- Author       : Wu Jie 
-- Last Change  : 05/17/2013 | 11:43:30 AM | Friday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

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
    font_style = "normal", -- ui.font.style { normal, italic, oblique }
    font_decoration = "none", -- ui.font.decoration { none, underline, overline, through }
    font_extra_style = "none", -- ui.font.extra_style { none, outline, shadow }
    font_outline_thickness = 1,
    font_shadow_offset = {1,1},

    -- box { top, right, bottom, left } -- can be number, "auto", "inherit" and nil.
    border  = { 0, 0, 0, 0 },
    margin  = { 0, 0, 0, 0 },
    padding = { 0, 0, 0, 0 },

    -- colors { red, gree, blue, alpha }
    color               = { 0, 0, 0, 255 }, 
    border_color        = { 0, 0, 0, 255 },
    background_color    = { 255, 255, 255, 0 },
    font_extra_color    = { 0, 0, 0, 255 }, -- color of font's extra style (outline color or shadow color) 

    -- size
    width = "auto",
    height = "auto",
    min_width = "auto",
    min_height = "auto",
    max_width = "auto",
    max_height = "auto",

    --
    display = "block", -- block, inline-block, inline


    -- functions

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    setup_font = function ( _self )
        local font = nil
        for i=1,#_self.font_family do
            font = ui.fonts[_self.font_family[i]]
            if font ~= nil then 
                break 
            end
        end
        assert ( font ~= nil )

        -- TODO: _self.font_style
        font.size = _self.font_size

        return font
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    draw = function ( _self, _rect, _content )
        local tname = typename (_content)

        local x, y, w, h = _rect[1], _rect[2], _rect[3], _rect[4]

        x = x + _self.margin[ui.css.left] 
        y = y + _self.margin[ui.css.top] 
        w = w - _self.margin[ui.css.left] - _self.margin[ui.css.right]
        h = h - _self.margin[ui.css.top] - _self.margin[ui.css.bottom] 

        -- draw border
        local color = ex.color4f.from_rgba_8888(_self.border_color)
        ex.canvas.color = color
        ex.canvas.draw_rect_4( x, y, w, h,
                               _self.border[1], _self.border[2], _self.border[3], _self.border[4] ) 

        x = x + _self.border[ui.css.left] + _self.padding[ui.css.left] 
        y = y + _self.border[ui.css.top] + _self.padding[ui.css.top] 
        w = w - _self.border[ui.css.left] - _self.border[ui.css.right] - _self.padding[ui.css.left] - _self.padding[ui.css.right]
        h = h - _self.border[ui.css.top] - _self.border[ui.css.bottom] - _self.padding[ui.css.top] - _self.padding[ui.css.bottom] 

        if tname == "string" then 
            if _content == "" then 
                return
            end

            local color = ex.color4f.from_rgba_8888(_self.color)
            ex.canvas.color = color

            local font = _self:setup_font()
            if _self.font_extra_style == "none" then 
                ex.canvas.draw_text( _content, font, x, y ) 

            elseif _self.font_extra_style == "outline" then 
                local color2 = ex.color4f.from_rgba_8888( _self.font_extra_color )
                ex.canvas.draw_outline_text( _content, font, color, color2, _self.font_outline_thickness, x, y ) 

            elseif _self.font_extra_style == "shadow" then 
                local color2 = ex.color4f.from_rgba_8888( _self.font_extra_color )
                ex.canvas.draw_shadow_text( _content, font, color, color2, ex.vec2f(_self.font_shadow_offset[1], _self.font_shadow_offset[2]), x, y ) 

            end
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    content_height = function ( _self, _content )
        local tname = typename (_content)
        if tname == "string" then 
            local font = _self:setup_font()
            return font.height
        elseif tname == "texture" then
            TODO ( "please implement it" )
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    content_size = function ( _self, _content )
        local tname = typename (_content)
        if tname == "string" then 
            local font = _self:setup_font()

            TODO ( "please implement it" )
        elseif tname == "texture" then
            TODO ( "please implement it" )
        end
    end,
}
__M.default = default

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
