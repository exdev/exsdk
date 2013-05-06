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

    color   = { 0, 0, 0, 0 }, -- red, gree, blue, alpha.   NOTE: -1 means the element is not defined
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

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
