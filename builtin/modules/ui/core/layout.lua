-- ======================================================================================
-- File         : layout.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 01:29:00 AM | Thursday,May
-- Description  : 
-- ======================================================================================

local __M = {}

local cur_x, cur_y = 0, 0

--/////////////////////////////////////////////////////////////////////////////
-- public functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local do_layout = function ( _root )
    _root._rect = { cur_x, cur_y, _root.style.width, _root.style.height }

    for i=1,#_root.children do
        local el = _root.children[i]
        local next_el = _root.children[i+1]
        local style = el.style

        -- TODO: you can't doing it like this { 
        style.height = el:content_height()
        el._rect = { cur_x, cur_y, style.width, style.height }
        -- } TODO end 

        -- TODO: should recursively get parent style { 
        -- margin_bottom = style.margin[3]
        -- next_margin_top = next_el ? 0 : next_el.style.margin[3]
        -- } TODO end 
        cur_y = cur_y + style.height
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local layout = function ( _root )
    cur_x, cur_y = 0, 0
    do_layout (_root)
end
__M.layout = layout

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
