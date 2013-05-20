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

local def = function ( _prop_name, _parse_func )
    __M[_prop_name] = function ( _text )
        __style[_prop_name] = _parse_func (_text)
        return __M
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_option = function ( _text, _options )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_offset_rect = function ( _text )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_value = function ( _text )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local parse_color = function ( _text )
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

def ( "margin",  parse_offset_rect )
def ( "margin_left",    parse_value )
def ( "margin_right",   parse_value )
def ( "margin_top",     parse_value )
def ( "margin_bottom",  parse_value )

def ( "padding",  parse_offset_rect )
def ( "padding_left",    parse_value )
def ( "padding_right",   parse_value )
def ( "padding_top",     parse_value )
def ( "padding_bottom",  parse_value )

def ( "border",  parse_offset_rect )
def ( "border_left",    parse_value )
def ( "border_right",   parse_value )
def ( "border_top",     parse_value )
def ( "border_bottom",  parse_value )
def ( "border_color",  parse_color )

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
