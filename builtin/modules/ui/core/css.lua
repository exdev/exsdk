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

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_option = function ( _style, _prop_name, _text, _options )
    local valid_option = false
    for i=1,#_options do 
        if _options[i] == _text then
            valid_option = true
            break
        end
    end

    assert ( valid_option, "Can't find the option " .. _text )
    _style[_prop_name] = _text
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_size = function ( _style, _prop_name, _text, _options )
    if _text == "inherit" then
        _style[_prop_name] = { "inherit" }
        return
    elseif _text == "auto" then
        _style[_prop_name] = { "auto" }
        return
    end

    local len = _text:len()
    if _text:ncmp("px", len-2, 2) then
        _style[_prop_name] = { "px", tonumber( _text:sub( 1, len-2 ) )  }
    elseif _text:ncmp("%", len-1, 1) then
        _style[_prop_name] = { "%", tonumber( _text:sub( 1, len-1 ) )  }
    end
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
        elseif #v == 6 then
            local r = _text:sub(2,3)
            local g = _text:sub(4,5)
            local b = _text:sub(6,7)
            _style[_prop_name] = { tonumber(r,16), tonumber(g,16), tonumber(b,16), 255 }
        else
            error ( "invalid color value " .. _text )
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
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_offset_rect = function ( _style, _prop_name, _text, _options )
    local list = {}
    for w in string.gmatch(_text, "%S+") do
        table.add ( list, w )
    end
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

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_font_family = function ( _style, _prop_name, _text, _options )
    local list = {}
    for w in string.gmatch(_text, "[^,]+") do
        table.add ( list, w )
    end
    if #list == 0 then return end
    _style[_prop_name] = list
end

--/////////////////////////////////////////////////////////////////////////////
-- functions
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

-- def ( "font",  parse_font )
def ( "font_family",  parse_font_family )
def ( "font_size",  parse_size )
def ( "font_style",  parse_option, { "normal", "italic", "oblique", "inherit" } )

def ( "margin",  parse_offset_rect )
def ( "margin_left",    parse_size )
def ( "margin_right",   parse_size )
def ( "margin_top",     parse_size )
def ( "margin_bottom",  parse_size )

def ( "padding",  parse_offset_rect )
def ( "padding_left",    parse_size )
def ( "padding_right",   parse_size )
def ( "padding_top",     parse_size )
def ( "padding_bottom",  parse_size )

def ( "border",  parse_offset_rect )
def ( "border_left",    parse_size )
def ( "border_right",   parse_size )
def ( "border_top",     parse_size )
def ( "border_bottom",  parse_size )
def ( "border_color",  parse_color )

def ( "color",  parse_color )

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
