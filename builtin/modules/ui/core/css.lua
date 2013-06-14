-- ======================================================================================
-- File         : css.lua
-- Author       : Wu Jie 
-- Last Change  : 05/20/2013 | 09:47:39 AM | Monday,May
-- Description  : 
-- ======================================================================================

-- NOTE: in our css store file, we write this to make sure the order is correct for parser
-- {
--     { "margin", "10px 10px 10px 10px" },
--     { "margin_left", "10px" },
-- }

-- NOTE: why I use function parser instead of table parser, is because I need to make sure the define order so that
--       the last defined item can overwrite the previours value

-- table parser (not use)
-- ui.css {
--     font_size = "20px",
--     text_outline =  "1px #000",
--     color = "#0f0",
--     margin = "0px 0px 0px 10px",
-- }

-- function parser ( we choose this style! )
-- ui.css.build()
--       .font_size("20px")
--       .text_outline("1px #000")
--       .color("#0f0")
--       .margin("0px 0px 0px 10px")
--       .done()

local __M = {}
local __style = nil

--/////////////////////////////////////////////////////////////////////////////
-- local
--/////////////////////////////////////////////////////////////////////////////

local def = function ( _prop_name, _parse_func, _options )
    __M[_prop_name] = function ( _text )
        _parse_func ( __style, _prop_name, _text, _options )
        return __M
    end
end

local def_group = function ( _prop_name, _group )
    __M[_prop_name] = function ( _text )
        local r1 = 1
        local r2 = _text:find( " " )
        local text_el = ""

        for i=1,#_group do
            local p = _group[i]

            if i ~= #_group and r2 ~= nil then 
                text_el = _text:sub( r1, r2-1 )
            else
                text_el = _text:sub( r1 )
            end

            local parse_func = __M[p]
            if parse_func and parse_func (text_el) then
                if r2 ~= nil then 
                    r1 = r2+1
                    r2 = _text:find( " ", r1 )
                end
            end
        end

        return __M
    end
end

--/////////////////////////////////////////////////////////////////////////////
-- parse atomic
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_option = function ( _style, _prop_name, _text, _options )
    if _options ~= nil then
        local valid_option = false
        local has_image_path = false
        local has_size = false

        --
        for i=1,#_options do 
            local opt = _options[i] 
            if opt == _text then
                valid_option = true
                break
            elseif opt == "image_path" then 
                has_image_path = true
            elseif opt == "size" then 
                has_size = true
            end
        end

        --
        if valid_option == false then
            if has_image_path then
                if path.is ( _text, {".bmp", ".jpg", ".png", ".tga"} ) then
                    valid_option = true
                end
            elseif has_size then
                -- TODO:
            end
        end

        --
        if valid_option == false then 
            return false
        end
    end

    _style[_prop_name] = _text
    return true
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_size = function ( _style, _prop_name, _text, _options )
    local has_inherit = false
    local has_auto = false
    local has_none = false
    local has_percent = false
    local has_px = false

    --
    for i=1,#_options do
        local opt = _options[i]

        if opt == "inherit" then
            has_inherit = true
        elseif opt == "auto" then
            has_auto = true
        elseif opt == "none" then
            has_none = true
        elseif opt == "%" then
            has_percent = true
        elseif opt == "px" then
            has_px = true
        end
    end

    -- inherit or auto
    if has_inherit and _text == "inherit" then
        _style[_prop_name] = { "inherit" }
        return true
    elseif has_auto and _text == "auto" then
        _style[_prop_name] = { "auto" }
        return true
    elseif has_none and _text == "none" then
        _style[_prop_name] = { "none" }
        return true
    end

    -- px or %
    local len = _text:len()
    if has_px and _text:ncmp("px", len-2, 2) then
        _style[_prop_name] = { "px", tonumber( _text:sub( 1, len-2 ) )  }
        return true
    elseif has_percent and _text:ncmp("%", len-1, 1) then
        _style[_prop_name] = { "%", tonumber( _text:sub( 1, len-1 ) )  }
        return true
    end

    -- not a size
    return false
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_color = function ( _style, _prop_name, _text, _options )
    -- #f00, #ff0000
    if _text:ncmp("#",0,1) then
        local v = _text:sub(2)
        if #v == 3 then
            local r = _text:sub(2,2)
            local g = _text:sub(3,3)
            local b = _text:sub(4,4)
            _style[_prop_name] = { tonumber(r..r,16), tonumber(g..g,16), tonumber(b..b,16), 255 }
            return true
        elseif #v == 6 then
            local r = _text:sub(2,3)
            local g = _text:sub(4,5)
            local b = _text:sub(6,7)
            _style[_prop_name] = { tonumber(r,16), tonumber(g,16), tonumber(b,16), 255 }
            return true
        else
            return false
            -- error ( "invalid color value " .. _text )
        end

    -- rgb or rgba
    elseif _text:ncmp("rgb",0,3) then
        local list = {}
        for w in string.gmatch(_text, "%d+") do
            table.add ( list, w )
        end
        local r = list[1] or 255
        local g = list[2] or 255
        local b = list[3] or 255
        local a = list[4] or 255
        _style[_prop_name] = { r, g, b, a }
        return true
    end

    return false
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_font_family = function ( _style, _prop_name, _text, _options )
    local list = string.split( _text, "," )
    if #list == 0 then return end
    for i,v in ipairs(list) do 
        list[i] = string.trim(v)
    end

    _style[_prop_name] = list
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_offset_rect = function ( _style, _prop_name, _text, _options )
    local list = string.split( _text, " " )
    if #list == 0 then return end

    local top = list[1]
    local right = list[2] or top
    local bottom = list[3] or top
    local left = (list[4] or right) or top

    parse_size( _style, _prop_name .. "_top", top, _options )
    parse_size( _style, _prop_name .. "_right", right, _options )
    parse_size( _style, _prop_name .. "_bottom", bottom, _options )
    parse_size( _style, _prop_name .. "_left", left, _options )
end

--/////////////////////////////////////////////////////////////////////////////
-- build and done
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local build = function ( _style ) 
    assert ( __style == nil, "You didn't call ui.css.done()." )
    __style = _style or {}
    return __M
end
__M.build = build

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local done = function () 
    assert ( __style ~= nil, "You didn't call ui.css.build()." )
    local style = __style
    __style = nil

    return style
end
__M.done = done

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

-- font
def_group ( "font", {
    "font_style",
    "font_size",
    "font_family",
} )
def ( "font_style",  parse_option, { "normal", "italic", "oblique", "inherit" } )
-- def ( "font_variant",  parse_option, { "normal", "small-cap", "inherit" } ) -- TODO? I don't think we need this
-- def ( "font_weight",  parse_font_weight ) -- TODO? must know how to setup bold or other font in FreeType
def ( "font_size",  parse_size, { "inherit", "px", "%" } )
def ( "font_family",  parse_font_family )

-- margin
def ( "margin",  parse_offset_rect, { "inherit", "auto", "px", "%" } )
def ( "margin_top",     parse_size, { "inherit", "auto", "px", "%" } )
def ( "margin_right",   parse_size, { "inherit", "auto", "px", "%" } )
def ( "margin_bottom",  parse_size, { "inherit", "auto", "px", "%" } )
def ( "margin_left",    parse_size, { "inherit", "auto", "px", "%" } )

-- padding
def ( "padding",  parse_offset_rect, { "inherit", "px", "%" } )
def ( "padding_top",     parse_size, { "inherit", "px", "%" } )
def ( "padding_right",   parse_size, { "inherit", "px", "%" } )
def ( "padding_bottom",  parse_size, { "inherit", "px", "%" } )
def ( "padding_left",    parse_size, { "inherit", "px", "%" } )

-- border
def_group ( "border", {
    "border_size",
    "border_style",
    "border_color",
} )
def ( "border_size",  parse_offset_rect, { "inherit", "px", "%" } )
def ( "border_size_top",     parse_size, { "inherit", "px", "%" } )
def ( "border_size_right",   parse_size, { "inherit", "px", "%" } )
def ( "border_size_bottom",  parse_size, { "inherit", "px", "%" } )
def ( "border_size_left",    parse_size, { "inherit", "px", "%" } )
def ( "border_style",  parse_option, { "none", "solid", "image_path" } ) -- can be solid, image_icon_path
def ( "border_color",  parse_color )

-- text
def ( "text_decoration",  parse_option, { "none", "underline", "overline", "through", "inherit" } )
def ( "text_overflow", parse_option, { "clip", "ellipsis" } )

def_group ( "text_outline", {
    "text_outline_thickness",
    "text_outline_color",
} )
def ( "text_outline_thickness", parse_size, { "inherit", "px", "%" } )
def ( "text_outline_color", parse_color )

def_group ( "text_shadow", {
    "text_shadow_offset_x",
    "text_shadow_offset_y",
    "text_shadow_color",
} )
def ( "text_shadow_offset_x", parse_size, { "inherit", "px", "%" } )
def ( "text_shadow_offset_y", parse_size, { "inherit", "px", "%" } )
def ( "text_shadow_color", parse_color )

-- size
def ( "width",      parse_size, { "inherit", "auto", "px", "%" } )
def ( "height",     parse_size, { "inherit", "auto", "px", "%" } )
def ( "min_width",  parse_size, { "inherit", "px", "%" } )
def ( "min_height", parse_size, { "inherit", "px", "%" } )
def ( "max_width",  parse_size, { "inherit", "none", "px", "%" } )
def ( "max_height", parse_size, { "inherit", "none", "px", "%" } )

-- 
-- TODO { 
-- def ( "overflow",  parse_option, { "visible", "hidden", "scroll", "auto", "inherit" } )
-- def ( "overflow_x",  parse_option, { "visible", "hidden", "scroll", "auto", "inherit" } )
-- def ( "overflow_y",  parse_option, { "visible", "hidden", "scroll", "auto", "inherit" } )
-- } TODO end 

-- background
def ( "background_color",  parse_color )

-- position
def ( "position",  parse_option, { "static", "absolute", "fixed", "relative", "inherit" } )
def ( "left",   parse_size, { "inherit", "auto", "px", "%" } )
def ( "right",  parse_size, { "inherit", "auto", "px", "%" } )
def ( "top",    parse_size, { "inherit", "auto", "px", "%" } )
def ( "bottom", parse_size, { "inherit", "auto", "px", "%" } )

-- misc
def ( "white_space",  parse_option, { "normal", "nowrap", "inherit" } )
def ( "color",  parse_color )
def ( "display",  parse_option, { "block", "inline-block", "inline", "inherit" } )

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
