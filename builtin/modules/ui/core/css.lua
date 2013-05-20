-- ======================================================================================
-- File         : css.lua
-- Author       : Wu Jie 
-- Last Change  : 05/20/2013 | 09:47:39 AM | Monday,May
-- Description  : 
-- ======================================================================================

local __M = {}
local __style = {}

--/////////////////////////////////////////////////////////////////////////////
-- local
--/////////////////////////////////////////////////////////////////////////////

local def = function ( _prop_name, _parse_func )
    __M[_prop_name] = function ( _text )
        __style[_prop_name] = _parse_func (_text)
        return ui.css
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

local finalize = function () 
    local new_style = __style
    __style = {}
    return new_style
end
__M.finalize = finalize

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
